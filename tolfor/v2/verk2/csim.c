/*
 * csim.c - A cache simulator that can replay traces from Valgrind
 *     and output statistics such as number of hits, misses, and
 *     evictions.  The default replacement policy is LRU.
 *
 * Implementation and assumptions:
 *  1. Each load/store can cause at most one cache miss. (the largest requests in the
 *     trace files are for 8 bytes).
 *  2. Instruction loads (I) are ignored, since we are only interested in evaluating
 *     data cache performance.
 *  3. Data modify (M) is treated as a load followed by a store to the same
 *     address. Hence, an M operation can result in two cache hits, or a miss and a
 *     hit plus an possible eviction.
 *
 */
#include <getopt.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <limits.h>
#include <string.h>
#include <errno.h>

/* Type: Memory address */
typedef unsigned long long int mem_addr_t;

/* Type: Cache line */
typedef struct cache_line {
    char valid;
    mem_addr_t tag;
    unsigned long long int lru;    /* counter for LRU */
    unsigned long long int fifo;   /* counter for FIFO */
} cache_line_t;

typedef cache_line_t* cache_set_t;
typedef cache_set_t* cache_t;


/* Hér fyrir neðan eru ýmsar víðværar breytur skilgreindar.  Þið munuð nota þessar
   breytur og ættuð ekki að þurfa að skilgreina fleiri víðværar breytur.
 */


/* Globals set by command line args */
int S = 0;    /* number of sets */
int B = 0;    /* block size (bytes) */
int E = 0;    /* associativity */
char* trace_file = NULL;   /* string with filename */
char* policy = NULL;       /* string with "LRU", "FIFO" or "RAND" */
int policy_code = 1;       /* code for replacement rule 1=LRU, 2=FIFO, 3=RAND */

/* Derived from command line args */
int s;    /* set index bits */
int b;    /* block offset bits */

/* Counters used to record cache statistics */
int miss_count = 0;
int hit_count = 0;
int eviction_count = 0;
unsigned long long int lru_counter = 1;
unsigned long long int fifo_counter = 1;

/* The cache we are simulating */
cache_t cache;  
mem_addr_t set_index_mask;



/* 
 * initCache - Allocate memory, write 0's for valid and tag and LRU
 */
void initCache()
{

    /* Þið þurfið að útfæra þetta fall sem upphafsstillir gagnagrindurnar.
       Það þarf að búa til skyndiminnið sem fylki af mengjum og hvert mengi
       inniheldur mengi af línum (nota malloc).  Það þarf að upphafsstilla
       öll sviðin í öllum línum.
     */


    cache = (cache_t) malloc(S * sizeof(cache_set_t));
    if (cache == NULL) { // ef enhv fokkast upp i mallocation skrefinu
        perror("nadi ekki ad allocatea cache");
        exit(1); // haettir
    }

    for (int i = 0; i < S; i++){ // iterar i gegnum hvert mengi
        cache[i] = (cache_set_t) malloc(E * sizeof(cache_line_t));
        if (cache[i] == NULL){
            perror("nadi ekki ad allocatea cache i sett [i]");
            exit(1);
        }

        for (int j = 0; j < E; j++){ // iteratar yfir allar linur i hverju mengi
            cache[i][j].valid = 0;   
            cache[i][j].tag = 0; 
            cache[i][j].lru = 0; 
            cache[i][j].fifo = 0;    
        }
    }
}


/* 
 * freeCache - free allocated memory
 */
void freeCache()
{

    /* Þið þurfið að útfæra þetta fall sem skilar til baka úthlutuðu minni
     */

    // notum bara free skipunina a hvert mengi ig????
    free(cache); // allt fylkid af settum freed

}


/* 
 * accessData - Access data at memory address addr.
 *   If it is already in cache, increast hit_count
 *   If it is not in cache, bring it in cache, increase miss count.
 *   Also increase eviction_count if a line is evicted.
 */
void accessData(mem_addr_t addr)
{

    /* Þið þurfið að útfæra þetta fall sem útfærir minnisaðgang.
       Helstu skref:
        1. Finna hvaða mengi línan ætti að vera í.
        2. Athuga hvort línan er í því mengi (fara í gegnum öll sætin og ath. valid og tag).
        3. Ef svo er, þá smellur og uppfæra LRU
        4. Ef línan finnst ekki í neinu sæti, þá skellur
        5.  Ef eitthvað sætið í menginu er ólöglegt þá fer nýja línan þangað
        6.  Annars þarf að velja línu til að henda út með réttri útskiptireglu
        7.  Setja nýja línu inn og uppfæra svið í sætinu.
     */
    
    int set_index = (addr >> b) & set_index_mask;
    mem_addr_t tag = addr >> (b + s);

    cache_set_t set = cache[set_index];
    int hit = 0;



    for (int i = 0; i < E; i++){
        if (set[i].valid && set[i].tag == tag) {
            hit_count++;
            hit = 1;
            
            set[i].lru = lru_counter++;
            break;
        }
    }

    if (!hit) {
        miss_count++;
        int eviction_index = -1;
        unsigned long min_lru = ULLONG_MAX;
        unsigned long min_fifo = ULLONG_MAX;

        for (int i = 0; i < E; i++){
            if (!set[i].valid){
                eviction_index = i;
                break;
            }

            if (policy_code == 1 && set[i].lru < min_lru) {
                min_lru = set[i].lru;
                eviction_index = 1i;           
            }
            
            else if (policy_code == 2 && set[i].fifo < min_fifo){
                min_fifo = set[i].fifo;
                eviction_index = i;
            }
        }
        
        if (set[eviction_index].valid) {
            eviction_count++;
        }
        
        set[eviction_index].valid = 1;
        set[eviction_index].tag = tag;
        set[eviction_index].lru = ++lru_counter;
        set[eviction_index].fifo = fifo_counter;
        
    }
}


/*
 * replayTrace - replays the given trace file against the cache 
 */
void replayTrace(char* trace_fn)
{
    char buf[1000];
    mem_addr_t addr=0;
    unsigned int len=0;
    FILE* trace_fp = fopen(trace_fn, "r");

    if(!trace_fp){
        fprintf(stderr, "%s: %s\n", trace_fn, strerror(errno));
        exit(1);
    }

    while( fgets(buf, 1000, trace_fp) != NULL) {
        if(buf[1]=='S' || buf[1]=='L' || buf[1]=='M') {
            sscanf(buf+3, "%llx,%u", &addr, &len);
      
            accessData(addr);

            /* If the instruction is R/W then access again */
            if(buf[1]=='M')
                accessData(addr);
        }
    }

    fclose(trace_fp);
}

/* 
 * printSummary - Summarize the cache simulation statistics
 */
void printSummary(int hits, int misses, int evictions)
{
    printf("hits: %d  misses: %d  evictions: %d\n", hits, misses, evictions);
    printf("miss ratio: %.2f%%\n", 100.0*misses/(hits+misses));
}

/*
 * printUsage - Print usage info
 */
void printUsage(char* argv[])
{
    printf("Usage: %s [-h] -S <num> -E <num> -B <num> -p <P> -t <file>\n", argv[0]);
    printf("Options:\n");
    printf("  -h         Print this help message.\n");
    printf("  -S <num>   Number of sets (s = log_2(S) is the number of bits for set index).\n");
    printf("  -E <num>   Number of lines per set (the associativity of the cache).\n");
    printf("  -B <num>   Number of bytes per line (b = log_2(B) is the number of bits for line offset).\n");
    printf("  -p <P>     Selects line replacement policy, LRU, FIFO or RAND.\n");
    printf("  -t <file>  Trace file.\n");
    printf("\nExamples:\n");
    printf("  linux>  %s -S 16 -E 1 -B 16 -p LRU -t traces/yi.trace\n", argv[0]);
    printf("  linux>  %s -v -S 256 -E 2 -b 16 -p FIFO -t traces/yi.trace\n", argv[0]);
    exit(0);
}

/*
 * main - Main routine 
 */
int main(int argc, char* argv[])
{
    char c;

    while( (c=getopt(argc,argv,"S:E:B:p:t:vh")) != -1){
        switch(c){
        case 'S':
            S = atoi(optarg);
            break;
        case 'E':
            E = atoi(optarg);
            break;
        case 'B':
            B = atoi(optarg);
            break;
        case 'p':
            policy = optarg;
        case 't':
            trace_file = optarg;
            break;
        case 'h':
            printUsage(argv);
            exit(0);
        default:
            printUsage(argv);
            exit(1);
        }
    }

    /* Make sure that all required command line args were specified */
    if (S == 0 || E == 0 || B == 0 || trace_file == NULL || policy == NULL) {
        printf("%s: Missing required command line argument\n", argv[0]);
        printUsage(argv);
        exit(1);
    }
    
    /* Check replacement policy string and set code */
    if ( strcmp(policy, "LRU") == 0 ) policy_code = 1;
    else if (strcmp(policy, "FIFO") == 0 ) policy_code = 2;
    else if (strcmp(policy, "RAND") == 0 ) policy_code = 3;
    else {
        printf("%s: Line replacement policy invalid, use LRU, FIFO or RAND\n", argv[0]);
        printUsage(argv);
        exit(1);
   }

	/* Compute s and b from command line args */
	s = (unsigned int) log2(S);
	b = (unsigned int) log2(B);

	/* Initialize cache */
	initCache();

	replayTrace(trace_file);

	/* Free allocated memory */
	freeCache();

	/* Output the hit and miss statistics for the autograder */
	printSummary(hit_count, miss_count, eviction_count);
	return 0;
}

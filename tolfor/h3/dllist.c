/******************************************************************
  Beinagrind að lausn á dæmi 5 í heimadæmum 3 í Tölvutækni og
  forritun, haust 2024
  
  Sjá lýsingu verkefnis á dæmablaði 
*******************************************************************/
#include <stdio.h>
#include <stdlib.h>

struct dNode {
   int data;
   struct dNode *prev;
   struct dNode *next;
};

/* Haus og hali listans eru víðværar breytur */
struct dNode *head = NULL;
struct dNode *tail = NULL;


/* Prentar út stök í tvítengdum list */
void printList() {
    struct dNode *p = head;
    
	printf("Listi: ");
	while (p != NULL) {
		printf("%d ", p->data);
		p = p->next;
	}
	printf("\n");
}


/* Prentar út stök í tvítengdum list í öfugri röð */
void printRevList() {

    /***** Þið skrifið þennan hluta *****/
	struct dNode *p = tail;

	printf("RevListi: ");
	while (p != NULL) {
		printf("%d ", p->data);
		p = p->prev;
	}
	printf("\n");
}


/* Setur inn hnút með gildinu v sem hnút númer k í tvítengdum lista */
void insAs(int k, int v) {
    struct dNode *p, *q;
    int i;

    /* Búa til hnútinn og setja gildið inn í hann */
    p = (struct dNode *)malloc(sizeof(struct dNode));
    p->data = v;
    
    if (head == NULL) {
        /* Tómur listi */

        /***** Skrifið kóða hér *****/
		head = p;
		tail = p;

    } else if (k == 0) {
        /* innsetning fremst í listann */

        /***** Skrifið kóða hér *****/
		p->next = head;
		head->prev = p;
		head = p;

    } else {
        /* annars rekja okkur eftir listanum */


        /***** Skrifið kóða hér *****/
        /* Athugið að hér gæti þurft að uppfæra tail-bendinn */

		int end = 0;
		q = head;
		for ( int i = 0; i < k; i++ ) {
			p->prev = q;
			if ( q->next == NULL ) {
				tail = p;
				end = 1;
				break;
			} else {
				q = q->next;
			}
		}
		(p->prev)->next = p;
		if ( !end ) {
			p->next = q;
			q->prev = p;
		}
   }
}


/* Býr til n-staka tvítengdan lista með slembigildum (0 til 99).
   Setur víðværu breyturnar head og tail */
void createRandList(int n) {
    struct dNode *p;
    int i;

    /* Ef n er núll eða minna þá tómur listi */
    if (n < 1) {
        head = NULL;
        tail = NULL;
        return;
    }
    
    /* Búa til fyrsta hnútinn og láta haus og hala benda á hann */
    head = tail = (struct dNode *)malloc(sizeof(struct dNode));
    head->data = rand()%100;
    head->prev = NULL;
    head->next = NULL;
    
    /* Búa til restina af hnútunum og setjum þá aftast */
    for(i=1; i<n; i++) {
        p = (struct dNode *)malloc(sizeof(struct dNode));
        p->data = rand()%100;
        p->prev = tail;
        p->next = NULL;
        tail->next = p;
        tail = p;
    }
}


int main() {
    int i;

    /* Búa til listann með 5 slembigildum */
    createRandList(5);
    printList();
    printRevList();

    printf("\n");
    
    printf("Setja 10 sem stak 0:\n");
    insAs(0, 10);
    printList();
    
    printf("Setja 20 sem stak 10:\n");
    insAs(10, 20);
    printList();

    printf("Setja 30 sem stak 3:\n");
    insAs(3, 30);
    printList();

   return 0;
}


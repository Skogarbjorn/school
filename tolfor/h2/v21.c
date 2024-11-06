/***************************************************************
  Beinagrind að lausn á dæmi 5 í heimadæmum 2 í Tölvutækni
  og forritun, haust 2024
  
  Sjá lýsingu verkefnis á dæmablaði 
****************************************************************/
#include <stdio.h>
#include <stdlib.h>

#define NUM_ELEM 10

struct Node {
	int val;
	struct Node *next;
};

/* Prentar út stökin í tengdum list */
void printlist(struct Node *h) {
	printf("Listi: ");
	while (h != NULL) {
		printf("%d->", h->val);
		h = h->next;
	}
	printf("\n");
}

/* Afritar stök fylkis yfir í tengdan lista */
struct Node* vec2list(int a[], int n) {
    struct Node *head, *p;
    int i;
    
    head = NULL;

    /* Þið skrifið þennan hluta */

	struct Node *q;
	for ( i = 0; i < n; i++ ) {
		q = (struct Node*)malloc(sizeof(struct Node));
		q->val = a[i];
		q->next = NULL;

		if (head == NULL) {
			head = q;
		} else {
			p->next = q;
		}
		p = q;
	}
    
    return head;
}

int main(int argc, char **argv) {
    struct Node *list;
    int a[NUM_ELEM];
	int i;
	
	/* Setja gildi í fylki */
    printf("Fylki: ");
    for (i=0; i<NUM_ELEM; i++) {
        a[i] = 2*(i+1);
        printf("%d ", a[i]);
    }
    printf("\n");
    
    /* Breyta í tengdan lista */
    list = vec2list(a, NUM_ELEM);
    
    /* Prenta út tengdan lista */
    printlist(list);

    return 0;
}


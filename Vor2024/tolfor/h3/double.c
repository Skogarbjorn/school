/*******************************************************************
  Beinagrind fyrir dæmi 3 í heimadæmum 3 í Tölvutækni og forritun,
  haust 2024
  
  Skrifa fall sem tvöfaldar stærð fylkis sem er úthlutað á kösinni 
********************************************************************/
#include <stdio.h>
#include <stdlib.h>


/* Fallið fær inn bendi á heiltölufylkið a af stærð n
   og skilar bendi á tvöfalt stærra fylki með sömu stökum
   og voru í upphaflega fylkinu.  Minni gamla fylkisins
   er frelsað með free()   */
int* doubleArr(int* a, int n) {

    /***** Þennan hluta skrifið þið *****/

	int *b = (int *)calloc(n*2, sizeof(int));
	for ( int i = 0; i < n; i++ ) {
		b[i] = a[i];
	}
	free(a);

    /* Skilum hér bendi á upphaflega fylkið til að
       beinagrindin keyri, en gæti þurfa að breyta    */
    return b;
}


int main() {

    int i;
    int n = 10;
    
    /* Skilgreinum a sem 10 staka fylki með slembistökum */
    int *a = (int *)calloc(n, sizeof(int));
    for (i=0; i<n; i++)
        a[i] = rand()%100;
    

    /* Tvöfalda fylkið */
    a = doubleArr(a, n);
    n *= 2;

    /* Nú er a 20 staka fylki með fyrstu 10 stökin óbreytt */
    printf("n: %d\n", n);
    for (i=0; i<n; i++)
        printf("%d\n", a[i]);

   return 0;
}


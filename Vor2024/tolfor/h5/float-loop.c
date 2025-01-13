/******************************************************************
   Forrit sem ítrar frá 0.0 til 1.0 með upphækkun 0.1
   Dæmi 2 í heimadæmum 5 í Tölvutækni og forritun, 2024
*******************************************************************/
#include <stdio.h>

int main ()
{
    double val = 0.0;
    double end = 1.0;
    double inc = 0.1;
    double sum = 0.0;

    printf ("Ítra með fleytitölum frá %.2f til %.2f, upphækkun %.2f\n", val, end, inc);

    for (val=0.0; val!=end; val+=inc) {
        sum += val;
        printf ("val = %.15f;  sum = %.15f\n", val, sum);
    }

    printf ("Lykkju lokið með val = %.2f;  sum = %.2f\n", val, sum);

}

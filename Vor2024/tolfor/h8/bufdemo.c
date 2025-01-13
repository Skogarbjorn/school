/* Demonstration of buffer overflow */
#include <stdio.h>
#include <stdlib.h>

/* Implementation of library function gets() */
char *gets(char *s)
{
    int c;
    char *dest = s;
    while ((c = getchar()) != '\n' && c != EOF) 
        *dest++ = c;
    if (c == EOF && dest == s)
        return NULL;
    *dest++ = '\0';
    return s;  
}

/* Read input line and write it back */
void echo()
{
    char buf[4];      /* Way too small! */
    gets(buf);
    puts(buf);
}

int main(int argc, char *argv[])
{
    printf("Type a string:");

    echo();

    return 0;
}

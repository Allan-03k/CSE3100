#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* print out an error message and exit */
void my_error(char *s)
{
    perror(s);
    exit(1);
}

/* Concatnate two strings.
 * Dynamically allocate space for the result.
 * Return the address of the result.
 */
char *my_strcat(char *s1, char *s2)
{
    // TODO
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    char *result = (char*)malloc(len1 + len2 +1);
    
    memcpy(result,s1,len1);
    memcpy(result+len1,s2,len2);
    result[len1+len2]=0x00;
    if(s1[0]!='\0'){
        free(s1);
    }
    
    return result;
}

int main(int argc, char *argv[])
{
    char    *s;

    s = my_strcat("", argv[0]);

    for (int i = 1; i < argc; i ++) {
        s = my_strcat(s, argv[i]);
    }

    printf("%s\n", s);
    free(s);
    return 0;
}
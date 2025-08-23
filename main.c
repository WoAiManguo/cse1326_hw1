#include <stdio.h>
#include <stdlib.h>

int main ()
{
    FILE *file;
    file = fopen("iata-icao.csv", "r");

    if(file == NULL)
    {
        printf("Error opening file.\n");
        return 1;
    }

    //seek EOF, return ptr position for size of file
    fseek(file, 0L, SEEK_END);
    long filesz = ftell(file);

    int *ptr = (int *)malloc(filesz);

    if (ptr == NULL)
    {
        printf("Failed to allocate memory.\n");
        return 1;
    }

    printf("memory ptr is %p\n\n", ptr);

    rewind(file);


    int lines = 0;

/*     do
    {

    } while(!feof(file)); */

    return 0;
}
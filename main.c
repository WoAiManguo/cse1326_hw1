#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


int main ()
{
    char u_in[50];
    char* tkn;
    char* pend;
    float lat;
    float lon;

    FILE *file;
    file = fopen("iata-icao.csv", "r");

    if(file == NULL)
    {
        printf("Error opening file.\n");
        return 1;
    }


    while (strcmp(u_in, "stop") != 0)
    {
        scanf("%[^\n]%*c", &u_in);
        printf("string: %s\n", u_in);
        if(isdigit(u_in) != 0)
        {
            lat = strtof(u_in, &pend);
            lon = strtof(pend, NULL);
            printf("lat is %f lon is %f\n", lat, lon);
        }
    }
    

    return 0;
}
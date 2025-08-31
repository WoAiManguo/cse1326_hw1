#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct
{
    char *country_code;
    char *region_name;
    char *iata;
    char *icao;
    char *airport;
    char *latitude;
    char *longitude;
} Airport;

char *strdup(const char *src)
{
    if (!src)
        return NULL;
    char *dst = malloc(strlen(src) + 1);
    if (dst)
        strcpy(dst, src);
    return dst;
}

char *strip_quotes(char *str)
{
    if (str == NULL)
        return NULL;

    if (str[0] == '"')
        str++;

    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '"')
    {
        str[len - 1] = '\0';
    }

    return str;
}

int main(int argc, char *argv[])
{
    const int MAXLN = 1024;
    char line[MAXLN];

    int cap = 100;
    int count = 0;

    FILE *file;
    file = fopen("iata-icao.csv", "r");

    if (file == NULL)
    {
        printf("Error opening file.\n");
        return 1;
    }

    fgets(line, MAXLN, file); //skips first line if header

    if (strstr(line, "country_code"))
    {
    }
    else
        fseek(file, 0, SEEK_SET); //else seeks to beginning of file

    Airport *airports = malloc(cap * sizeof(Airport));

    while (fgets(line, MAXLN, file))
    {
        if (count >= cap)
        {
            cap *= 2;
            Airport *temp = realloc(airports, cap * sizeof(Airport));
            airports = temp;
        }

        char *tokens[7];
        int field = 0;
        char *token = strtok(line, ",");

        while (token && field < 7)
        {
            token[strcspn(token, "\r\n")] = '\0';
            tokens[field++] = strip_quotes(token);
            token = strtok(NULL, ",");
        }

        if (field == 7)
        {
            airports[count].country_code = strdup(tokens[0]);
            airports[count].region_name = strdup(tokens[1]);
            airports[count].iata = strdup(tokens[2]);
            airports[count].icao = strdup(tokens[3]);
            airports[count].airport = strdup(tokens[4]);
            airports[count].latitude = strdup(tokens[5]);
            airports[count].longitude = strdup(tokens[6]);
            count++;
        }
    }

    fclose(file);

    printf("There are %d entries in the list\n", count);

    while (1)
    {
        long lat;
        long lon;

        char u_in[100];
        scanf("%99[^\n]", u_in);
        getchar();

        u_in[strcspn(u_in, "\n")] = '\0';

        if (strcmp(u_in, "stop") == 0)
            break;

        sscanf(u_in, "%ld %ld", &lat, &lon); //saves stdin to lat and lon



        for (int i = 0; i < count; i++)
        {
            char *end1, *end2;
            long airport_lat = strtol(airports[i].latitude, &end1, 10);
            long airport_lon = strtol(airports[i].longitude, &end2, 10);

            if (airport_lat == lat && airport_lon == lon)
            {
                printf("%s %s %s %s %s %s %s\n",
                       airports[i].country_code,
                       airports[i].region_name,
                       airports[i].iata,
                       airports[i].icao,
                       airports[i].airport,
                       airports[i].latitude,
                       airports[i].longitude);
            }
        }
    }

    for (int i = 0; i < count; i++)
    {
        free(airports[i].country_code);
        airports[i].country_code = NULL;
        free(airports[i].region_name);
        airports[i].region_name = NULL;
        free(airports[i].iata);
        airports[i].iata = NULL;
        free(airports[i].icao);
        airports[i].icao = NULL;
        free(airports[i].airport);
        airports[i].airport = NULL;
        free(airports[i].latitude);
        airports[i].latitude = NULL;
        free(airports[i].longitude);
        airports[i].longitude = NULL;
    }
    free(airports);

    return 0;
}

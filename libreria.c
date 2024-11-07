#include "libreria.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 1024 // Tamaño buffer de stdin
#define DEFAULT 10 // Valor predeterminado que se le dara a N

static char*  read_line(FILE* archivo); // Lectura de lineas dinamicamte
static int    find_short(int *longitudes, int len, int N); // Busca la linea más corta en un array


static char* read_line(FILE* archivo) {
    char* linea;

    linea = malloc(SIZE);
    if (linea == NULL) {
        return NULL;
    }
    if (fgets(linea, SIZE, archivo) == NULL) {
        free(linea);
        return NULL;
    }
    return linea;
}

int head(int N){
    char*    buffer;

    if (N <= 0)
        N = DEFAULT;

    while (N > 0 && (buffer = read_line(stdin)))
    {
        printf("%s", buffer);
        free(buffer);
        N--;
    }
    
    return 0;
}

int tail(int N){
    char*   buffer;
    int     i;
    int     print;

    if (N <= 0)
        N = DEFAULT;
    // Un array de punteros para ir almacenando las lineas
    char* lineas[N];

    for (i = 0; i < N; i++) {
        lineas[i] = NULL;
    }

    i = 0;

    // Vamos guardando las lineas en el array hasta dejar las N ultimas
    while ((buffer = read_line(stdin)))
    {
        // Liberamos en el caso de que la linea a escribir este llena
        if (lineas[i] != NULL)
            free(lineas[i]);
        lineas[i] = strdup(buffer);
        free(buffer);   
        i = (i + 1) % N; // Para no sobrepasar el indice N
    }

    // Empezamos a imprimir desde la siguiente posicion a i
    for (int j = 0; j < N; j++)
    {
        print = (i + j) % N;
        // Comprobamos que no sea NULL por si stdin tiene menos de N lineas
        if (lineas[print] != NULL)
        {
            printf("%s", lineas[print]);
            free(lineas[print]);
        }
    }

    return 0;
}

static int find_short(int *longitudes, int len, int N)
{
    int found;
    int i;

    found = -1;
    i = 0;
    // Va comparando 
    while (i < N)
    {
        if (len > longitudes[i])
        {
            if (found == -1 || longitudes[i] < longitudes[found])
                found = i;
        }
        i++;
    }
    return found;
}

int longlines(int N){
    char*   buffer;
    int     len;
    char**  lineas; // Almacena las lineas más largas actuales
    int*    longitudes; // Almacena las longitudes de lineas más largas
    int     index;
    int     count;
    int     i;

    if (N <= 0)
        N = DEFAULT;

    lineas = malloc(N * sizeof(char*));
    longitudes = calloc(N, sizeof(int));

    count = 0;
    while ((buffer = read_line(stdin)))
    {
        len = strlen(buffer);
        index = find_short(longitudes, len, N);
        if (index != -1)
        {
            free(lineas[index]);
            lineas[index] = strdup(buffer);
            longitudes[index] = len;
            count++;
        }
    }

    i = 0;
    while (i < count)
    {
        index = 0;
        for (int j = 0; j < N; j++)
        {
            if (longitudes[j] > longitudes[index])
                index = j;
        }
        if (longitudes[index] != 0)
        {
            printf("%s", lineas[index]);
            free(lineas[index]);
            longitudes[index] = 0;
            i++;
        } else
            i++;
    }

    free(lineas);
    free(longitudes);

    return 0;
}

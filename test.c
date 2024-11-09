#include "libreria.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define WRONG_ARGC "Error: Número incorrecto de argumentos. Uso: ./test <función> [número de líneas]"
#define WRONG_FUNCTION "Error: Nombre de función no válido -head, -tail, -longlines."

static void print_error(char *error, int type)
{
    printf("%s \n", error);
    exit(type);
}


int main(int argc, char** argv)
{
    int N;

    if (argc != 2 && argc != 3)
        print_error(WRONG_ARGC, 1);
    
    if (argc == 3)
        N = atoi(argv[2]);
    else
        N = 10;

    if (strcmp(argv[1], "-head") == 0)
		return (head(N));
    if (strcmp(argv[1], "-tail") == 0)
		return (tail(N));
	if (strcmp(argv[1], "-longlines") == 0)
		return (longlines(N));

    print_error(WRONG_FUNCTION, 3);
}
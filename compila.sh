#!/bin/bash

# Proceso de compilación

# Creamos un archivo objeto de nuestro programa
gcc -Wall -Werror -Wextra -c libreria.c -o libreria.o

# Creamos una libreria estática usando nuestro archivo objeto
ar -rv liblibreria.a libreria.o

# Creamos un ejecutable test enlazando los archivos cabecera y libreria
gcc -Wall -Werror -Wextra test.c -o test -I . -L . -llibreria

# Borramos archivos objeto
rm -fr *.o

RED='\033[0;31m'
NC='\033[0m' # No Color
echo -e " ${RED}Compilación terminada${NC} archivos objeto borrados"
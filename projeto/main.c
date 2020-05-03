/**
@file main.c
Ficheiro que tem a função principal(main) do projeto.
*/
#include <stdio.h>
#include <stdlib.h>
#include "dados.h"
#include "interface.h"
#include "logica.h"
#include <time.h>

/**
\brief 
Função principal do projeto que chama a função inicializar_estado e afunção interpretador. Por fim, liberta a memória ocupada por esse estado.
*/


int main () {
        srand(time(NULL));
        ESTADO *  estado;
        estado = inicializar_estado();
        interpretador(estado);
        free(estado);   
        return 0;
}

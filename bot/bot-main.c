/**
@file bot-main.c
Ficheiro que contém a função principal(main) do módulo bot.
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "dados.h"
#include "logica.h"
#include "interface.h"
#include "bot.h"
/**
\brief 
Função main do módulo bot que recebe nome de dois ficheiros como argumento,inicializa a semente de aleatoridade baseda no tempo e inicializa um estado. De seguida lê o estado ficheiro, chama a função jogar_bot e grava o novo estado no ficheiro dado como argumento.
*/
int main (int argc, char *argv[]) {

    srand(time(NULL)); 
    if (argc == 3) {

       ESTADO *e = inicializar_estado();
       altera_isBot(e);
       ler(e, argv[1]); 
       jogar_bot(e);
       gravar(e, argv[2]);
       free(e);
       
    }
    else {
        printf("Comando Inválido");
    }
    return 0;

    

}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "dados.h"
#include "logica.h"
#include "interface.h"
#include "bot.h"

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

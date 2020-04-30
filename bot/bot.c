#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../dados.h"
#include "../interface.h"
#include "../logica.h"
#include "bot.h"
   
void jogar_bot(ESTADO * e) {
   
    COORDENADA cord;
        
    srand(time(NULL));  
    int r = rand() % 2;  

    if(obter_numero_de_jogadas(e) <= 2) {
        cord = r ? estrategia_floodfill(e) : estrategia_paridade(e);
    }
    else {
        cord = estrategia_floodfill(e);

        if (cord.linha == 3 && cord.coluna == 4) {
           cord = estrategia_paridade(e);     
        }
    }
    jogar(e,cord);
    
}

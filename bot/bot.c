#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "dados.h"
#include "interface.h"
#include "logica.h"
#include "bot.h"
   
void jogar_bot(ESTADO * e) {
   
    COORDENADA cord;
        

    cord = estrategia_floodfill(e);

    if (cord.linha == 3 && cord.coluna == 4) {
           cord = estrategia_paridade(e);     
    }
    
    jogar(e,cord);
    
}

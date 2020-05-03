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
    COORDENADA cord2; //será a jogada simulada a partir de nossa jogada simulada
    ESTADO estado_copia = *e;
        
    cord = estrategia_paridade(e);
    if (jogar(e,cord) != 2){ //Verifica se já dá para ganhar com a paridade  
        *e = estado_copia;  
        cord = estrategia_floodfill(e);
        if ((cord.linha != 3 || cord.coluna != 4)
         && obter_estado_casa(e,cord) != UM
         && obter_estado_casa(e,cord) != DOIS ){
    /*Processo de simulação sobre o que acontecerá depois de nossa possível jogada*/
            jogar(e,cord);
            cord2 = estrategia_paridade(e);
         }
        if (obter_estado_casa(e,cord) != UM
             && obter_estado_casa(e,cord) != DOIS){
             if ((cord.linha == 3 && cord.coluna == 4) || (jogar(e,cord2) == 2)) {
                cord = estrategia_paridade(&estado_copia);     
             }
         }
    }
    *e = estado_copia;
    jogar(e,cord);
    
}

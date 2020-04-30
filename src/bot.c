#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dados.h"
#include "interface.h"
#include "logica.h"



void jogar_bot(ESTADO * e) {

    COORDENADA cord = estrategia_floodfill(e);
    jogar(e,cord);
    

}

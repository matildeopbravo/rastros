#include <stdio.h>
#include <stdlib.h>
#include "dados.h"


int jogar(ESTADO *estado, COORDENADA c) {

    estado -> tab [c.linha] [c.coluna] =  BRANCA;

    return 1;
}

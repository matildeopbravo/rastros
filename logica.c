#include <stdio.h>
#include <stdlib.h>
#include "dados.h"


int jogar(ESTADO *estado, COORDENADA c) {

    printf("jogar %d %d\n", c.coluna, c.linha);
    estado -> tab [c.linha] [c.coluna] =  BRANCA;

    return 1;
}

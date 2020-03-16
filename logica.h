#ifndef CAMADA_LOGICA_H
#define CAMADA_LOGICA_H

int jogar(ESTADO *estado, COORDENADA c);
int verifica_fim ( ESTADO *e , int l , int c, int j );
int verifica_valida ( ESTADO *e , COORDENADA jog_ant , COORDENADA jog_efet);

#endif
/**
@file logica.h
*/

#ifndef CAMADA_LOGICA_H
#define CAMADA_LOGICA_H

/**
\brief Executa a jogada em si.
Se a jogada não for válida, a função retorna 0.
@param estado Apontador para o estado
@param c Coordenada da jogada efetuada
*/
int jogar(ESTADO *estado, COORDENADA c);

/**
\brief Esta função verifica se o jogo chegou ao fim.
Verifica as condições de fim de jogo,isto é, "jogador atual nas extremidades 1 ou 2, ou jogador atual
encurralado". Retornando 0 caso não se verifique nenhum.
@param e Apontador para o estado
@param l linha da jogada efetuada
@param l coluna da jogada efetuada 
@param j jogador atual
*/
int verifica_fim ( ESTADO *e , int l , int c, int j );
/**
\brief Esta função verifica se a jogada que se pretende efetuar é válida.
Para a jogada ser válida, é necessário que a casa para onde esta se pretende efetuar esteja:
1) Vazia (sendo do tipo VAZIO, UM ou DOIS);
2) A uma distância de 1 na horizontal, vertical, ou diagonal da casa atual.
@param estado Apontador para o estado
@param c Coordenada da jogada anterior
@param c Coordenada da jogada efetuada
*/

int verifica_valida ( ESTADO *e , COORDENADA jog_ant , COORDENADA jog_efet);

#endif
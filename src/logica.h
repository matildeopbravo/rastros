/**
@file logica.h
*/
#ifndef CAMADA_LOGICA_H
#define CAMADA_LOGICA_H
/**
\brief Executa a jogada em si. Se algum jogador vencer a partida, após a execução de uma jogada, retorna o valor 2.
Se a jogada não for válida, a função retorna 0. Caso não for nenhum dos casos anteriores, devolve 1.
Atualiza a struct principal mediante a jogada efetuada.
@param estado Apontador para o estado
@param c Coordenada da jogada efetuada
*/
int jogar(ESTADO *estado, COORDENADA c);
/**
\brief Esta função verifica se o jogo chegou ao fim.
Verifica as condições de fim de jogo,isto é, "jogador atual nas extremidades 1 ou 2, ou jogador atual
encurralado". Retorna 0 caso não se verifique nenhum, em contrapartida devolve o número do jogador vencedor.
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
Devolve 1 caso for válida, retorna 0 caso contrário.
@param estado Apontador para o estado
@param c Coordenada da jogada anterior
@param c Coordenada da jogada efetuada
*/

int verifica_valida ( ESTADO *e , COORDENADA jog_ant , COORDENADA jog_efet);

COORDENADA estrategia_paridade(ESTADO *e);

int calcula_area(COORDENADA * possiveljogada, ESTADO * e);

#endif
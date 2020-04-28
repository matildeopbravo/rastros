/**
@file logica.h
*/
#include "listas.h"
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
@param e Apontador para o estado
@param c Coordenada da jogada anterior
@param c Coordenada da jogada efetuada
*/

int verifica_valida ( ESTADO *e , COORDENADA jog_ant , COORDENADA jog_efet);

COORDENADA estrategia_paridade(ESTADO *e);

int calcula_area(COORDENADA * possiveljogada, ESTADO * e);

COORDENADA estrategia_floodfill ( ESTADO * e ) ;
/**
\brief Preenche a lista (*posicoesvazias) com as possíveis jogadas que o jogador atual consegue
efetuar. Retorna uma coordenada que vai servir mais a frente para ver se é preciso efetuar uma estratégia
ou não. Caso a coordenada devolvida seja a mesma que a função recebeu como argumento (3,4), significa
que ela não foi alterada em momento algum durante a função e por tanto não foi encontrado uma jogada
que garanta vitória ao jogador atual(pois assim a coordenada a devolver seria a de tal jogada).
@param e Apontador para o estado
@param e Apontador para o estado
@param posicoesvazias apontador para uma lista(lista das possíveis jogadas)
@param coord_escolhida coordenada a ser devolvida pela função
*/
COORDENADA insere_possiveis_jogadas ( ESTADO *e , LISTA *posicoesvazias,COORDENADA coord_escolhida );
/**
\brief Inicializa a matriz que vai conter o valor de cada casa do tabuleiro para o algoritimo floodfill.
Tal inicialização dependerá da flag dada. Isto porque podemos fazer tal inicialização em 2 momentos distintos:
quando é possível chegar na cada da vitória e quando não é. Mediante os 2 casos teremos uma inicialização diferente.
@param num_casa Matriz com os valores de cada casa do tabuleiro
@param e Apontador para o estado
@param flag variável de aviso para diferenciar os 2 momentos distintos já enunciados
*/
void inicializa_num_casa(int num_casa[8][8],ESTADO *e, int flag);
/**
\brief Função invocada pela funcção "estratégia_floodfill" para melhor organização e gestão de memória
da mesma. Realiza o processo da escolha da melhor jogada a ser efetuada (que é devolvida pela função).
É a função cerne do raciocínio em si por trás de tal estratégia.
@param e apontador para o estado
@param possiveis_jogadas lista ligada com as possíveis jogadas a efetuar pelo jogador atual
@param coord_escolhida melhor coordenada a ser jogada, modificada e devolvida pela função.
*/
COORDENADA auxiliar_floodfill(ESTADO *e,LISTA possiveis_jogadas,COORDENADA coord_escolhida);
/**
\brief Função principal da estratégia floodfill. Devolve a melhor jogada a ser efetuada pelo jogador atual.
Para melhor organização tal função se ramifica numa função auxiliar que seleciona tal jogada. Caso for
possível vencer a partida com base numa jogada tal funçãop auxiliar  não é chamada e é devolvido o valor
da coordenada da vitória.
@param e apontador para o estado
*/
COORDENADA estrategia_floodfill ( ESTADO * e );
/**
\brief Dá para cada casa do tabuleiro um valor específico. Tal valor será importante para indicar o 
caminho mais curto para a casa da vitória(ou o mais longo para a casa da derrota mediante a flag dada como argumento). 
As casas não preenchidas aqui já foram preenchidas pela função que inicializa a matriz com os valores de cada casa do tabuleiro.
É parado o preenchimento quando consigo chegar na casa onde estou partindo de um preenchimento com origem
na casa que desejo chegar, e isto simboliza que encontrei o caimho mais curto para ela. Tal função devolve
o valor que dei a casa onde estou subtraído por 1, sendo tal valor único, sevindo de guia para conseguir
retirar a  jogada desejada (pois ela terá tal valor devolvido).
@param num_casa matriz com os valores de casa casa do tabuleiro
@param e apontador para o estado
@param flag Indicador se devo preencher supondo que quero encontrar o caminho mais curto para minha casa ou o mais longo para a casa da derrota
*/
int preenche_valor_das_casas(int num_casa[8][8],ESTADO *e, int flag);
/**
\brief Duplica uma coordenada e coloca ela num endereço novo. Possui utilidade no preenchimento da lista
ligada de modo a evitar perder seu conteúdo mais tarde.
@param coordenada Coordenada a ser duplicada e colocada num endereço novo
*/
COORDENADA * duplica_coordenada(COORDENADA coordenada);
/**
\brief Recebe o valor dado a casa tual de acordo com a estratégia floodfill, e devolve uma das casas
vizinhas armazenadas na lista ligada intitulada como "possiveis_jogadas" que tenha o valor da casa atual
subtraido por 1.
@param valor_casa_atual número dado a casa atual do jogador a partir da estratégia floodfill
@param possiveis_jogadas lista ligada que armazenará as possíveis jogadas a se fazer
@param num_casa matriz com os valores numéricos dados a cada possível casa do tabuleiro a partir da estratégia floodfill
*/
COORDENADA devolve_coordenada_flood ( int valor_casa_atual , LISTA possiveis_jogadas , int num_casa[8][8])

#endif
/**
@file interface.h
*/

#ifndef CAMADA_INTERFACE_H
#define CAMADA_INTERFACE_H

/**
\brief Função que apresenta o estado do tabuleiro. 
Recorre a carácteres especiais, bem com os números e letras das linhas e colunas correspondentes. 
O tabuleiro é apresentado na stream fornecida como argumento será um apontador para um ficheiro ou stdout.
@param estado Apontador para o estado
@param stream Apontador para FILE
*/
void mostrar_tabuleiro(ESTADO * estado, FILE * stream);
/**
\brief Função que apresenta o prompt, o qual contém o número do jogador atual,o número e jogadas e o número de comandos efetuados.
O prompt é apresentado na stream fornecida como argumento que será um apontador para um ficheiro ou stdout.
@param e Apontador para o estado
@param stream Apontador para FILE
*/
void mostrar_prompt(ESTADO * e);
/**
\brief Função que apresenta as jogadas efetuadas no jogo atual, ou seja, o array JOGADAS do estado. 
As jogadas são apresentadas na stream fornecida como argumento que será um apontador para um ficheiro ou stdout.
@param e Apontador para o estado
@param stream Apontador para FILE
*/
void mostrar_jogadas (ESTADO * e,  FILE * stream);
/** 
\brief Funcão que apresenta no ecrã o vencedor do jogo atual 
@param estado Apontador para o estado
*/
void printar_campeao(ESTADO * estado);
/** 
\brief Função que controla o Input/Output do jogo. 
Apresenta no ecrã, em primeiro lugar, o estado atual do tabuleiro e o prompt.
Além disso,lê o input do utilizador e interpreta os comandos/jogadas que este efetuar e chama as devidas funções.
@param e Apontador para o estado
*/
int interpretador(ESTADO *e);
/**
\brief Função que verifica se o comando escrito pelo utilizador é "ler" ou "gr"
@param token Apontador para caracter
*/
COMANDO verifica_comando( char * token );
/** 
\brief Função que lê o tabuleiro  de um ficheiro e guarda no estado atual o array tab e a COORDENADA da última jogda. 
@param e Apontador para o estado
@param file_pointer Apontador para FILE
*/
void ler_tabuleiro(ESTADO * e, FILE * file_pointer);
/** 
\brief Função que lê a lista de jogadas pela forma como foram gravadas no ficheiro. 
Ou seja, uma jogada em cada linha. Acrescenta cada jogada ao array JOGADAS do estado atual.
@param e Apontador para o estado
@param file_pointer Apontador para FILE
*/
void ler_jogadas(ESTADO * e, FILE * file_pointer);
/** 
\brief Função que lê o prompt que foi gravado num ficheiro. 
Atualiza o estado com os valores do número de jogadas, jogador atual número de comandos.
@param e Apontador para o estado
@param file_pointer Apontador para FILE
*/
void ler_prompt(ESTADO *e,FILE* file_pointer);
/** 
\brief Função que dado um nome de um ficheiro, grava o tabuleiro, o prompt e a a lista de jogadas no mesmo.
@param e Apontador para o estado
@param nome_ficheiro Apontador para carácter (primeiro caracter do nome do ficheiro)
*/
void gravar (ESTADO * e, char * nome_ficheiro);
/** 
\brief Função que dado um nome de um ficheiro, lê do mesmo o estado do jogo através da leitura do tabuleiro,
do prompt e da lista de jogadas.
@param e Apontador para o estado
@param nome_ficheiro Apontador para carácter (primeiro caracter do nome do ficheiro)
*/
void ler (ESTADO * e, char * nome_ficheiro);

#endif

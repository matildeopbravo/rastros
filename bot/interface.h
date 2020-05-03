/**
@file interface.h
*/

#ifndef CAMADA_INTERFACE_H
#define CAMADA_INTERFACE_H

/**
\brief Mostra o tabuleiro no ecrã como também o insere num ficheiro quando efetuado o comando "gr".
O tabuleiro é apresentado na stream fornecida como argumento que  será um apontador para um ficheiro ou stdout.
Sempre que efetuamos esse comando "alteramos o tabuleiro", isto é, preenchemos ele do zero, algo que é útil em diversas situações
e potencial de ser reaproveitado tanto para apresentar o tabuleiro após jogadas normais como para apresentar o tabuleiro após um comando
"pos".
@param estado Apontador para o estado
@param stream Apontador para FILE
*/
void mostrar_tabuleiro(ESTADO * estado, FILE * stream);
/**
\brief Função que apresenta o prompt, o qual contém o número do jogador atual,o número e jogadas e o número de comandos efetuados.
@param e Apontador para o estado
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
\brief Função que verifica se o comando escrito pelo utilizador é um dos possíveis de serem feitos
@param token Apontador para caracter
*/
COMANDO verifica_comando( char * token );
/**
\brief Função que guarda o estado atual do tabuleiroe  das jogadas num "estado copia"
@param Apontador para o estado atual
@param Apontador para o estado copia
*/
void guarda_estado(ESTADO * e, ESTADO * copia_estado);
/**
\brief Função que guarda no estado atual o tabuleiro e as jogados do "estado copia"
@param Apontador para o estado atual
@param Apontador para o estado copia
*/
void repor_estado(ESTADO *e, ESTADO * copia_estado); 
/**
\brief Função que guarda no estado atual o tabuleiro e as jogados do "estado copia"
@param Apontador para o estado atual
@param Apontador para o estado copia
@param Token que poderá corresponder ao número da jogada para qual se pretende voltar
*/
int pos(ESTADO * e, ESTADO * copia_estado, char * token);
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
@param nome_ficheiro Apontador para carácter (primeiro carácter do nome do ficheiro)
*/
void gravar (ESTADO * e, char * nome_ficheiro);
/** 
\brief Função que dado um nome de um ficheiro, lê do mesmo o estado do jogo através da leitura do tabuleiro,
do prompt e da lista de jogadas.
@param e Apontador para o estado
@param nome_ficheiro Apontador para carácter (primeiro caracter do nome do ficheiro)
*/
void ler (ESTADO * e, char * nome_ficheiro);
/** 
\brief Função que verifica se um dado carácter, "token", é um digito ou não. Devolve 1 caso for digito, 0 caso contrário.  
@param token Carácter a ser verificado se é digito
*/
int verificanumero (char token);
/** 
\brief Função que preenche o tabuleiro de acordo com as jogadas efetuadas até a n-ésima jogada, onde n é o número
de jogadas atual. Útil utilizá-la sempre que é efetuada uma jogada de modo a se preocupar apenas em alterar o número de jogadas
mediante a necessidade, podendo ser uma função reutilizada tanto para o comando se jogar normal como também após ter sido
efetuado um comando "pos" .
@param estado Appontador para o estado do jogo
*/
void altera_tabuleiro(ESTADO *estado);

/** 
\brief Função de rotina criada pois tais processos feitos por ela é comum a diversas partes do interpretador. É ativada quando
a flag_pos = 1, por tanto há que preparar o código para tais situações de "pos" encadeados. Tal função realiza tais operações de preparação.
@param salva_num_jogadas apontador para um inteiro que representa o número de jogadas salvo na função chamadora
@param salva_jogador_atual apontador para um inteiro que representa o jogador_atual salvo na função chamadora
@param estado Apontador para o estado do jogo
*/
void alterna_situacao_pos (int *salva_num_jogadas, int *salva_jogador_atual, ESTADO *estado);

#endif

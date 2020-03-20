/**
@file dados.h
Definição da Struct principal e protótipos das funções úteis a camada de dados
*/
#ifndef CAMADA_DADOS_H
#define CAMADA_DADOS_H
/**
\brief Tipo de dados para o tipo CASA
*/
typedef enum {UM = '1', DOIS = '2', VAZIO = 0, BRANCA = '*', PRETA = '#'} CASA;
/**
\brief Tipo de dados para o tipo COMANDO
*/
typedef enum {GRAVAR =1 , LER = 2, QUIT = 3, JOG = 4} COMANDO;
/**
\brief Tipo de informação para o tipo COORDENADA
*/
typedef struct {
	int linha;
	int coluna;	
} COORDENADA;
/**
\brief Tipo de dados para o tipo JOGADA
*/
typedef struct {
	COORDENADA jogador1;
	COORDENADA jogador2;
} JOGADA;
/**
\brief Tipo de dados para o tipo JOGADAS
*/
typedef JOGADA JOGADAS[32];
/**
\brief Tipo de dados para o tipo ESTADO - struct principal
*/
typedef struct {
	/** O tabuleiro */
	CASA tab[8][8];
	/** A última jogada */
	COORDENADA ultima_jogada;
	/** O histórico de jogadas*/
	JOGADAS jogadas;
	/** O número de jogadas efetuadas */
	int num_jogadas;
	/** O jogador atual */
	int jogador_atual;
	/** O número de comandos efetuados */
	int num_comandos;
} ESTADO;

/**
\brief Inicializa a struct principal correspondente ao estado do jogo
Isto é, preenche a struct do estado do jogo de forma a representar
o conteúdo do jogo quando se inicia*/
ESTADO * inicializar_estado();
/**
\brief Devolve o jogador atual
@param estado Apontador para o estado
*/
int obter_jogador_atual(ESTADO *estado);
/**
\brief Devolve o numero de jogadas
@param estado Apontador para o estado
*/
int obter_numero_de_jogadas(ESTADO *estado);
/**
\brief Devolve o jogador que jogou a última jogada
@param estado Apontador para o estado
*/
int obter_ultimo_jogador(ESTADO * estado);
/**
\brief Devolve uma jogada dado um índice para procurá-la
@param e Apontador para o estado
@param indice_jogada Indice da jogada a ser procruada
@param jogador jogador que vai ser buscada a jogada
*/
char * obtem_jogada(ESTADO *e, int indice_jogada, int jogador);
/**
\brief Devolve o número de comandos efetuados até então
@param estado Apontador para o estado
*/
int obter_numero_de_comandos(ESTADO *estado);
/**
\brief Dado uma coordenada, devolve a CASA correspondente no tabuleiro
@param e Apontador para o estado
@param c Coordenada
*/
CASA obter_estado_casa(ESTADO *e, COORDENADA c);
/**
\brief Dado uma coordenada e uma CASA, coloca a CASA dada na coordenada do tabuleiro correspondente
@param e Apontador para o estado
@param c Coordenada
@param casa Casa a ser trocada
*/
void altera_casa(ESTADO *e, COORDENADA c, CASA casa);
/**
\brief Dado uma coordenada, altera a última jogada efetuada por esta coordenada
@param e Apontador para o estado
@param c Coordenada
*/
void altera_ultima_jogada(ESTADO * e, COORDENADA c);
/**
\brief Dado um número de jogadas, altera tal componente da struct principal
@param e Apontador para o estado
@param numerojogadas Numero de jogadas a ser trocado
*/
void altera_num_jogadas(ESTADO *e,int numerojogadas);
/**
\brief Dado um jogador, altera a componente de "Jogador atual" da struct principal por esse jogador
@param e Apontador para o estado
@param jogador Jogador a ser colocado na componente de "jogador atual" da struct principal
*/
void altera_jogador_atual(ESTADO *e,int jogador);
/**
\brief Dado um índice e uma jogada, altera o índice correspondente no histórico de jogadas por essa jogada dada.
@param e Apontador para o estado
@param index índice a ser trocado
@param jog Jogada a ser colocada no índice correspondente
*/
void acrescenta_jogada(ESTADO *e, int index, JOGADA jog);
/**
\brief Altera o número de comandos da struct principal
@param e Apontador para o estado
@param numerocomandos Número de comandos a ser posto na struct principal
*/
void altera_numero_comandos(ESTADO *e,int numerocomandos);
/**
\brief Incrementa, em 1, o número de comandos na struct principal
@param e Apontador para o estado
*/
void incrementa_comandos(ESTADO *e);


#endif
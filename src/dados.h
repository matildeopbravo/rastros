/**
@file dados.h
Definição da Struct principal e protótipos das funções úteis a camada de dados
*/
#ifndef CAMADA_DADOS_H
#define CAMADA_DADOS_H

/**
\brief Tipo de dados para o tipo CASA
*/
typedef enum {/** Casa da vitória para o jogador 1 */
	          UM = '1',/** Casa da vitória para o jogador 2 */
              DOIS = '2',/** Casa em que nenhum jogador passou  */
			  VAZIO = 0,/** Casa atual do jogador*/
			  BRANCA = '*',/** Casa que os jogador já passaram*/
			  PRETA = '#',
			  } CASA;
/**
\brief Tipo de dados para o tipo COMANDO
*/
typedef enum {/** Correspondente ao comando gr. Função de salvar a partida*/
	          GRAVAR =1 ,/** Correspondente ao comando lr. Função de carregar partida salva*/ 
			  LER = 2,/** Correspondente ao comando Q.Função de sair da partida*/
			  QUIT = 3, /** Correspondente ao comando jog. Função de mostrar a melhor jogada*/
			  JOG = 4,/** Correspondente a mvoltar a jogar a aprtida a partir de uma jogada anterior*/
			  POS = 5,
              MOVS = 6,
			  JOG2 = 7,
			  } COMANDO;
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
	/** Irá controlar se um novo cenário se iniciou ou não*/
	int flag_pos;
	/** Guarda o número inserido no comando pos*/
	int guarda_num_jogadas_pos;
} ESTADO;

/**
\brief Inicializa a struct principal correspondente ao estado do jogo.
Isto é, preenche a struct do estado do jogo de forma a representar
o conteúdo do jogo quando se inicia*/
ESTADO * inicializar_estado();
/**
\brief Devolve o jogador atual-aquele que irá efetuar a jogada atual.
@param estado Apontador para o estado
*/
int obter_jogador_atual(ESTADO *estado);
/**
\brief Devolve o número de jogadas efetuadas até o preciso momento.
@param estado Apontador para o estado
*/
int obter_numero_de_jogadas(ESTADO *estado);
/**
\brief Devolve o jogador que jogou a última jogada.
@param estado Apontador para o estado
*/
int obter_ultimo_jogador(ESTADO * estado);
/**
\brief Devolve uma jogada dado um índice para procurá-la, no histórico de jogadas, e o jogador correspondente.
@param e Apontador para o estado
@param indice_jogada Indice da jogada a ser procruada
@param jogador jogador que vai ser buscada a jogada
*/
char * obtem_jogada(ESTADO *e, int indice_jogada, int jogador);
/**
\brief Devolve o número de comandos efetuados até então.
@param estado Apontador para o estado
*/
int obter_numero_de_comandos(ESTADO *estado);
/**
\brief Dado uma coordenada, devolve a CASA correspondente no tabuleiro.
@param e Apontador para o estado
@param c Coordenada
*/
CASA obter_estado_casa(ESTADO *e, COORDENADA c);
/**
\brief Dado uma coordenada e uma CASA, coloca a CASA dada na coordenada do tabuleiro correspondente.
@param e Apontador para o estado
@param c Coordenada
@param casa Casa a ser trocada
*/
void altera_casa(ESTADO *e, COORDENADA c, CASA casa);
/**
\brief Dado uma coordenada, altera a última jogada efetuada por esta coordenada.
@param e Apontador para o estado
@param c Coordenada
*/
void altera_ultima_jogada(ESTADO * e, COORDENADA c);
/**
\brief Dado um número de jogadas, altera tal componente da struct principal- útil na leitura de um jogo salvo.
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
\brief Altera o número de comandos da struct principal- útil no carregamento de um jogo salvo.
@param e Apontador para o estado
@param numerocomandos Número de comandos a ser posto na struct principal
*/
void altera_numero_comandos(ESTADO *e,int numerocomandos);
/**
\brief Incrementa, em 1, o número de comandos na struct principal.
@param e Apontador para o estado
*/
void incrementa_comandos(ESTADO *e);
/**
\brief Devolve a última jogada efetuada
@param e Apontador para o estado
*/
COORDENADA obtem_ultima_jogada(ESTADO * e);


COORDENADA obtem_coordenada(ESTADO * e,int indice_jogada, int jogador);

#endif

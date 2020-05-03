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
			  QUIT = 3, /** Correspondente ao comando jog que utiliza o algoritmo da paridade*/
			  JOG = 4,/** Correspondente a voltar a jogar a partida a partir de uma jogada anterior*/
			  POS = 5, /** Correspondente a apresentar as jogas efetuadas ao longo do jogo*/
              MOVS = 6, /** Correspondente ao comando jog2 que utiliza o algoritmo floodfill*/
			  JOG2 = 7,
			  } COMANDO;
/**
\brief Tipo de informação para o tipo COORDENADA
*/
typedef struct {/** Correspondente à linha de uma coordenada */
	int linha; /** Correspondente à coluna de uma coordenada */ 
	int coluna;	
} COORDENADA;
/**
\brief Tipo de dados para o tipo JOGADA
*/
typedef struct {/** Movimento efetuado pelo jogador 1  */
	COORDENADA jogador1; /** Movimento efetuado pelo jogador 2  */
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
    /** Indica se é o bot a realizar a jogada */
    int isBot;
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
\brief Dado uma linha e uma coluna, devolve a CASA correspondente no tabuleiro.
@param e Apontador para o estado
@param linha linha da casa
@param coluna coluna da casa
*/
CASA obter_estado_casa2(ESTADO *e, int linha, int coluna);
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
/**
\brief Devolve uma jogada dado um índice para procurá-la, no histórico de jogadas, e o jogador correspondente.
@param e Apontador para o estado
@param indice_jogada Indice da jogada a ser procruada
@param jogador jogador que vai ser buscada a jogada
*/

COORDENADA obtem_coordenada(ESTADO * e,int indice_jogada, int jogador);
/**
\brief Altera a flag do isBot do estado para o seu contrário 
@param e Apontador para o estado
*/

void altera_isBot(ESTADO * e);

/** 
\brief Função de rotina criada pois tais processos feitos por ela é comum a diversas partes do interpretador. É ativada quando
a flag_pos = 1, por tanto há que preparar o código para tais situações de "pos" encadeados. Tal função realiza tais operações de preparação.
@param salva_num_jogadas apontador para um inteiro que representa o número de jogadas salvo na função chamadora
@param salva_jogador_atual apontador para um inteiro que representa o jogador_atual salvo na função chamadora
@param estado Apontador para o estado do jogo
*/
void alterna_situacao_pos (int *salva_num_jogadas, int *salva_jogador_atual, ESTADO *estado);
/**
\brief Devolve a flag_pos  do estado, dado um estado.
@param e Apontador para o estado
*/

int devolve_flagpos(ESTADO * e);
/**
\brief Altera a flag_pos do estado para o valor dado.
@param e Apontador para o estado
@param valor valor a colocar na flag
*/

void altera_flag(ESTADO * e, int valor);
/**
\brief Altera o jogador atual e o num de jogados de acordo com os argumentos fornecidos.
@param e Apontador para o estado
@param jogador_atual jogador a ser colocado no estado como jogador atual
@param num_jogdas numero a ser colocado no numero de jogadas
*/

void recupera_valores(ESTADO * e, int jogador_atual, int num_jogadas);
/**
\brief Altera o valor do guarda_num_jogadas_pos do estado para o valor dado.
@param e Apontador para o estado
@param valor valor a colocar na flag
*/
void altera_jogadas_pos (ESTADO * e, int valor);
/**
\brief Acrescenta uma coordenada à lista de jogadas 
@param e Apontador para o estado
@param efetuada Coordenada correspondente à jogada efetuada
@param jog Jogador a que realizou a jogada
*/
void acrescenta_coordenada(ESTADO * e, COORDENADA efetuada, int jog);
/**
\brief Devolve a linha de uma coordenada. 
*/
int devolve_linha(COORDENADA c);
/**
\brief Devolve a coluna de uma coordenada. 
*/
int devolve_coluna(COORDENADA c);
/**
\brief Devolve o valor da flag isBot
*/
int devolve_isBot(ESTADO * e); 



#endif

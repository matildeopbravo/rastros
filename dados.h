#ifndef CAMADA_DADOS_H
#define CAMADA_DADOS_H

// Definição de tipos e estruturas

typedef enum {UM = '1', DOIS = '2', VAZIO = 0, BRANCA = '*', PRETA = '#'} CASA;

typedef enum {GRAVAR =1 , LER = 2, QUIT = 3, JOG = 4} COMANDO;

typedef struct {
	int linha;
	int coluna;	
} COORDENADA;

typedef struct {
	COORDENADA jogador1;
	COORDENADA jogador2;
} JOGADA;

typedef JOGADA JOGADAS[32];

typedef struct {
	CASA tab[8][8];
	COORDENADA ultima_jogada;
	JOGADAS jogadas;
	int num_jogadas;
	int jogador_atual;
	int num_comandos;
} ESTADO;

// Protótipos das funções correspondentes à camada de dados.

ESTADO * inicializar_estado();

int obter_jogador_atual(ESTADO *estado);

int obter_numero_de_jogadas(ESTADO *estado);

int obter_ultimo_jogador(ESTADO * estado);

int obtem_ultimo_jog (ESTADO * e);

char * obtem_jogada(ESTADO * e, int indice_jogada, int jogador);

int obter_numero_de_comandos(ESTADO *estado);

CASA obter_estado_casa(ESTADO *e, COORDENADA c);

void altera_casa(ESTADO * e, COORDENADA c, CASA casa);

void altera_ultima_jogada(ESTADO * e, COORDENADA c);

void altera_num_jogadas(ESTADO *e,int numerojogadas);

void altera_jogador_atual(ESTADO *e,int jogador);

void acrescenta_jogada(ESTADO * , int index, JOGADA jog);

void altera_numero_comandos(ESTADO *e,int numerocomandos);

void incrementa_comandos(ESTADO *e);


#endif
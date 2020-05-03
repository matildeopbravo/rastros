#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dados.h"

ESTADO * inicializar_estado(){

    // calloc coloca todos os 'pedacos' de memória a 0, no caso do tabuleiro, 0 = VAZIO. Só resta colocar a peca Branca.
    ESTADO *e = calloc(1, sizeof(ESTADO));
  
    *e =(ESTADO) {
 
    .jogador_atual = 1,
    .num_jogadas = 1,
    .ultima_jogada = (COORDENADA) {3,4},
    .tab[3][4] = BRANCA,
    .tab[0][7] = DOIS,
    .tab[7][0] = UM, 
    };

    return e ;	
}   

int obter_jogador_atual (ESTADO *estado) {

    int j = estado -> jogador_atual ;
    return j ;
}

int obter_ultimo_jogador(ESTADO * estado) {
    return(obter_jogador_atual(estado) == 1 ? 2 : 1);
}

int obter_numero_de_jogadas (ESTADO *estado) {

    int n = estado -> num_jogadas ;
    return n ;
}

int obter_numero_de_comandos(ESTADO *estado){

    int numerocomandos = estado -> num_comandos;
    return numerocomandos;
}

void altera_jogador_atual(ESTADO *e,int jogador){

       e->jogador_atual = jogador;
}

void altera_num_jogadas(ESTADO *e,int numerojogadas){

       e->num_jogadas = numerojogadas;
}

void altera_numero_comandos(ESTADO *e,int numerocomandos){

    e->num_comandos = numerocomandos;
}

CASA obter_estado_casa(ESTADO *e, COORDENADA c) {
    
    int col , l , t ;

    l = c.linha ;
    col = c.coluna ;
    t = e -> tab[l][col] ;

    return t ;
}
CASA obter_estado_casa2(ESTADO *e, int linha, int coluna) {
    return e->tab[linha][coluna];
}

void altera_casa(ESTADO * e, COORDENADA c, CASA casa) {

    e->tab[c.linha][c.coluna] = casa;
}


void altera_ultima_jogada(ESTADO * e, COORDENADA c) {
    e->ultima_jogada = (COORDENADA) {c.linha,c.coluna};
}

COORDENADA obtem_coordenada(ESTADO * e,int indice_jogada, int jogador) {
    JOGADA jog = e->jogadas[indice_jogada];
    COORDENADA c;
    c = jogador == 1 ? jog.jogador1 : jog.jogador2;
    return c;
    
}

void acrescenta_jogada(ESTADO *e , int index, JOGADA jog) {
    e->jogadas[index]=jog;
}

void incrementa_comandos(ESTADO *e){
    
    e->num_comandos = e->num_comandos + 1;

}

COORDENADA obtem_ultima_jogada(ESTADO * e){
    return (e->ultima_jogada);
}

void altera_isBot(ESTADO * e) {
   
   e->isBot = !(e->isBot);
}

int devolve_flagpos(ESTADO * e) {
    return (e->flag_pos);
}


void altera_flag(ESTADO * e, int valor) {
    e->flag_pos = valor;

}
void alterna_situacao_pos (int *salva_num_jogadas, int *salva_jogador_atual, ESTADO *estado){
     *salva_num_jogadas = obter_numero_de_jogadas(estado);
     *salva_jogador_atual =  obter_jogador_atual(estado);
     altera_num_jogadas(estado,estado->guarda_num_jogadas_pos + 1);
     altera_jogador_atual(estado,1);
}    

void recupera_valores(ESTADO * e, int jogador_atual, int num_jogadas) {
    altera_jogador_atual(e,jogador_atual);
    altera_num_jogadas(e, num_jogadas);
}


void altera_jogadas_pos (ESTADO * e, int valor) {
    e->guarda_num_jogadas_pos = valor;
}

void acrescenta_coordenada(ESTADO * e, COORDENADA efetuada, int jog) {
    int num_jogadas = obter_numero_de_jogadas(e); 
    if (jog == 1) {
       e->jogadas[num_jogadas-1].jogador1 = efetuada; 
    }
    else {

       e->jogadas[num_jogadas-1].jogador2 = efetuada; 
    }

}

int devolve_linha(COORDENADA c) {
    return c.linha;
}
int devolve_coluna(COORDENADA c) {
    return c.coluna;
}
int devolve_isBot(ESTADO * e) {
    return e->isBot;
}



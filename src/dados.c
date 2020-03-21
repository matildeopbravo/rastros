#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dados.h"

ESTADO * inicializar_estado(){

    // calloc coloca todos os 'pedacos' de memória a 0, no caso do tabuleiro, 0 = VAZIO. Só resta colocar a peca Branca.
    ESTADO *e = calloc(1, sizeof(ESTADO));
  
    *e =(ESTADO) {
 
    .jogador_atual = 1,
    .num_jogadas = 0,
    .ultima_jogada = (COORDENADA) {3,4},
    .tab[3][4] = BRANCA,
    .tab[0][7] = DOIS,
    .tab[7][0] = UM };

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

char * obtem_jogada(ESTADO * e, int indice_jogada, int jogador) {

   
    char * str = (char*)malloc(3 * sizeof(char));
    COORDENADA c = obtem_coordenada(e,indice_jogada,jogador);
    sprintf(str,"%c%d",c.coluna + 'a',8 - c.linha);
    return(str);

}

void acrescenta_jogada(ESTADO *e , int index, JOGADA jog) {
    e->jogadas[index]=jog;
}

void incrementa_comandos(ESTADO *e){
    
    e->num_comandos = e->num_comandos + 1;

}

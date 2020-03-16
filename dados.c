#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dados.h"

ESTADO *inicializar_estado(){

    // calloc coloca todos os 'pedacos' de memória a 0, no caso do tabuleiro, 0 = VAZIO. Só resta colocar a peca Branca.
    ESTADO *e = calloc(1, sizeof(ESTADO)); 
    e->jogador_atual = 1;
    e->num_jogadas = 0;
    e->ultima_jogada = (COORDENADA) {3,4};
    e->tab[3][4] = BRANCA;
    e->tab[0][7] = DOIS;
    e->tab[7][0] = UM;
	return e ;	
}   

int obter_jogador_atual (ESTADO *estado) {

    int j = estado -> jogador_atual ;
    return j ;
}

int obter_numero_de_jogadas (ESTADO *estado) {

    int n = estado -> num_jogadas ;
    return n ;
}

CASA obter_estado_casa(ESTADO *e, COORDENADA c) {
    
    int col , l , t ;

    l = c.linha ;
    col = c.coluna ;
    t = e -> tab[l][col] ;

    return t ;
}
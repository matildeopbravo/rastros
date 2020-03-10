#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dados.h"

ESTADO *inicializar_estado(){

    ESTADO * novo =  malloc (sizeof(ESTADO));

    *novo = (ESTADO){
        .tab = {{VAZIO, VAZIO, VAZIO, VAZIO, VAZIO, VAZIO, VAZIO, VAZIO},
        {VAZIO, VAZIO, VAZIO, VAZIO, VAZIO, VAZIO, VAZIO, VAZIO},
        {VAZIO, VAZIO, VAZIO, VAZIO, VAZIO, VAZIO, VAZIO, VAZIO},
        {VAZIO, VAZIO, VAZIO, VAZIO, BRANCA, VAZIO, VAZIO, VAZIO},
        {VAZIO, VAZIO, VAZIO, VAZIO, VAZIO, VAZIO, VAZIO, VAZIO},
        {VAZIO, VAZIO, VAZIO, VAZIO, VAZIO, VAZIO, VAZIO, VAZIO},
        {VAZIO, VAZIO, VAZIO, VAZIO, VAZIO, VAZIO, VAZIO, VAZIO},
        {VAZIO, VAZIO, VAZIO, VAZIO, VAZIO, VAZIO, VAZIO, VAZIO}},
		.ultima_jogada ={4,3},
        .jogadas = {},  
        .num_jogadas = 0,
        .jogador_atual = 0};
	return (novo);	

}   

void coloca_branca(ESTADO * estado ) {
	COORDENADA jogada =  estado -> ultima_jogada; 
	estado -> tab[jogada.linha][jogada.coluna] = BRANCA;
}

int obter_jogador_atual (ESTADO *estado) {
    int j ;
    j = (*estado).jogador_atual ;
    return j ;
}

int obter_numero_de_jogadas (ESTADO *estado) {
    int n;
    n = (*estado).num_jogadas ;
    return n ;
}

int obter_estado_casa(ESTADO *e, COORDENADA c) {
    int col , l , t ;

    l = c.linha ;
    col = c.coluna ;
    t = (*e).tab[l][col] ;

    return t ;
}
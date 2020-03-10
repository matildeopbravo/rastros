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

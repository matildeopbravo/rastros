#include <stdio.h>
#include "dados.h"
#include "logica.h"
#include <string.h>
#define BUF_SIZE 1024

void printarcampeao(ESTADO * estado){
    
    COORDENADA ultimajogada;  
    ultimajogada  = (estado -> ultima_jogada);
    int linha,coluna;

    linha = ultimajogada.linha;
    coluna = ultimajogada.coluna;

     if ( linha == 7 && coluna == 0 ) 
     printf ( "Parabéns jogador 1, é o vencedor deste jogo!!!! \n");
     else
     {
    printf ( "Parabéns jogador 2, é o vencedor deste jogo!!!! \n");
     }
     
}


void prompt (ESTADO * estado){
    int jogadoratual;
    int numerojogadas;   // Cada vez que uma rodada e jogadas acontece (ambos jogam) o numero de jogadas aumenta

    jogadoratual = estado -> jogador_atual;
    numerojogadas = estado -> num_jogadas;

    printf ("-> Player nº %d | Jogada nº %d > ", jogadoratual,numerojogadas);    

}

void mostrar_tabuleiro(ESTADO * estado) {
    int i , j ;

    for ( i = 0 ; i < 8 ; i++ ) {
        printf ("%d ", 8 - i);         // Printa o número de cada linha na tela
        for ( j = 0 ; j < 8 ; j++ ) {
            if ( i == 0 && j == 7 ) 
                putchar ((obter_estado_casa(estado, (COORDENADA){i,j})) == VAZIO ? '2' : '#') ;
            else if  ( i == 7 && j == 0 ) 
                putchar ((obter_estado_casa(estado, (COORDENADA){i,j})) == VAZIO ? '1' : '#') ;
            else {
                if ((obter_estado_casa(estado, (COORDENADA){i,j})) == VAZIO) putchar ('.') ;
                else if ((obter_estado_casa(estado, (COORDENADA){i,j})) == BRANCA ) putchar ('*') ;
                else putchar ('#') ;
            }
            
            }
        printf ("\n") ;
    }
 printf ("  abcdefgh\n");    
        
}

int interpretador(ESTADO *e) {
    char linha[BUF_SIZE];
    char col[2], lin[2];
    int t =0;

    mostrar_tabuleiro(e);

    while(t != 2) { // enquanto t for 0;
        prompt (e);
        if (fgets(linha, BUF_SIZE, stdin) == NULL)
            return 0;
        
        if (strlen(linha) == 3 && sscanf(linha, "%[a-h]%[1-8]", col, lin) == 2) {
            COORDENADA coord = { '8' - *lin , *col -'a'};
            t = jogar ( e , coord );
            mostrar_tabuleiro(e);
        }
  
    }

    printarcampeao(e); 
    
    return 1;
}

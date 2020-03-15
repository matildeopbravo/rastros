#include <stdio.h>
#include "dados.h"
#include "logica.h"
#include <string.h>
#define BUF_SIZE 1024

void mostrar_tabuleiro(ESTADO * estado) {
    int i , j ;

    for ( i = 0 ; i < 8 ; i++ ) {
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
        
}

int interpretador(ESTADO *e) {
    char linha[BUF_SIZE];
    char col[2], lin[2];
   // int * fim;
 //   *fim = 0;
    int t =0;

    while( !t) {
        if (fgets(linha, BUF_SIZE, stdin) == NULL)
            return 0;
        
        if (strlen(linha) == 3 && sscanf(linha, "%[a-h]%[1-8]", col, lin) == 2) {
            COORDENADA coord = { '8' - *lin , *col -'a'};
            t = jogar ( e , coord );
            mostrar_tabuleiro(e);
        }
  
    } 
    
    return 1;
}

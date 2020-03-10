#include <stdio.h>
#include "dados.h"

//oi
void mostrar_tabuleiro(ESTADO * estado) {
    int i , j ;

    for ( i = 0 ; i < 8 ; i++ ) {
        for ( j = 0 ; j < 8 ; j++ ) {
            if ( i == 0 && j == 7 ) putchar ((*estado).tab[i][j] == VAZIO ? '2' : '#') ;
            else if  ( i == 7 && j == 0 ) putchar ((*estado).tab[i][j] == VAZIO ? '1' : '#') ;
            else {
                if ((*estado).tab[i][j] == VAZIO) putchar ('.') ;
                else if ((*estado).tab[i][j] == BRANCA ) putchar ('*') ;
                else putchar ('#') ;
            }
            
        }

        printf ("\n") ;
    }
        
}


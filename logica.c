#include <stdio.h>
#include <stdlib.h>
#include "dados.h"

int evalida ( ESTADO *e , COORDENADA c1 , COORDENADA c2 ) {
    int l1 , l2 , col1 , col2 , r = 0;

    l1 = c1.linha ;
    col1 = c1.coluna ;

    l2 = c2.linha ;
    col2 = c2.coluna ;

    if ( obter_estado_casa ( e , c2 ) == VAZIO )
        if ( abs( col1 - col2 ) <= 1 && abs( l1 - l2 ) <= 1 )
            r = 1;

    return r;

}

int fim ( ESTADO *e , int l , int c , int j ) {

    if ( (*e).ultima_jogada.linha == 7 && (*e).ultima_jogada.coluna == 0 ) return 2 ;

    if ( (*e).ultima_jogada.linha == 0 && (*e).ultima_jogada.coluna == 7 ) return 1 ;

    if ( l == 0 ) {
        if ( c == 0 )
            return j ;
        if ( (*e).tab[l][c-1]   == 2 
          && (*e).tab[l][c+1]   == 2 
          && (*e).tab[l+1][c-1] == 2 
          && (*e).tab[l+1][c]   == 2 
          && (*e).tab[l+1][c+1] == 2 )
            return j ;
    }

    if ( l == 7 ) {
        if ( c == 7 )
            return j ;
        if ( (*e).tab[l][c-1]   == 2 
          && (*e).tab[l][c+1]   == 2 
          && (*e).tab[l-1][c-1] == 2 
          && (*e).tab[l-1][c]   == 2 
          && (*e).tab[l-1][c+1] == 2 )
            return j ;
    }

    if ( c == 0 ) 
        if ( (*e).tab[l-1][c]   == 2 
          && (*e).tab[l+1][c]   == 2 
          && (*e).tab[l+1][c+1] == 2 
          && (*e).tab[l][c+1]   == 2 
          && (*e).tab[l-1][c+1] == 2 )
            return j ;

    if ( c == 7 ) 
        if ( (*e).tab[l-1][c]   == 2 
          && (*e).tab[l+1][c]   == 2 
          && (*e).tab[l+1][c-1] == 2 
          && (*e).tab[l][c-1]   == 2 
          && (*e).tab[l-1][c-1] == 2 )
            return j ;

    if ( (*e).tab[l-1][c]   == 2 
      && (*e).tab[l+1][c]   == 2 
      && (*e).tab[l+1][c-1] == 2 
      && (*e).tab[l][c-1]   == 2 
      && (*e).tab[l-1][c-1] == 2 
      && (*e).tab[l+1][c+1] == 2 
      && (*e).tab[l][c+1]   == 2 
      && (*e).tab[l-1][c+1] == 2 )
        return j ;

    return 0 ;

}

int jogar( ESTADO *e , COORDENADA c ) {
    int l1 , l2 , col1 , col2 , t , nj , jog ;
    COORDENADA uj ;

    uj = e -> ultima_jogada ;

    l1 = uj.linha ;
    col1 = uj.coluna ;

    l2 = c.linha ;
    col2 = c.coluna ;

    jog = e -> jogador_atual ;

    if ( evalida ( e , uj , c ) ) {
        
        printf("jogar %d %d\n", col2 , l2 );
        
        (*e).tab[l1][col1] = PRETA ;
        (*e).tab[l2][col2] = BRANCA ;
        (*e).ultima_jogada = c ;

        nj = e -> num_jogadas ;

        if ( obter_jogador_atual (e) == 1 ) {
            (*e).jogadas[nj].jogador1 = c ;
            e -> jogador_atual = 2 ;
        }
        else {
            (*e).jogadas[nj-1].jogador2 = c ;
            e -> jogador_atual = 1 ;
            nj++ ;
        }
            
        t = fim ( e , l2 , col2 , jog ) ;

        if ( t != 0 )
            printf ( "Parabéns jogador %d, é o vencedor deste jogo!!!! \n" , t ) ;
            
        return 1;
    }

    else {
       printf ( "A jogada não é válida, tente novamente! \n") ;
       return 0 ;
    } 
}
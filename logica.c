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
int n = 0;
int jogar( ESTADO *e , COORDENADA jog_efet ) {
 

    COORDENADA jog_ant = e->ultima_jogada;
    int lin_atual =  jog_ant.linha ;
    int col_atual = jog_ant.coluna ;

    int prox_lin = jog_efet.linha ;
    int prox_col = jog_efet.coluna ;
    int num_jogadas = obter_numero_de_jogadas(e);
  

    if (evalida ( e , jog_ant , jog_efet ) ) {
        
        printf("jogar %d %d\n", prox_col , prox_lin);
        
        e->tab[lin_atual][col_atual] = PRETA ;
        e->tab[prox_lin][prox_col] = BRANCA ;
        e-> ultima_jogada = jog_efet ;
      

        if ( obter_jogador_atual (e) == 1 ) {
            e->jogadas[num_jogadas].jogador1 = jog_efet ;
            e -> jogador_atual = 2 ;
        }
        else {
            e->jogadas[num_jogadas -1].jogador2 = jog_efet ;
            e -> jogador_atual = 1 ;
            e->num_jogadas++;
        
        }
        
        
        int t = fim ( e , prox_lin , prox_col , obter_jogador_atual(e));
        if (t)
            printf ( "Parabéns jogador %d, é o vencedor deste jogo!!!! \n" ,t) ;
            
        return 1;
        
    }

    else {
       printf ( "A jogada não é válida, tente novamente! \n") ;
       return 0 ;
    } 
}
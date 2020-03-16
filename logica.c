#include <stdio.h>
#include <stdlib.h>
#include "dados.h"


int verifica_valida ( ESTADO *e , COORDENADA jog_ant , COORDENADA jog_efet) {

    int r = 0;

    if ( obter_estado_casa ( e , jog_efet ) == VAZIO 
        && abs( jog_ant.coluna - jog_efet.coluna ) <= 1 
        && abs( jog_ant.linha - jog_efet.linha ) <= 1 ) {
               r = 1;
        }
    return r;
}

int verifica_fim ( ESTADO *e , int l , int c, int j ) {

    if ( l == 7 && c == 0 ) return 1 ;
    if ( l == 0 && c == 7 ) return 2 ;
 
    // Caso em que o jogador está no canto superior esquerdo
    if ( l == 0 && c == 0 ) {      
        if ( e->tab[l][c+1]   == PRETA 
          && e->tab[l+1][c]   == PRETA 
          && e->tab[l+1][c+1] == PRETA )
        return j ;}

     // Caso em que o jogador está no canto inferior direito
    if ( l == 7 && c == 7 ) {      
        if ( e->tab[l-1][c]   == PRETA 
          && e->tab[l][c-1]   == PRETA 
          && e->tab[l-1][c-1] == PRETA )
        return j ;}    

    if ( l == 0 ) {
        if ( e->tab[l][c-1]   == PRETA 
          && e->tab[l][c+1]   == PRETA 
          && e->tab[l+1][c-1] == PRETA 
          && e->tab[l+1][c]   == PRETA 
          && e->tab[l+1][c+1] == PRETA )
            return j ;
    }

    if ( l == 7 ) {
        if ( e->tab[l][c-1]   == PRETA 
          && e->tab[l][c+1]   == PRETA 
          && e->tab[l-1][c-1] == PRETA 
          && e->tab[l-1][c]   == PRETA 
          && e->tab[l-1][c+1] == PRETA )
            return j ;
    }

    if ( c == 0 ) 
        if ( e->tab[l-1][c]   == PRETA 
          && e->tab[l+1][c]   == PRETA 
          && e->tab[l+1][c+1] == PRETA 
          && e->tab[l][c+1]   == PRETA 
          && e->tab[l-1][c+1] == PRETA )
            return j ;

    if ( c == 7 ) 
        if ( e->tab[l-1][c]   == PRETA 
          && e->tab[l+1][c]   == PRETA 
          && e->tab[l+1][c-1] == PRETA 
          && e->tab[l][c-1]   == PRETA 
          && e->tab[l-1][c-1] == PRETA )
            return j ;

    if ( e->tab[l-1][c]   == PRETA 
      && e->tab[l+1][c]   == PRETA 
      && e->tab[l+1][c-1] == PRETA 
      && e->tab[l][c-1]   == PRETA 
      && e->tab[l-1][c-1] == PRETA 
      && e->tab[l+1][c+1] == PRETA 
      && e->tab[l][c+1]   == PRETA 
      && e->tab[l-1][c+1] == PRETA )
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
  

    if (verifica_valida ( e , jog_ant , jog_efet ) ) {
        
        printf("jogar %d %d\n", prox_col , prox_lin);
        
        e->tab[lin_atual][col_atual] = PRETA ;
        e->tab[prox_lin][prox_col] = BRANCA ;
        e-> ultima_jogada = jog_efet ;

        int t = verifica_fim ( e , prox_lin , prox_col , obter_jogador_atual(e));
        // Condição para verificar se há um ganhador
        if (t) return 2;
                 
        if ( obter_jogador_atual (e) == 1 ) {
            e->jogadas[num_jogadas].jogador1 = jog_efet ;
            e -> jogador_atual = 2 ;
            e->num_jogadas++;
        }
        else {
            e->jogadas[num_jogadas -1].jogador2 = jog_efet ;
            e -> jogador_atual = 1 ;
 
        }
        
    return 1;   
    }

    else {
       printf ( "A jogada não é válida, tente novamente! \n") ;
       return 0 ;
    } 
}
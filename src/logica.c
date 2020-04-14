#include <stdio.h>
#include <stdlib.h>
#include "dados.h"
#include "listas.h"

//-------------------------------------estrategias comando jog--------------------------------------

// CALCULA A ÁREA RESTANTE SIMULADA A PARTIR DE UMA POSSÍVEL JOGADA
int calculaarea(COORDENADA * possiveljogada, ESTADO * e){ // O ARGUMENTO É A COORDENADA DA POSSÍVEL JOGADA
    COORDENADA coordvizinha;
    int area = 0;


    for (int i = -1 ;i <= 1;i++){
        for (int j = -1;j <= 1;j++){ 
            
        coordvizinha.linha = ((*possiveljogada).linha) + i;
        coordvizinha.coluna = ((*possiveljogada).coluna) + j;

        if ((obter_estado_casa(e,coordvizinha) == VAZIO)
        && (coordvizinha.linha >= 0)
        && (coordvizinha.linha <= 7)
        && (coordvizinha.coluna >= 0)
        && (coordvizinha.coluna <= 7))
           {
            area++;
            altera_casa(e,(COORDENADA){(*possiveljogada).linha,(*possiveljogada).coluna}, PRETA);
            altera_casa(e,(COORDENADA){coordvizinha.linha,coordvizinha.coluna}, BRANCA);// SIMBOLICO
            altera_casa(e,(COORDENADA){coordvizinha.linha,coordvizinha.coluna}, PRETA);
            area += calculaarea(&coordvizinha,e);
        }
      }
    } 


return area;
}

void auxiliarparidade (ESTADO *e,LISTA posicoesvazias,int paridade[8],COORDENADA *cabeca){
   CASA tabcopia[8][8];
   int cont = 0;  
    
    while (posicoesvazias != NULL) {

         for (int i= 0; i < 8; i++){
          for (int j = 0; j < 8; j++){   
               tabcopia[i][j] = e->tab[i][j]; 
             } 
          } 
     
        cabeca = devolve_cabeca(posicoesvazias);
        printf("%c%d\n",(*cabeca).coluna + 'a',8 - (*cabeca).linha); 
          altera_casa(e,(COORDENADA){(e->ultima_jogada).linha,(e->ultima_jogada).coluna}, PRETA);
          altera_casa(e,(COORDENADA){(*cabeca).linha,(*cabeca).coluna}, BRANCA);
        paridade[cont] = calculaarea((posicoesvazias->valor),e);
        printf("Área : %d\n",paridade[cont]);
        cont++;
        posicoesvazias = posicoesvazias->prox;
        
        // DEVO VOLTAR O TABUELIRO ANTIGO
        for (int i= 0; i < 8; i++){
                        for (int j = 0; j < 8; j++){
                            e->tab[i][j] = tabcopia[i][j];
      }
     }
    }

}


COORDENADA estrategiaparidade(ESTADO *e){
    
    LISTA posicoesvazias;
    posicoesvazias = criar_lista(); // LISTA LIGADA QUE VAI ARMAZENAR AS POSIÇÕES VAZIAS POSSÍVEIS DE EFETUAR UMA JOGADA
    COORDENADA coordvizinha[8]; 

    COORDENADA coordaserjogada;
    COORDENADA *cabeca;
    int paridade[8];
    
    LISTA guardalista;
    guardalista = criar_lista();
    guardalista = posicoesvazias; 
           
    for (int i = 0;i< 9;i++)
         paridade[i]= 1;
   

// CICLO QUE VAI ANALISAR QUAIS DAS POSIÇÕES VIZINHAS ESTÃO VAZIAS e ARMAZENAR ELAS NA LISTA LIGADA
// CRIADA PARA ESSE FIM.
int h = 0;
    for (int i = -1 ;i <= 1;i++){
        for (int j = -1;j <= 1;j++,h++){
            
            coordvizinha[h].linha = ((e->ultima_jogada).linha) + i;
            coordvizinha[h].coluna = ((e->ultima_jogada).coluna) + j;

            if ((obter_estado_casa(e,coordvizinha[h]) == VAZIO)
            && (coordvizinha[h].linha >= 0)
            && (coordvizinha[h].linha <= 7)
            && (coordvizinha[h].coluna >= 0)
            && (coordvizinha[h].coluna <= 7)){
            posicoesvazias = insere_cabeca(posicoesvazias, &(coordvizinha[h]));;
            }
              
        }
    }

    auxiliarparidade(e,posicoesvazias,paridade,cabeca);


    //CICLO PARA DECIDIR A JOGADA PAR A EFETUAR (SE TIVER MAIS DE UMA SERÁ ESCOLHIDA A MENOR)
    int resultado = 65; // NADA É MAIOR QUE ISSO
    int indicedajogadaaefetuar = 9;
        for (int i = 0; i <8;i++){
            printf("cheguei %d \n",i); 
            if (paridade[i] % 2 == 0 && paridade[i] < resultado){
            indicedajogadaaefetuar = i;
            resultado = paridade[i];
            }
            printf("cheguei %d \n",i); 
        }
          printf("%d\n ",indicedajogadaaefetuar); 
        
        if (indicedajogadaaefetuar == 9){
          resultado = 0;
          for (int i = 0; i < 8;i++){
            if (paridade[i] > resultado)
            indicedajogadaaefetuar = i;
            resultado = paridade[i];
        }

        }   

        printf("%d",indicedajogadaaefetuar);  

         for (int i = indicedajogadaaefetuar; i >= 0;i--,posicoesvazias = posicoesvazias->prox){
             if (i == 0)
             cabeca = devolve_cabeca(posicoesvazias);        
             coordaserjogada = *cabeca;
         }
 
         return (coordaserjogada);
}



// --------------------------------------------------------------------------------------------------

int verifica_valida ( ESTADO *e , COORDENADA jog_ant , COORDENADA jog_efet) {

    int r = 0;

    int linhajogefet = jog_efet.linha;
    int linhajogant = jog_ant.linha;
    int coljogefet = jog_efet.coluna;
    int coljogant = jog_ant.coluna;

    if ((obter_estado_casa ( e , jog_efet ) != PRETA)  
        && abs( jog_ant.coluna - jog_efet.coluna ) <= 1 
        && abs( jog_ant.linha - jog_efet.linha ) <= 1 
        && ((coljogant != coljogefet)
        || (linhajogant != linhajogefet)))
        {
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
        
        printf("\njogar %d %d\n\n", prox_col , prox_lin);

        altera_casa(e,(COORDENADA){lin_atual, col_atual}, PRETA);
        altera_casa(e,(COORDENADA){prox_lin,prox_col}, BRANCA);
        altera_ultima_jogada(e,jog_efet);

        int t = verifica_fim ( e , prox_lin , prox_col , obter_jogador_atual(e));
        // Condição para verificar se há um ganhador
        if (t) return 2;
                 
        if ( obter_jogador_atual (e) == 1 ) {
            
            e->jogadas[num_jogadas-1].jogador1 = jog_efet ;
            e -> jogador_atual = 2 ;
            
        }
        else {
            e->jogadas[num_jogadas-1].jogador2 = jog_efet ;
            e -> jogador_atual = 1 ;
            e->num_jogadas++;
 
        }

    return 1;   
    }

    else {
       printf ( "A jogada não é válida, tente novamente! \n") ;
       return 0 ;
    } 
}
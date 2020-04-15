#include <stdio.h>
#include <stdlib.h>
#include "dados.h"
#include "listas.h"

/*------------------Funções correspondentes a estratégia Paridade----------------------------------*/

int aux_1_indice(ESTADO * e,int paridade[8]){
    int resultado = 65; /*inicialização da variável com uma quantidade que eu evite ser aleatória e
    é de nosso conhecimento que nenhuma área será maior que isso*/
    int indicedajogadaaefetuar = 9;/*inicialização análoga a anterior porém com índices. Servirá para
    indicar que, caso sair do pŕoximo ciclo for e continuar sendo 9 o valor de tal variável, então
    não há jogadas com área par para efetuar e por tanto devo escolher uma com área ímpar*/
    /*Ciclo que escolhe a menor área par do array*/    
        for (int i = 0; i <8;i++){
              if (paridade[i] % 2 == 0 && paridade[i] <= resultado){
            indicedajogadaaefetuar = i;
            resultado = paridade[i];
            }
        }
        /*Situação em que não existem jogadas com área restante par.
        Por tanto devo jogar para a MAIOR área ímpar(dado que diminuirá
        as probabilidades de eu ser encurralado)* pois a longo prazo
        o cenário pode mudar*/
        if (indicedajogadaaefetuar == 9){
          resultado = 0;
          for (int i = 0; i < 8;i++){
            if (paridade[i] >= resultado)
            indicedajogadaaefetuar = i;
            resultado = paridade[i];
           }
         }   
return indicedajogadaaefetuar;
}

int aux_2_indice(ESTADO * e,int paridade[8]){
    int resultado = 65; /*inicialização da variável com uma quantidade que eu evite ser aleatória e
    é de nosso conhecimento que nenhuma área será maior que isso*/
    int indicedajogadaaefetuar = 9;/*inicialização análoga a anterior porém com índices. Servirá para
    indicar que, caso sair do pŕoximo ciclo for e continuar sendo 9 o valor de tal variável, então
    não há jogadas com área par para efetuar e por tanto devo escolher uma com área ímpar*/
    /*Ciclo que escolhe a menor área par do array*/    
        for (int i = 0; i <8;i++){
              if (paridade[i] % 2 == 0 && paridade[i] < resultado){
            indicedajogadaaefetuar = i;
            resultado = paridade[i];
            }
        }
        /*Situação em que não existem jogadas com área restante par.
        Por tanto devo jogar para a MAIOR área ímpar(dado que diminuirá
        as probabilidades de eu ser encurralado)* pois a longo prazo
        o cenário pode mudar*/
        if (indicedajogadaaefetuar == 9){
          resultado = 0;
          for (int i = 0; i < 8;i++){
            if (paridade[i] > resultado)
            indicedajogadaaefetuar = i;
            resultado = paridade[i];
           }
         }   
return indicedajogadaaefetuar;
}

/*Devolve o índice escolhida da melhor jogada a efetuar*/
int  jogadaaefetuar(ESTADO * e,int paridade[8]){
    int indice_jogada_a_efetuar;

    if (e->jogador_atual == 1)
    indice_jogada_a_efetuar = aux_1_indice(e,paridade);
    else 
    indice_jogada_a_efetuar =  aux_2_indice(e,paridade); 
   
return indice_jogada_a_efetuar;
}

/* Calcula A ÁREA RESTANTE simulada a partir de uma POSSÍVEL JOGADA*/
int calcula_area(COORDENADA * possiveljogada, ESTADO * e){ 
    COORDENADA coordvizinha;
    int area = 0;

    for (int i = 1 ;i >= -1;i--){
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
            altera_casa(e,(COORDENADA){coordvizinha.linha,coordvizinha.coluna}, BRANCA);// simbólico
            altera_casa(e,(COORDENADA){coordvizinha.linha,coordvizinha.coluna}, PRETA);
            area += calcula_area(&coordvizinha,e);
        }
      }
    } 

return area;
}

/*Função auxiliar da "estrategia_paridade" que preenche o array paridade(que armazena a área restante para cada possível 
jogada) com as respetivas áreas de cada possível jogada*/
void auxiliarparidade (ESTADO *e,LISTA posicoesvazias,int paridade[8],COORDENADA *cabeca){
   CASA tabcopia[8][8];//matriz auxiliar criada de forma a não ser perdido o conteúdo do tabuleiro inicial
   int cont = 0; 

   printf("\n->Área que sobra mediante cada possível jogada\n") ;
   
    while (posicoesvazias != NULL) {

         for (int i= 0; i < 8; i++){
          for (int j = 0; j < 8; j++){   
               tabcopia[i][j] = e->tab[i][j]; 
             } 
          } 
        cabeca = devolve_cabeca(posicoesvazias);
        printf("%c%d -> ",(*cabeca).coluna + 'a',8 - (*cabeca).linha); 
          altera_casa(e,(COORDENADA){(e->ultima_jogada).linha,(e->ultima_jogada).coluna}, PRETA);
          altera_casa(e,(COORDENADA){(*cabeca).linha,(*cabeca).coluna}, BRANCA);
        paridade[cont] = calcula_area((posicoesvazias->valor),e);

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

/* Função Principal da heurística da Paridade*/
//Devolve a melhor jogada possível;
COORDENADA estrategia_paridade(ESTADO *e){
    
    LISTA posicoesvazias;//lista ligada que armazena as possíveis jogadas
      posicoesvazias = criar_lista(); 
    COORDENADA coordvizinha[8];//array que vai auxiliar no preenchimento da lista acima
    COORDENADA coordaserjogada;//coordenada escolhida resultado de aplicar a função
    COORDENADA *cabeca;//apontador auxiliar para retirar o conteúdo do apontador void da lista ligada
    int paridade[8] =  {1,1,1,1,1,1,1,1,};//array que armazena a área restante para cada possível jogada
    /* o array acima é inicializado com 1 para efeitos no momento de desprezar certas jogadas   

/* ciclo que vai analisar quais das POSIÇÕES VIZINHAS estão VAZIAS e armazená-las na LISTA ligada
criada para esse fim */
  
    int h = 0;
    for (int i = 1 ;i >= -1;i--){
        for (int j = -1;j <= 1;j++,h++){
            
            coordvizinha[h].linha = ((e->ultima_jogada).linha) + i;
            coordvizinha[h].coluna = ((e->ultima_jogada).coluna) + j;

            if (((obter_estado_casa(e,coordvizinha[h]) == VAZIO)
                 ||(obter_estado_casa(e,coordvizinha[h]) == UM)
                 || (obter_estado_casa(e,coordvizinha[h]) == DOIS))
                 && ((coordvizinha[h].linha >= 0)
                    && (coordvizinha[h].linha <= 7)
                    && (coordvizinha[h].coluna >= 0)
                    && (coordvizinha[h].coluna <= 7))) 
                     {
            posicoesvazias = insere_cabeca(posicoesvazias, &(coordvizinha[h]));
            }              
        }
    }

    /*Função auxiliar que preenche o array paridade com as respetivas áreas de cada possível jogada*/
    auxiliarparidade(e,posicoesvazias,paridade,cabeca);
    /*Função auxiliar que devolverá o índice do array paridade escolhido. Como o array paridade
    possui as áreas respetivas de cada possível jogada, o índice escolhido estará de acordo com
    a posição da jogada na lista ligada*/
    int indice_da_jogada_escolhida;
    indice_da_jogada_escolhida = jogadaaefetuar(e,paridade);     
         
    /*Mediante o índice escolhido na função anterior, será então retirada a melhor jogada possível
    na lista ligada*/
    for (int i = indice_da_jogada_escolhida; i >= 0;i--,posicoesvazias = posicoesvazias->prox){
        if (i == 0)
             cabeca = devolve_cabeca(posicoesvazias);        
             coordaserjogada = *cabeca;
         }
         printf("\n->Jogada escolhida a partir da heurística da paridade : %c%d  ",(*cabeca).coluna + 'a',8 - (*cabeca).linha); 

         return (coordaserjogada);
}

/*-------------------------------------------------------------------------------------------------------------*/

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
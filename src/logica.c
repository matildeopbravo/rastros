#include <stdio.h>
#include <stdlib.h>
#include "dados.h"
#include "listas.h"


COORDENADA insere_possiveis_jogadas ( ESTADO *e , LISTA *posicoesvazias,COORDENADA coord_escolhida ) {

    COORDENADA coordvizinha[8];//array que vai auxiliar no preenchimento da lista acima
 
    int h = 0;
    for (int i = 1 ;i >= -1;i--){
        for (int j = -1;j <= 1;j++,h++){
            
            coordvizinha[h].linha = ((e->ultima_jogada).linha) + i;
            coordvizinha[h].coluna = ((e->ultima_jogada).coluna) + j;
             
            /* Este primeiro if é a situação de preenchimento normal*/
            if ((obter_estado_casa(e,coordvizinha[h]) == VAZIO)
                 && (coordvizinha[h].linha >= 0) && (coordvizinha[h].linha <= 7)
                 && (coordvizinha[h].coluna >= 0) && (coordvizinha[h].coluna <= 7))
               {
                    *posicoesvazias = insere_cabeca(*posicoesvazias, &(coordvizinha[h]));
                    printf("Possível jogada: %c%d\n", coordvizinha[h].coluna + 'a',8 -  coordvizinha[h].linha);
               }
            /* Este if analisa uma das situações de prioridade MÀXIMA- VITÓRIA
            O ciclo deve ser interrompido dado que já achamos a jogada*/
            if ((e->jogador_atual == 1 )
                && (obter_estado_casa(e,coordvizinha[h]) == UM)
                && (coordvizinha[h].linha >= 0)  && (coordvizinha[h].linha <= 7)
                && (coordvizinha[h].coluna >= 0) && (coordvizinha[h].coluna <= 7))
               {
                coord_escolhida = coordvizinha[h];
                j = 1;
                i = -1;
               }

            /* Este if analisa a outra situações de prioridade MÀXIMA- VITÓRIA
            O ciclo deve ser interrompido dado que já achamos a jogada*/
            if ((e->jogador_atual == 2 
                &&   obter_estado_casa(e,coordvizinha[h]) == DOIS)
                && (coordvizinha[h].linha >= 0) && (coordvizinha[h].linha <= 7)
                && (coordvizinha[h].coluna >= 0) && (coordvizinha[h].coluna <= 7))
               {
                coord_escolhida = coordvizinha[h];
                j = 1;
                i = -1;
               }
         }
    }

    return coord_escolhida;
}

/*------------------Funções correspondentes a estratégia Floodfill---------------------------------*/

COORDENADA aux ( int f1 , LISTA l , int num_casa[8][8]){
    
    COORDENADA coor_final;
    COORDENADA * cabeca ;
    cabeca = devolve_cabeca(l);
    
    while ( num_casa[cabeca->linha][cabeca->coluna] != (f1 - 1)) {
   
        l = proximo(l);
        cabeca = devolve_cabeca (l) ;
    }

    coor_final = *cabeca ;
    return coor_final;
}

// Temos a coordenada t. Queremos saber se a CASA no tabuleiro correspondente a essa coordenada t
// está ao lado de alguma com valor n-1. Para isso corremos todas as posições do tabuleiro até 
// encontrarmos alguma ao lado da coordenada que temos ou chegarmos ao fim do tabuleiro.

int eaolado ( COORDENADA t , int num_casa[8][8] , int n ) {                 
    int f = 0 ;// flag que será usada no ciclo
    int l = 0 , c = 0 ; // primeira posição do tabuleiro é linha 0 coluna 0

    while ( f == 0 ) {
        if (c == 7 && l == 7) // verificamos se chegou ao fim do tabuleiro.Se isso acontecer, mudamos a flag,
            f = 2 ;          //  parando o ciclo e informando que não está ao lado de nenhuma casa

        if (num_casa[l][c] == (n-1) ) {  // verificação de se a casa tem valor (n-1)
            if ( abs(t.linha - l) <= 1 && abs(t.coluna - c) <= 1 )    // verificamos que está ao lado da nossa coordenada dada
                f = 1 ;                                               // alterar a flag, parando o ciclo, e indicando aquilo que acabamos de verificar
        }
                                                                            // mudar a posição do tabuleiro, se este ainda não tiver chegado ao fim
        if (c == 7 && l != 7) {                                             // se estiver na ultima coluna,
            c = 0 ;                                                       // passar para a primeira coluna
            l++;                                                          // da linha seguinte
        }
        else c++;                                                         // senão simplesmente vai-se para a coluna seguinte da mesma linha
    }

    if ( f == 1 ) return 1 ;                                                // a flag com valor 1 indica que a função tem valor 1
    else return 0;                                                          // a flag com valor 2 indica que a função tem valor 0

}

void inicializa_num_casa(int num_casa[8][8],ESTADO *e, int in){
        /* variáveis que preencherão as casas especiais do tabuleiro, UM e DOIS, mediante
        o jogador atual*/
        int casa1 ;
        int casa2 ; 

        if (( e->jogador_atual == 1 && in == 1)
         || ( e->jogador_atual == 2 && in == 2)) 
        {                             
            casa1 = 0 ; // O algoritimo floodfill terá como ponto de partida a casa que o jogador atual quer chegar.
            casa2 = -1 ; // Tal casa recebe o valor de 0, a outra -1.                  
        }  
        else {
            casa1 = -1 ;//raciocínio análogo ao anterior.
            casa2 = 0 ;
        }
        /*Ciclo que vai inicializar nossa matriz auxiliar com valores -1(exceto nas casas UM E DOIS)*/
        for (int a = 0;a<8;a++){
            for (int b = 0;b<8;b++)
            {
                if ( a == 0 && b == 7 )
                    num_casa[a][b] = casa2;
                else if ( a == 7 && b == 0 )
                    num_casa[a][b] = casa1;
                else num_casa[a][b] = -1;
            }
        }
}

int preenche_valor_das_casas(int num_casa[8][8],ESTADO *e, int in){
    int f1,nn,n;
    f1 = 0;
    nn = 0;
    n = 0;
    printf ("\n->Atribuição de valor dado para cada casa do tabuleiro:\n\n");

    while ( f1 == 0 ) {
  
            n++ ; 
            nn = 0 ;
            COORDENADA t ;

            for ( t.linha = 0 ; f1 == 0 && t.linha < 8 ; t.linha++ ) {
                for ( t.coluna = 0 ; f1 == 0 && t.coluna < 8 ; t.coluna++ ) {
                    if ( num_casa[t.linha][t.coluna] == -1 ) {

                        if (eaolado ( t , num_casa , n )) {

                            if (e->tab[t.linha][t.coluna] == VAZIO ) {
                                if (( in == 2 )
                                 || ( e->jogador_atual == 1 && (t.linha > 1 || t.coluna < 6))
                                 || ( e->jogador_atual == 2 && (t.linha < 6 || t.coluna > 1))) {
                                    num_casa[t.linha][t.coluna] = n ;
                                    nn++ ;
                                } 
                            }
                            else {
                                if (e->tab[t.linha][t.coluna] == BRANCA ) {
                                    num_casa[t.linha][t.coluna] = n ;
                                    if ( in == 1 )
                                        f1 = n ;
                                    nn++ ;
                                }
                            }
                        }
                    }
                }
            }

            if ( nn == 0 ) {
                if ( in == 1 )
                    f1 = -1 ;
                else
                    f1 = n ;
            }

            for (int a = 0;a<8;a++){
                for (int b = 0;b<8;b++){
                    if ((num_casa[a][b] < 0 || num_casa[a][b] > 9 ) && f1 != 0)
                        printf ("%d", num_casa[a][b]);
                    else if (f1!= 0)
                        printf (" %d", num_casa[a][b]);
                }
                if (f1!= 0)
                printf ("\n");
            }
            if (f1!= 0)
            printf ("\n");
        }

        if (f1 != -1){
            printf (" ---------------\n");
            printf (" a b c d e f g h\n");
        }
        else printf("\n->Não há necessidade de dar valor a nada... \nNão dá mais para chegar a minha casinha, algoritimo floodfill é inútil aqui :(\n");
    return f1;
}

COORDENADA floodfill_inversa ( int num_casa[8][8] , LISTA l , ESTADO *e ) {

    COORDENADA coor_final;
    COORDENADA * cabeca ;
    cabeca = devolve_cabeca(l);
    COORDENADA * cabecamax = cabeca;
    int numcabecamax = -1 ;
    
    inicializa_num_casa(num_casa,e,2);
    preenche_valor_das_casas(num_casa,e,2);

    while ( l != NULL ) {
        cabeca = devolve_cabeca (l) ;
        if (num_casa[cabeca->linha][cabeca->coluna] > numcabecamax) {
            numcabecamax = num_casa[cabeca->linha][cabeca->coluna]  ;
            cabecamax = cabeca ;
            printf ("%d %d %d\n", num_casa[cabeca->linha][cabeca->coluna] , cabeca->linha, cabeca->coluna );
        }
        l = proximo(l);
    }

    coor_final = *cabecamax ;
    return coor_final;
}

void guarda_jogadas(LISTA possiveis_jogadas,COORDENADA jogadas_possiveis[8],COORDENADA *cabeca){
    int contador = 0;
    
    while (possiveis_jogadas!=NULL){
        cabeca = devolve_cabeca(possiveis_jogadas);
        jogadas_possiveis[contador] = *cabeca;
        contador++;
        possiveis_jogadas = proximo(possiveis_jogadas);
    }
}

void recupera_jogadas(LISTA possiveis_jogadas,COORDENADA jogadas_possiveis[8]){
    int contador = 0;
    while (possiveis_jogadas!=NULL){
        possiveis_jogadas->valor = &jogadas_possiveis[contador];
        contador++;
        possiveis_jogadas = proximo(possiveis_jogadas);
    }

} 

COORDENADA auxiliar_floodfill(ESTADO *e,LISTA possiveis_jogadas,COORDENADA coord_escolhida){
    COORDENADA *cabeca;//váriavel auxiliar para retirar valores da lista ligada
    cabeca = &coord_escolhida; //inicialização para prevenir warnings
    int num_casa[8][8] ;//matriz auxiliar que é o cerne da estratégia
    //variáveis para operações de rotina de gestão de memória
    COORDENADA coordpossiveis[8];
    int f1;
     
    //processo para corrigir a problemática da matriz ocupar memória indesejada
    guarda_jogadas(possiveis_jogadas,coordpossiveis,cabeca);

    inicializa_num_casa(num_casa,e,1);

    //processo (reverso)para corrigir a problemática da matriz ocupar memória indesejada
    recupera_jogadas(possiveis_jogadas,coordpossiveis);

    f1 = preenche_valor_das_casas(num_casa,e,1);
     
        if (f1 > 0) coord_escolhida = aux (f1,possiveis_jogadas,num_casa);
        else {
            //inicializa_num_casa(num_casa,e,2);
            //preenche_valor_das_casas(num_casa,e,2);
            coord_escolhida = floodfill_inversa ( num_casa , possiveis_jogadas, e );
            //cabeca = devolve_cabeca (posicoesvazias);
            //coordaserjogada = *cabeca ;
        }
        //fazer caso em que não há como chegar
return coord_escolhida;
}

COORDENADA estrategia_floodfill ( ESTADO * e ) {
    LISTA possiveis_jogadas = criar_lista();//lista das possíveis jogadas
    COORDENADA coord_escolhida; //coordenada que vamos retornar no final
  
    printf ("\n => Resumo da estratégia efetuada (floodfill) \n\n")  ;
    
    coord_escolhida.linha  = 3;
    coord_escolhida.coluna = 4;
    
    coord_escolhida = insere_possiveis_jogadas (e,&possiveis_jogadas,coord_escolhida) ;//inicialização da lista ligada com as possiveis jogadas a se fazer
        
    /*Caso a condição abaixo se verificar é porque nenhuma das possíveis jogadas era uma jogada
    vitoriosa, e então vamos aplicar o algoritimo do floodfill*/
    if ((obter_estado_casa(e,coord_escolhida) != DOIS)
     && (obter_estado_casa(e,coord_escolhida) != UM)) {    

        coord_escolhida = auxiliar_floodfill(e,possiveis_jogadas,coord_escolhida);                              
        printf("\n->Jogada escolhida a partir da heurística floodfill : %c%d  ", coord_escolhida.coluna + 'a',8 -  coord_escolhida.linha); 
    }

    return  coord_escolhida;

}


/*------------------Funções correspondentes a estratégia Paridade----------------------------------*/

int aux_1_indice(int paridade[8]){
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
            if (paridade[i] >= resultado){
                indicedajogadaaefetuar = i;
                resultado = paridade[i];
            }
        }   
    }

    return indicedajogadaaefetuar;
}

int aux_2_indice(int paridade[8]){
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
            if (paridade[i] > resultado){
                indicedajogadaaefetuar = i;
                resultado = paridade[i];
            }
        }
    }

    return indicedajogadaaefetuar;
}

/*Devolve o índice escolhida da melhor jogada a efetuar*/
int  jogadaaefetuar(ESTADO * e,int paridade[8]){
    int indice_jogada_a_efetuar;

    if (e->jogador_atual == 1)
        indice_jogada_a_efetuar = aux_1_indice(paridade);
    else 
        indice_jogada_a_efetuar =  aux_2_indice(paridade); 
   
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
             && (coordvizinha.coluna <= 7)) {
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

void transfere_tabuleiro (CASA tabuleiro_1[8][8],CASA tabuleiro_2[8][8]){
        for (int i= 0; i < 8; i++){
            for (int j = 0; j < 8; j++){  
                tabuleiro_1[i][j] = tabuleiro_2[i][j]; 
            } 
        } 
}

/*Função auxiliar da "estrategia_paridade" que preenche o array paridade(que armazena a área restante para cada possível 
jogada) com as respetivas áreas de cada possível jogada*/
void auxiliarparidade (ESTADO *e,LISTA possiveis_jogadas,int paridade[8],COORDENADA *cabeca){
    
    CASA tabcopia[8][8];//matriz auxiliar criada de forma a não ser perdido o conteúdo do tabuleiro inicial
    int contador = 0;
    //variáveis para operações de rotina de gestão de memória
    COORDENADA coord_possiveis[8];
    COORDENADA coord_possiveis2[8];
    LISTA guarda_lista = possiveis_jogadas;

    guarda_jogadas(possiveis_jogadas,coord_possiveis2,cabeca);
  
    printf("\n->Área que sobra mediante cada possível jogada\n") ;
   
    while (possiveis_jogadas != NULL) {
        
        guarda_jogadas(possiveis_jogadas,coord_possiveis,cabeca);
        transfere_tabuleiro(tabcopia,e->tab);
        recupera_jogadas(possiveis_jogadas,coord_possiveis);

        cabeca = devolve_cabeca(possiveis_jogadas);
        printf("%c%d -> ",(*cabeca).coluna + 'a',8 - (*cabeca).linha); 
        altera_casa(e,(COORDENADA){(e->ultima_jogada).linha,(e->ultima_jogada).coluna}, PRETA);
        altera_casa(e,(COORDENADA){(*cabeca).linha,(*cabeca).coluna}, BRANCA);
        paridade[contador] = calcula_area(((possiveis_jogadas)->valor),e);

        printf("Área : %d\n",paridade[contador]);
        contador++;
        possiveis_jogadas = (possiveis_jogadas)->prox;
        
        // DEVO VOLTAR O TABUELIRO ANTIGO
        transfere_tabuleiro(e->tab,tabcopia);
    }
    possiveis_jogadas = guarda_lista;
    recupera_jogadas(possiveis_jogadas,coord_possiveis2);
}

/* Função Principal da heurística da Paridade*/
//Devolve a melhor jogada possível;
COORDENADA estrategia_paridade(ESTADO *e){
    
    LISTA possiveis_jogadas = criar_lista(); //lista ligada que armazena as possíveis jogadas
    COORDENADA coord_escolhida;//coordenada escolhida resultado de aplicar a função
    
    coord_escolhida.linha = 3;  // Inicialização da coordenada com este valor com fins na condição
    coord_escolhida.coluna = 4; //presente no próximo 'if'.
    
    COORDENADA *cabeca;//apontador auxiliar para retirar o conteúdo do apontador void da lista ligada
    cabeca = &coord_escolhida;//inicialização
    int paridade[8] =  {-1,-1,-1,-1,-1,-1,-1,-1,};//array que armazena a área restante para cada possível jogada
    /* o array acima é inicializado com -1 para efeitos no momento de desprezar certas jogadas  */ 
    
/* ciclo que vai analisar quais das POSIÇÕES VIZINHAS estão VAZIAS e armazená-las na LISTA ligada
criada para esse fim */
  
    coord_escolhida = insere_possiveis_jogadas(e,&possiveis_jogadas,coord_escolhida);
    /* Caso a coordaserjogada for uma das casas da vitória para o jogador atual, então quer dizer
    que o ciclo anterior encontrou uma jogada de prioridade MÁXIMA: a jogada da vitória. Caso 
    contrário então entrará em ação a escolha com base na paridade*/


    if ((obter_estado_casa(e,coord_escolhida) != DOIS)
     && (obter_estado_casa(e,coord_escolhida) != UM)){
    
        /*Função auxiliar que preenche o array paridade com as respetivas áreas de cada possível jogada*/
        auxiliarparidade(e,possiveis_jogadas,paridade,cabeca);
        
        /*Função auxiliar que devolverá o índice do array paridade escolhido. Como o array paridade
        possui as áreas respetivas de cada possível jogada, o índice escolhido estará de acordo com
        a posição da jogada na lista ligada*/
        int indice_da_jogada_escolhida;
        indice_da_jogada_escolhida = jogadaaefetuar(e,paridade); 
            
        /*Mediante o índice escolhido na função anterior, será então retirada a melhor jogada possível
        na lista ligada*/
        for (int i = indice_da_jogada_escolhida; i >= 0;i--,possiveis_jogadas = possiveis_jogadas->prox){
            if (i == 0)
                cabeca = devolve_cabeca(possiveis_jogadas);        
            coord_escolhida = *cabeca;
        }
        
        printf("\n->Jogada escolhida a partir da heurística da paridade : %c%d  ",(*cabeca).coluna + 'a',8 - (*cabeca).linha); 
    }
    else printf("\n->Você não me deu hipóteses...Parabéns pelo segundo lugar\n");

    return (coord_escolhida);
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
          && e->tab[l+1][c+1] == PRETA ){
       if (j == 1)
            return 2 ;
            else return 1 ;}}

     // Caso em que o jogador está no canto inferior direito
    if ( l == 7 && c == 7 ) {      
        if ( e->tab[l-1][c]   == PRETA 
          && e->tab[l][c-1]   == PRETA 
          && e->tab[l-1][c-1] == PRETA ){
        if (j == 1)
            return 2 ;
            else return 1;}}

    if ( l == 0 ) {
        if ( e->tab[l][c-1]   == PRETA 
          && e->tab[l][c+1]   == PRETA 
          && e->tab[l+1][c-1] == PRETA 
          && e->tab[l+1][c]   == PRETA 
          && e->tab[l+1][c+1] == PRETA ){
            if (j == 1)
            return 2 ;
            else return 1;}
    }

    if ( l == 7 ) {
        if ( e->tab[l][c-1]   == PRETA 
          && e->tab[l][c+1]   == PRETA 
          && e->tab[l-1][c-1] == PRETA 
          && e->tab[l-1][c]   == PRETA 
          && e->tab[l-1][c+1] == PRETA ){
           if (j == 1)
            return 2 ;
            else return 1;}
    }

    if ( c == 0 ) {
        if ( e->tab[l-1][c]   == PRETA 
          && e->tab[l+1][c]   == PRETA 
          && e->tab[l+1][c+1] == PRETA 
          && e->tab[l][c+1]   == PRETA 
          && e->tab[l-1][c+1] == PRETA ){
           if (j == 1)
            return 2 ;
            else return 1;}}

    if ( c == 7 ) {
        if ( e->tab[l-1][c]   == PRETA 
          && e->tab[l+1][c]   == PRETA 
          && e->tab[l+1][c-1] == PRETA 
          && e->tab[l][c-1]   == PRETA 
          && e->tab[l-1][c-1] == PRETA ){
            if (j == 1)
            return 2 ;
            else return 1;}}

    if ( e->tab[l-1][c]   == PRETA 
      && e->tab[l+1][c]   == PRETA 
      && e->tab[l+1][c-1] == PRETA 
      && e->tab[l][c-1]   == PRETA 
      && e->tab[l-1][c-1] == PRETA 
      && e->tab[l+1][c+1] == PRETA 
      && e->tab[l][c+1]   == PRETA 
      && e->tab[l-1][c+1] == PRETA ){
        if (j == 1)
            return 2 ;
            else return 1;}

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
                 
        if ( obter_jogador_atual (e) == 1 ) {
            
            e->jogadas[num_jogadas-1].jogador1 = jog_efet ;
            e -> jogador_atual = 2 ;
            
        }
        else {
            e->jogadas[num_jogadas-1].jogador2 = jog_efet ;
            e -> jogador_atual = 1 ;
            e->num_jogadas++;
 
        }
    if (t!=0) return 2;
    else 
    return 1;   
    }

    else {
       printf ( "A jogada não é válida, tente novamente! \n") ;
       return 0 ;
    } 
}
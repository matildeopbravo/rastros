#include <stdio.h>
#include <stdlib.h>
#include "dados.h"
#include "listas.h"


// {3,4} é a coordenada de controlo
COORDENADA vizinhas ( ESTADO *e , LISTA posicoesvazias ) {

    COORDENADA coordvizinha[8];//array que vai auxiliar no preenchimento da lista acima
    COORDENADA coordaserjogada;//coordenada escolhida resultado de aplicar a função
    coordaserjogada.linha = 3;  // Inicialização da coordenada com este valor com fins na condição
    coordaserjogada.coluna = 4; //presente no próximo 'if'.

    int h = 0;
    for (int i = 1 ;i >= -1;i--){
        for (int j = -1;j <= 1;j++,h++){
            
            coordvizinha[h].linha = ((e->ultima_jogada).linha) + i;
            coordvizinha[h].coluna = ((e->ultima_jogada).coluna) + j;
             
            /* Este primeiro if é a situação de preenchimento normal*/
            if ((obter_estado_casa(e,coordvizinha[h]) == VAZIO)
             && (coordvizinha[h].linha >= 0)
             && (coordvizinha[h].linha <= 7)
             && (coordvizinha[h].coluna >= 0)
             && (coordvizinha[h].coluna <= 7)) {
                posicoesvazias = insere_cabeca(posicoesvazias, &(coordvizinha[h]));
            }

            /* Este if analisa uma das situações de prioridade MÀXIMA- VITÓRIA
            O ciclo deve ser interrompido dado que já achamos a jogada*/
            if ((e->jogador_atual == 1 )
             && (obter_estado_casa(e,coordvizinha[h]) == UM)
             && (coordvizinha[h].linha >= 0)
             && (coordvizinha[h].linha <= 7)
             && (coordvizinha[h].coluna >= 0)
             && (coordvizinha[h].coluna <= 7)) {

                coordaserjogada = coordvizinha[h];
                j = 1;
                i = -1;
            }

            /* Este if analisa a outra situações de prioridade MÀXIMA- VITÓRIA
            O ciclo deve ser interrompido dado que já achamos a jogada*/
            if ((e->jogador_atual == 2 
             &&   obter_estado_casa(e,coordvizinha[h]) == DOIS)
             && (coordvizinha[h].linha >= 0)
             && (coordvizinha[h].linha <= 7)
             && (coordvizinha[h].coluna >= 0)
             && (coordvizinha[h].coluna <= 7)){
                   
                coordaserjogada = coordvizinha[h];
                j = 1;
                i = -1;
            }                  
        }
    }

    return coordaserjogada;
}

/*------------------Funções correspondentes a estratégia Floodfill---------------------------------*/
COORDENADA aux (int f1 , LISTA l , int num_casa[8][8]){
    COORDENADA coor_final;
    COORDENADA * cabeca ;
    cabeca = devolve_cabeca(l);
        if ( f1 > 0 ){                                                        // se houver caminho possível, encontrar a primeira casa 
            while ( num_casa[cabeca->linha][cabeca->coluna] != (f1 - 1)) {    // (é aleatório) com valor igual a (f1 - 1)
                l = proximo(l);
                cabeca = devolve_cabeca (l) ;
            }
        }
        coor_final = *cabeca ;
        return coor_final;
}

// Temos a coordenada t. Queremos saber se essa casa está ao lado de alguma com valor n-1. Para isso corremos todas as posições do tabuleiro até 
// encontrarmos alguma ao lado da coordenada que temos ou chegarmos ao fim do tabuleiro.

int eaolado ( COORDENADA t , int num_casa[8][8] , int n ) {                 
    int f = 0 ;                                                             // flag que será usada no ciclo
    int l = 0 , c = 0 ;                                                     // primeira posição do tabuleiro é linha 0 coluna 0

    while ( f == 0 ) {

        if (c == 7 && l == 7)                                               // verificamos se chegou ao fim do tabuleiro se isso acontecer, mudamos a flag,
            f = 2 ;                                                         //  parando o ciclo e informando que não está ao lado de nenhuma casa
                                                                          // nas condições que queríamos (a não ser que a condição seguinte se verifique)
        if (num_casa[l][c] == (n-1) ) {                                     // verificamos que tem valor (n-1)
            if ( abs(t.linha - l) <= 1 && abs(t.coluna - c) <= 1 )          // verificamos que está ao lado da nossa coordenada dada
                f = 1 ;                                                     // alterar a flag, parando o ciclo, e indicando aquilo que acabamos de verificar
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

COORDENADA estrategia_floodfill ( ESTADO * e ) {
    COORDENADA coor_final;                                                      // é a coordenada que vamos retornar no final

    LISTA l = criar_lista();                                                    // lista de posições vazias
    COORDENADA possiveljogada = vizinhas ( e , l ) ;

    int num_casa[8][8] ;

    if ( possiveljogada.linha != 3 
      || possiveljogada.coluna != 4 ) {
          coor_final = possiveljogada ;
    }
    else {    
        int f1 = 0 ;                                                            // flag 1 (explicação em baixo)
        //int f2 = 0 ;                                                            // flag 2 (explicação em baixo)
        int c1 ;                                                                // variáveis cujos valores serão determinados à frente
        int c2 ;
        int nn ;                                                                // explicação mais à frente
        int n = 0 ;                                                             // é a variável que vai dar valor às casas no num_casa

        if ( e->jogador_atual == 1 ) {                                           // ao saber qual o jogador_atual,
            c1 = 0 ;                                                           // conseguimos saber qual a peça para onde ele ganha o jogo
            c2 = -1 ;                                                          // e desse modo atribuir valor a c1 e c2
        }  
        else {
            c1 = -1 ;
            c2 = 0 ;
        }



        while ( f1 == 0 ) {

            num_casa[0][0] = -1 ;
            num_casa[0][1] = -1 ;
            num_casa[0][2] = -1 ;
            num_casa[0][3] = -1 ;
            num_casa[0][4] = -1 ;
            num_casa[0][5] = -1 ;
            num_casa[0][6] = -1 ;
            num_casa[0][7] = c2 ;
            num_casa[1][0] = -1 ;
            num_casa[1][1] = -1 ;
            num_casa[1][2] = -1 ;
            num_casa[1][3] = -1 ;
            num_casa[1][4] = -1 ;
            num_casa[1][5] = -1 ;
            num_casa[1][6] = -1 ;
            num_casa[1][7] = -1 ;
            num_casa[2][0] = -1 ;
            num_casa[2][1] = -1 ;
            num_casa[2][2] = -1 ;
            num_casa[2][3] = -1 ;
            num_casa[2][4] = -1 ;
            num_casa[2][5] = -1 ;
            num_casa[2][6] = -1 ;
            num_casa[2][7] = -1 ;
            num_casa[3][0] = -1 ;
            num_casa[3][1] = -1 ;
            num_casa[3][2] = -1 ;
            num_casa[3][3] = -1 ;
            num_casa[3][4] = -1 ;
            num_casa[3][5] = -1 ;
            num_casa[3][6] = -1 ;
            num_casa[3][7] = -1 ;
            num_casa[4][0] = -1 ;
            num_casa[4][1] = -1 ;
            num_casa[4][2] = -1 ;
            num_casa[4][3] = -1 ;
            num_casa[4][4] = -1 ;
            num_casa[4][5] = -1 ;
            num_casa[4][6] = -1 ;
            num_casa[4][7] = -1 ;
            num_casa[5][0] = -1 ;
            num_casa[5][1] = -1 ;
            num_casa[5][2] = -1 ;
            num_casa[5][3] = -1 ;
            num_casa[5][4] = -1 ;
            num_casa[5][5] = -1 ;
            num_casa[5][6] = -1 ;
            num_casa[5][7] = -1 ;
            num_casa[6][0] = -1 ;
            num_casa[6][1] = -1 ;
            num_casa[6][2] = -1 ;
            num_casa[6][3] = -1 ;
            num_casa[6][4] = -1 ;
            num_casa[6][5] = -1 ;
            num_casa[6][6] = -1 ;
            num_casa[6][7] = -1 ;
            num_casa[7][0] = c1 ;
            num_casa[7][1] = -1 ;
            num_casa[7][2] = -1 ;
            num_casa[7][3] = -1 ;
            num_casa[7][4] = -1 ;
            num_casa[7][5] = -1 ;
            num_casa[7][6] = -1 ;
            num_casa[7][7] = -1 ;


            n++ ;                                                               // incrementa-se o n para mudar o número que se coloca na matriz num_casa
            nn = 0 ;                                                            // nn representa quantas vezes se vai escrever o numero n em num_casa
                                                                              // no ciclo abaixo
            COORDENADA t ;                                                      // t representa a posição que vamos averiguar se colocamos o valor n

            for ( t.linha = 0 ; f1 == 0 && t.linha != 7 ; t.linha++ ) {
                for ( t.coluna = 0 ; f1 == 0 && t.coluna != 7 ; t.coluna++ ) {
                    if ( num_casa[t.linha][t.coluna] == -1 ) {

                        if (eaolado ( t , num_casa , n )) {

                            if (e->tab[t.linha][t.coluna] == VAZIO ) {
                                num_casa[t.linha][t.coluna] = n ;
                                nn++ ;
                            }
                            else {
                                if (e->tab[t.linha][t.coluna] == BRANCA ) {
                                    num_casa[t.linha][t.coluna] = n ;
                                    f1 = n ;
                                    nn++ ;
                                }
                            }
                        }
                    }
                }
            }

            if ( nn == 0 )                                                      // no fim de cada ciclo, é necessário ver se atribuímos o valor n a alguma
                f1 = -1 ;                                                     // casa neste ciclo. Se isso não acontecer, é porque não há caminho possível
                                                                                          // desde a casa detino até à casa ondee o jogador se encontra. É atribuído
        }
        printf("%d\n",f1);
        coor_final = aux (f1 , l , num_casa);                                                                     // o valor -1 à flag 1, para parar o ciclo maior, informando que não há caminho.
    }
        
    

    return coor_final;

}


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
            if (paridade[i] >= resultado){
                indicedajogadaaefetuar = i;
                resultado = paridade[i];
            }
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
    coordaserjogada.linha = 3;  // Inicialização da coordenada com este valor com fins na condição
    coordaserjogada.coluna = 4; //presente no próximo 'if'.
    COORDENADA *cabeca;//apontador auxiliar para retirar o conteúdo do apontador void da lista ligada
    int paridade[8] =  {-1,-1,-1,-1,-1,-1,-1,-1,};//array que armazena a área restante para cada possível jogada
    /* o array acima é inicializado com -1 para efeitos no momento de desprezar certas jogadas  */ 

/* ciclo que vai analisar quais das POSIÇÕES VIZINHAS estão VAZIAS e armazená-las na LISTA ligada
criada para esse fim */
  
    int h = 0;
    for (int i = 1 ;i >= -1;i--){
        for (int j = -1;j <= 1;j++,h++){
            
            coordvizinha[h].linha = ((e->ultima_jogada).linha) + i;
            coordvizinha[h].coluna = ((e->ultima_jogada).coluna) + j;
             
            /* Este primeiro if é a situação de preenchimento normal*/
            if ((obter_estado_casa(e,coordvizinha[h]) == VAZIO)
             && (coordvizinha[h].linha >= 0)
             && (coordvizinha[h].linha <= 7)
             && (coordvizinha[h].coluna >= 0)
             && (coordvizinha[h].coluna <= 7)) {
                posicoesvazias = insere_cabeca(posicoesvazias, &(coordvizinha[h]));
            }

            /* Este if analisa uma das situações de prioridade MÀXIMA- VITÓRIA
            O ciclo deve ser interrompido dado que já achamos a jogada*/
            if ((e->jogador_atual == 1 )
             && (obter_estado_casa(e,coordvizinha[h]) == UM)
             && (coordvizinha[h].linha >= 0)
             && (coordvizinha[h].linha <= 7)
             && (coordvizinha[h].coluna >= 0)
             && (coordvizinha[h].coluna <= 7)) {

                coordaserjogada = coordvizinha[h];
                j = 1;
                i = -1;
            }

            /* Este if analisa a outra situações de prioridade MÀXIMA- VITÓRIA
            O ciclo deve ser interrompido dado que já achamos a jogada*/
            if ((e->jogador_atual == 2 
             &&   obter_estado_casa(e,coordvizinha[h]) == DOIS)
             && (coordvizinha[h].linha >= 0)
             && (coordvizinha[h].linha <= 7)
             && (coordvizinha[h].coluna >= 0)
             && (coordvizinha[h].coluna <= 7)){
                   
                coordaserjogada = coordvizinha[h];
                j = 1;
                i = -1;
            }                  
        }
    }
    
    /* Caso a coordaserjogada for uma das casas da vitória para o jogador atual, então quer dizer
    que o ciclo anterior encontrou uma jogada de prioridade MÁXIMA: a jogada da vitória. Caso 
    contrário então entrará em ação a escolha com base na paridade*/
    
    if ((obter_estado_casa(e,coordaserjogada) != DOIS)
     && (obter_estado_casa(e,coordaserjogada) != UM)){
    
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
    }
    else printf("\n->Você não me deu hipóteses...Parabéns pelo segundo lugar\n");

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
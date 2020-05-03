#include <stdio.h>
#include <stdlib.h>
#include "dados.h"
#include "listas.h"

int verifica_casa_vazia(ESTADO *e, COORDENADA coordenada){
    int result = 0;

    if ((obter_estado_casa(e,coordenada) == VAZIO))
        result = 1;    

return result;
}

int verifica_limite_tabuleiro(COORDENADA coordenada){
    int result = 0;

    if ((coordenada.linha >= 0) && (coordenada.linha <= 7)
     && (coordenada.coluna >= 0)&& (coordenada.coluna <= 7))
    {
        result = 1;
    }    

return result;
}

COORDENADA * duplica_coordenada(COORDENADA coordenada){
    COORDENADA * coordenada_duplicada;
        coordenada_duplicada = (COORDENADA *)malloc(sizeof(COORDENADA));
        *coordenada_duplicada = coordenada;
    return coordenada_duplicada;        
}

COORDENADA insere_possiveis_jogadas ( ESTADO *e , LISTA *posicoesvazias,COORDENADA coord_escolhida ) {

    COORDENADA coord_vizinha; //Coordenada que vai armazenar cada possível coordenada vizinha em cada ciclo
    COORDENADA *coord_duplicada;// será o resultado de duplicar a coordenada anterior de modo a não perder seu conteúdo
 
    for (int i = 1 ;i >= -1;i--){
        for (int j = -1;j <= 1;j++){
            
            coord_vizinha.linha = ((obtem_ultima_jogada(e)).linha) + i;
            coord_vizinha.coluna = ((obtem_ultima_jogada(e)).coluna) + j;
             
            /* Este primeiro if é a situação de preenchimento normal*/
            if (verifica_casa_vazia(e,coord_vizinha)
               && verifica_limite_tabuleiro(coord_vizinha))
               {
                    coord_duplicada = duplica_coordenada(coord_vizinha);
                    *posicoesvazias = insere_cabeca(*posicoesvazias,coord_duplicada);

               }
            /* Este if analisa uma das situações de prioridade MÀXIMA- VITÓRIA
            O ciclo deve ser interrompido dado que já achamos a jogada*/
            if ((obter_jogador_atual(e) == 1 )
                && (obter_estado_casa(e,coord_vizinha) == UM)
                &&  verifica_limite_tabuleiro(coord_vizinha))
               {
                coord_escolhida = coord_vizinha;
                break;
               }

            /* Este if analisa a outra situações de prioridade MÀXIMA- VITÓRIA
            O ciclo deve ser interrompido dado que já achamos a jogada*/
            if ((obter_jogador_atual(e) ==  2)
                && obter_estado_casa(e,coord_vizinha) == DOIS
                && verifica_limite_tabuleiro(coord_vizinha))
               {
                coord_escolhida = coord_vizinha;
                break;
               }
         }
    }

    return coord_escolhida;
}


COORDENADA escolhe_aleatorio (LISTA lista) {
   int length = comprimento_lista(lista);           
   int random = rand() % length;

   for(int i = 0; i < random ; i++, lista = lista->prox); 
  // return *(lista->valor);
 return *(COORDENADA *)(lista->valor); 
}


COORDENADA devolve_coordenada_flood (int valor_casa_atual , LISTA possiveis_jogadas , int num_casa[8][8]){
  
    LISTA r = possiveis_jogadas;
    LISTA ant = NULL;

    while(r != NULL) {
     COORDENADA *  cabeca = devolve_cabeca(r);
    
        if (num_casa[cabeca->linha][cabeca->coluna] != (valor_casa_atual - 1)) {

           r = remove_cabeca(r); 

            if (ant) {
                ant->prox =r;
            }
            else {
                possiveis_jogadas = r;
            }
        }
        else {
             ant = r;
            r = proximo(r);
        }
    }
  return escolhe_aleatorio(possiveis_jogadas);
}
int verifica_adjacencia ( COORDENADA coord , int num_casa[8][8] , int valor ) {                 
    int flag = 0 ;// flag que será usada no ciclo
    COORDENADA coord_vizinha;

    for (int i = 1 ;i >= -1;i--){
        for (int j = -1;j <= 1;j++){
            
            coord_vizinha.linha = (coord.linha) + i;
            coord_vizinha.coluna = (coord.coluna) + j;

            if (num_casa[coord_vizinha.linha][coord_vizinha.coluna] == (valor - 1)
               && verifica_limite_tabuleiro(coord_vizinha))
                flag = 1;
                                              
        }
    }
return flag;   
}

void inicializa_num_casa(int num_casa[8][8],ESTADO *e, int flag){
        /* variáveis que preencherão as casas especiais do tabuleiro, UM e DOIS, mediante
        o jogador atual e a flag dada*/
        int casa1,casa2 ; 

        if (( obter_jogador_atual(e) == 1 && flag == 1)
         || ( obter_jogador_atual(e) && flag == 2)) 
        {                             
            casa1 = 0 ; // O algoritimo floodfill terá como ponto de partida a casa que o jogador atual quer chegar.
            casa2 = -1 ; // Tal casa recebe o valor de 0, a outra -1.                 
        }  
        else {
            casa1 = -1 ;//raciocínio análogo ao anterior.
            casa2 = 0 ;
        }
        /*Ciclo que vai inicializar nossa matriz auxiliar com valores -1(exceto nas casas UM E DOIS)*/
        for (int linha = 0;linha < 8 ;linha++){
            for (int coluna = 0;coluna <8 ;coluna++)
            {
                if ( linha == 0 && coluna == 7 )
                    num_casa[linha][coluna] = casa2;
                else if ( linha == 7 && coluna == 0 )
                    num_casa[linha][coluna] = casa1;
                else num_casa[linha][coluna] = -1;
            }
        }
}

int verifica_quadrante (ESTADO *e,COORDENADA coord){

    int result = 0;
    
    if ((obter_jogador_atual(e) == 1 && (coord.linha > 1 || coord.coluna < 6))
       || (obter_jogador_atual(e)== 2 && (coord.linha < 6 || coord.coluna > 1)))
       {
       result = 1;
       }
return result;

}

int preenche_valor_das_casas(int num_casa[8][8],ESTADO *e, int flag){
    
    int valor_casa_atual,//Indicará o valor dado a casa que o jogador está(util para indicar que chegamos ao fim da função ao preencher esta variável- mudará seu valor de 0 para outro)
        caminho_encontrado,// 0 se não é possível formar caminho para onde quero chegar. Diferente de zero caso contrário
        valor_casa_do_ciclo;//Valor que cada casa vai possuir mediante a fase do ciclo while

    //Inicialização das variáveis
    valor_casa_atual = caminho_encontrado =  valor_casa_do_ciclo = 0;
   
    while ( valor_casa_atual == 0 ) {
  
        valor_casa_do_ciclo++; // Toda vez que começa o ciclo incrementamos o valor das casas a preencher(para dar segmento a formação do caminho) 
        caminho_encontrado = 0 ;//Toda vez que o ciclo começa deve se partir do princípio que ainda não encontramos um possível caminho até ser dito o contrário
        COORDENADA coord;

        for ( coord.linha = 0 ; valor_casa_atual == 0 && coord.linha < 8 ; coord.linha++ ) {
            for ( coord.coluna = 0 ; valor_casa_atual == 0 && coord.coluna < 8 ; coord.coluna++ ) {
                
                 /*Para preencher uma casa com o valor_casa_do_ciclo devemos testar se a casa correspondente
                 a coordenada "coord" ainda possui o valor de -1(valor de inicialização,ou seja, ainda não foi
                 preenchida) e se ela é uma casa adjacente a uma outra casa com "valor_casa_do_ciclo - 1"*/
                 if ( num_casa[coord.linha][coord.coluna] == -1
                    && (verifica_adjacencia(coord,num_casa,valor_casa_do_ciclo))) {
                       
                       /*Precisamos testar se a casa potencial a ser preenchida é VAZIA,
                       dado que uma casa não VAZIA não poderá fazer parte do caminho*/

                       if (e->tab[coord.linha][coord.coluna] == VAZIO ) {
                            
                           /*Caso a CASA for fazia devemos nos preocupar apenas com uma situação:
                           se a flag for diferente de 2  e a casa estiver no quadrante de perigo(quando
                           verifica_quadrante devolve 0) não preencheremos a casa pois isso significa que
                           o caminho mais rápido para vitória pode correr o risco de passar por uma casa que pode
                           garantir a derrota na próxima jogada. Se estiver procurando o caminho mais longo para 
                           derrota isso é irrelevante, por isso a condição abaixo preencherá tal casa caso as situções
                           ditas acima não se verificarem*/

                           if (( flag == 2 ) || verifica_quadrante(e,coord)) 
                                {
                                 num_casa[coord.linha][coord.coluna] = valor_casa_do_ciclo ;
                                 caminho_encontrado++;
                                } 
                            }

                            else {
                                if (e->tab[coord.linha][coord.coluna] == BRANCA ) {
                                    num_casa[coord.linha][coord.coluna] = valor_casa_do_ciclo ;
                                    if ( flag == 1 )
                                        valor_casa_atual = valor_casa_do_ciclo ;
                                    caminho_encontrado++ ;
                                }
                            }
                         }
                     }
                }
            
            /*Caso não for encontrado caminho podemos estar na situação que estamos a procura do caminho mais rapido para
            vitoria ou o mais lento para derrota, caso estivermos na primeira situação metemos o valor_casa_atual a -1 para na função chamadora
            saber que é preciso aplicar o floodfill_inverso, caso contrário quer dizer que já estamos a aplicar o floodfill inverso 
            e mesmo assim não há caminho, logo devolvemos o valor_casa_atual como o valor_casa_do_ciclo para fins na escolha
            qualquer na floodfill inversa*/

            if ( caminho_encontrado == 0 ) {
                if ( flag == 1 )
                    valor_casa_atual = -1 ;
                else
                    valor_casa_atual = valor_casa_do_ciclo ;
            }

        }

    
    return valor_casa_atual;
}

COORDENADA floodfill_inversa ( int num_casa[8][8] , LISTA possiveis_jogadas , ESTADO *e ) {

    COORDENADA coor_final;
    COORDENADA * cabeca ;
    cabeca = devolve_cabeca(possiveis_jogadas);
    COORDENADA * cabecamax = cabeca;
    int numcabecamax = -1 ;
    
    inicializa_num_casa(num_casa,e,2);
    preenche_valor_das_casas(num_casa,e,2);

    while ( possiveis_jogadas != NULL ) {
        cabeca = devolve_cabeca (possiveis_jogadas) ;
        if (num_casa[cabeca->linha][cabeca->coluna] > numcabecamax) {
            numcabecamax = num_casa[cabeca->linha][cabeca->coluna]  ;
            cabecamax = cabeca ;
        }
        possiveis_jogadas = proximo(possiveis_jogadas);
    }

    coor_final = *cabecamax ;
    return coor_final;
}


COORDENADA auxiliar_floodfill(ESTADO *e,LISTA possiveis_jogadas,COORDENADA coord_escolhida){
    
    int num_casa[8][8] ;//matriz auxiliar que é o cerne da estratégia
    int valor_casa_atual; //Indicará se será preciso fazer a floodfill inversa ou não

    inicializa_num_casa(num_casa,e,1); //inicializa o tabuleiro com valores -1(exceto nos casos especiais das extremidades)

    valor_casa_atual = preenche_valor_das_casas(num_casa,e,1);
     
        if (valor_casa_atual > 0){
           coord_escolhida = devolve_coordenada_flood (valor_casa_atual,possiveis_jogadas,num_casa);
        }
        else if (e->isBot){
            coord_escolhida = (COORDENADA) {3,4};
        }
        else {
              coord_escolhida = floodfill_inversa (num_casa,possiveis_jogadas,e);
        }

return coord_escolhida;
}

COORDENADA estrategia_floodfill ( ESTADO * e ) {
    
    LISTA possiveis_jogadas = criar_lista();//lista das possíveis jogadas
    COORDENADA coord_escolhida; //coordenada que vamos retornar no final
    
    /*inicialização padrão para fins no if da linha 266*/
    coord_escolhida.linha  = 3;
    coord_escolhida.coluna = 4;
    
    coord_escolhida = insere_possiveis_jogadas (e,&possiveis_jogadas,coord_escolhida) ;//inicialização da lista ligada com as possiveis jogadas a se fazer
        
    /*Caso a condição abaixo se verificar é porque nenhuma das possíveis jogadas era uma jogada
    vitoriosa, e então vamos aplicar o algoritimo do floodfill*/
    if ((obter_estado_casa(e,coord_escolhida) != DOIS)
     && (obter_estado_casa(e,coord_escolhida) != UM)) {    

        coord_escolhida = auxiliar_floodfill(e,possiveis_jogadas,coord_escolhida);                              
    }

    return  coord_escolhida;

}
int devolve_indice_paridade(int paridade[8]){
    int jogadas_possiveis [8]; 
    int menor_par = 66, maior_impar = -1;
     /*inicialização da variável com uma quantidade que eu evite ser aleatória e
    é de nosso conhecimento que nenhuma área será maior que isso*/
    int j = 0,i = 0;

    for (i = 0; i < 8 ; i++) {
        if(paridade[i] <= menor_par && paridade[i] % 2 == 0) {
                menor_par = paridade[i];
        }
        if(paridade[i] >= maior_impar && paridade[i] % 2 != 0) {
                maior_impar = paridade[i];
        }
    }
    /*Ciclo que escolhe a menor área par do array*/    
    if (menor_par != 66 ) {

        for (i = 0; i <8;i++){
             if (paridade[i] == menor_par){
                 jogadas_possiveis[j] = i;
                 j++;
             }
        }
    }
    /*Situação em que não existem jogadas com área restante par.
    Por tanto devo jogar para a MAIOR área ímpar(dado que diminuirá
    as probabilidades de eu ser encurralado)* pois a longo prazo
    o cenário pode mudar*/
    else {

            for (int i = 0; i < 8;i++){
                 if (paridade[i] == maior_impar){
                    jogadas_possiveis[j] = i;
                    j++;
                  }
            }   
    }

    int x = rand() % j ;
    return jogadas_possiveis[x];
}

int  jogadaaefetuar(int paridade[8]){
    int indice_jogada_a_efetuar;

        indice_jogada_a_efetuar = devolve_indice_paridade(paridade); 
   
    return indice_jogada_a_efetuar;
}


int calcula_area(COORDENADA * possiveljogada, ESTADO * e){ 
    COORDENADA coordvizinha;
    int area = 0;

    for (int i = 1 ;i >= -1;i--){
        for (int j = -1;j <= 1;j++){ 
                
            coordvizinha.linha = ((*possiveljogada).linha) + i;
            coordvizinha.coluna = ((*possiveljogada).coluna) + j;

            if (verifica_casa_vazia(e,coordvizinha)
               && verifica_limite_tabuleiro(coordvizinha)) {
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

void auxiliarparidade (ESTADO *e,LISTA possiveis_jogadas,int paridade[8],COORDENADA *cabeca){
    
    CASA tabcopia[8][8];//matriz auxiliar criada de forma a não ser perdido o conteúdo do tabuleiro inicial
    int contador = 0;

    LISTA guarda_lista = possiveis_jogadas;
   
    while (possiveis_jogadas != NULL) {
        
        transfere_tabuleiro(tabcopia,e->tab);

        cabeca = devolve_cabeca(possiveis_jogadas);
        
        altera_casa(e,(COORDENADA){(e->ultima_jogada).linha,(e->ultima_jogada).coluna}, PRETA);
        altera_casa(e,(COORDENADA){(*cabeca).linha,(*cabeca).coluna}, BRANCA);
        
        paridade[contador] = calcula_area(((possiveis_jogadas)->valor),e);

        contador++;
        possiveis_jogadas = (possiveis_jogadas)->prox;
        
        // DEVO VOLTAR O TABUELIRO ANTIGO
        transfere_tabuleiro(e->tab,tabcopia);
    }
    possiveis_jogadas = guarda_lista;
}

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
        indice_da_jogada_escolhida = jogadaaefetuar(paridade); 
            
        /*Mediante o índice escolhido na função anterior, será então retirada a melhor jogada possível
        na lista ligada*/
        for (int i = indice_da_jogada_escolhida; i >= 0;i--,possiveis_jogadas = possiveis_jogadas->prox){
            if (i == 0)
                cabeca = devolve_cabeca(possiveis_jogadas);        
            coord_escolhida = *cabeca;
        }
        
    }

    return (coord_escolhida);
}


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

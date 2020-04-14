#include <stdio.h>
#include <stdlib.h>
#include "dados.h"
#include "logica.h"
#include <string.h>
#define BUF_SIZE 1024

int verificanumero (char token){
    int res = 0;
    for (char a = '0';a < '9';a++) {
        if (token == a)
           res = 1;
    }
    return res;
}

void printarcampeao(ESTADO * estado){

    int campeao,jogadoratual;
    COORDENADA ultimajogada; 

    ultimajogada  = estado -> ultima_jogada;
    jogadoratual = estado -> jogador_atual;

    campeao = verifica_fim (estado,ultimajogada.linha,ultimajogada.coluna,jogadoratual);

    if (campeao==1) 
        printf ("Parabéns jogador 1, é o vencedor deste jogo!!!! \n");
    else 
        printf ("Parabéns jogador 2, é o vencedor deste jogo!!!! \n");
}

//Mostra o tabuleiro no ecrã como também o insere num ficheiro quando efetuado o comando "gr"
void mostrar_tabuleiro(ESTADO * estado, FILE * stream) {
    int i , j ;

    for ( i = 0 ; i < 8 ; i++ ) {
        
        if ( stream == stdout )
            fprintf (stream, "%d ", 8 - i);    // Printa o número de cada linha na tela

        for ( j = 0 ; j < 8 ; j++ ) {
            CASA cs =(obter_estado_casa(estado, (COORDENADA){i,j}));
            if (cs == VAZIO) 
                fputc('.',stream) ;
            else
                 fputc(cs,stream);
        }       
        fputc('\n',stream) ;
    }

    if ( stream == stdout )
        fprintf (stream,"  abcdefgh\n");    
        
}

// nomeadamente a última jogada, que é uma componente da struct principal, deverá ser ainda a do jogo atual e nao da do jogo 
// inserido no comando pos. Por isso é guardado seu valor para no final de tudo, repor ele caso tal função tiver sido invocada num momento em que
// não era o conteúdo propriamente em si que iria ser mudado e apenas trabalhava  para funções que mostram na tela.
void altera_tabuleiro(ESTADO *e,int regulador){

     COORDENADA guardaultima = e->ultima_jogada;

    if (e-> num_jogadas != -1)
        e->ultima_jogada = obtem_coordenada(e,(e->num_jogadas),2);
    else  
        (e->ultima_jogada = (COORDENADA) {3,4});
   
    for (int h = e ->num_jogadas + 1; h <= 31; h++){
        COORDENADA coord1 = obtem_coordenada(e,h,1);
        COORDENADA coord2 = obtem_coordenada(e,h,2);
        e->tab[coord1.linha][coord1.coluna] = VAZIO;
        e->tab[coord2.linha][coord2.coluna] = VAZIO;
    }   
    COORDENADA coord3 = e->ultima_jogada;
    e->tab[coord3.linha][coord3.coluna] = BRANCA;

    if (regulador == 0)
        e->ultima_jogada = guardaultima;
    
}
void atualizapos(ESTADO *e){
      CASA tabcopia[8][8];
      e->jogador_atual = 1;//Padrão. O começo de uma nova jogada é sempre do jogador 1.
    
      for (int i= 0; i < 9 - 1; i++){
          for (int j = 0; j < 8; j++){
              tabcopia[i][j] = e->tab[i][j];
          }
      }
      e->num_jogadas = e->num_jogadas - 2;
      altera_tabuleiro(e,0);
      mostrar_tabuleiro(e,stdout);
 
      for (int i= 0; i < 8; i++){
          for (int j = 0; j < 8; j++){
              e->tab[i][j] = tabcopia[i][j];
          }
      }
}                               

void apagajogpost(ESTADO *e){
        
    JOGADA jog;
    int i;

    for ( i = e->num_jogadas + 1 ; i <= 31 ; i++ ) { 
        jog = (JOGADA) {.jogador1 = (COORDENADA){0,0}, .jogador2 =(COORDENADA){0,0}};
        acrescenta_jogada(e,i,jog);
    }
}

//Mostra o prompt no ecrã como também o insere num ficheiro quando feito o comando "gr"
void mostrar_prompt (ESTADO * e){
    int jogadoratual;
    int numerojogadas;
    int numerocomandos;   // Cada vez que uma rodada e jogadas acontece (ambos jogam) o numero de jogadas aumenta

    jogadoratual = obter_jogador_atual(e);
    numerojogadas = obter_numero_de_jogadas(e);
    numerocomandos = obter_numero_de_comandos (e);

    printf ("\nPlayer: %d |Jogada: %d  |comandos: %d  > ", jogadoratual,numerojogadas,numerocomandos);    
   
}

//Mostra o histórico de jogadas no ecrã como também os insere num ficheiro após efetuado ocomando "gr"
void mostrar_jogadas (ESTADO * e,  FILE * stream) {
    int numjogadas;
    if ( stream == stdout )
        fprintf (stream,"\n");

    if (e->jogador_atual == 1)
    numjogadas = e->num_jogadas  - 1;
    else numjogadas = e->num_jogadas;

    for(int i = 0; i < numjogadas; i++) {
        if ( i < 9 ) 
            fprintf(stream,"0%d: ", i + 1);
        else 
            fprintf(stream,"%d: ", i + 1);

        if(i == (numjogadas -1) && obter_ultimo_jogador(e) == 1)
            fprintf(stream,"%s\n",obtem_jogada(e,i,1));
        else
            fprintf(stream,"%s %s\n",obtem_jogada(e,i,1), obtem_jogada(e,i,2));
    }

}

void gravar (ESTADO * e, char * nome_ficheiro) {
    FILE *  fp = NULL;

    if ( (fp = fopen(nome_ficheiro,"w+")) ) {
        mostrar_tabuleiro(e,fp);
        fputc('\n',fp);
        mostrar_jogadas(e,fp);         
    }

    else printf("Erro a gravar ficheiro");

    fclose(fp);
}

COMANDO verifica_comando( char * token ) {
    if(!strcmp(token,"gr")) return GRAVAR;
    if(!strcmp(token,"ler")) return LER;
    if(!strcmp(token,"pos")) return POS;
    if(!strcmp(token,"movs")) return MOVS;
    if(!strcmp(token,"jog")) return  JOG;
    return 0;
}

//Auxiliar da função "ler" que lê a parte correspondente ao tabuleiro
void ler_tabuleiro(ESTADO * e, FILE * fp) {
    char ponto;
    int jognvazias = 0 ;
    int jogadoratual , numerojogadas ;

    for ( int i = 0 ; i < 8 ; i++ ) {
        for(int j = 0; (ponto = fgetc(fp)) != '\n'; j++) {
            if(ponto == '.')
                altera_casa(e,(COORDENADA) {i,j} , VAZIO);
            else {
                altera_casa(e,(COORDENADA) {i,j} ,ponto);
                jognvazias ++ ;
            }
                
            if(ponto == '*') altera_ultima_jogada(e,(COORDENADA){i,j});
                
        }
    }

    if ( jognvazias % 2 == 0 ) 
        jogadoratual = 2 ;
    else 
        jogadoratual = 1 ;

    altera_jogador_atual(e,jogadoratual);
    numerojogadas = ((jognvazias - 2 ) / 2) ;
    altera_num_jogadas(e,numerojogadas );
}

//Auxiliar da função "ler" que lê a parte correspondente as jogadas
void ler_jogadas(ESTADO * e, FILE * fp) {
    char col1 ,col2;
    int lin1,lin2;
    JOGADA jog;
    int num_jogadas = obter_numero_de_jogadas(e); 
    int ultimo_jog = obter_ultimo_jogador(e);

    while ( fgetc(fp) != '\n' ) ;

    for (int i = 0 ; i < num_jogadas ; i++ ) {
        while ( fgetc(fp) != ':' ) ;
        if ( i == (num_jogadas - 1) && ultimo_jog == 1 ) {
            fscanf ( fp , " %c%d\n" , &col1 , &lin1 ) ;
            jog = (JOGADA) {.jogador1 = (COORDENADA){8- lin1,col1 - 'a'}, .jogador2={}};
        }   
        else {
            fscanf(fp," %c%d %c%d\n",&col1,&lin1,&col2,&lin2);
            jog = (JOGADA) {(COORDENADA){8 - lin1,col1 - 'a'}, (COORDENADA){8- lin2,col2 - 'a'}};
        }
        acrescenta_jogada(e,i,jog);
    }
           
}
   
void ler (ESTADO * e, char * nome_ficheiro) {
        FILE * fp = NULL;
        if ((fp = fopen(nome_ficheiro,"r"))) {
           
            ler_tabuleiro(e,fp);
            ler_jogadas(e,fp);
            mostrar_tabuleiro(e,stdout);
            if (e->jogador_atual == 1)
            e->num_jogadas = e->num_jogadas + 1;
            mostrar_jogadas(e,stdout);
           
        }
        else
            printf("Erro a ler ficheiro\n"); 
        fclose(fp);
    }
void guarda_estado(ESTADO * e, ESTADO * copia_estado) {

    if (!copia_estado) {
        copia_estado = malloc(sizeof(ESTADO));
    }
    for (int i= 0; i < 8; i++){
        for (int j = 0; j < 8; j++){    // Processo de guardar o tabuleiro atual
             copia_estado->tab[i][j] = obter_estado_casa(e,(COORDENADA) {i,j}); 
        }
    }

    for (int  i = 0 ; i <= 31 ; i++ ) {   // Processo de guardar as jogadas atuais
         copia_estado->jogadas[i] = e->jogadas[i];  
    }
    
}

void repor_estado(ESTADO *e, ESTADO * copia_estado) {

    for (int i= 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            e->tab[i][j] = copia_estado->tab[i][j];
        }
    }

  for (int  i = 0 ; i <= 31 ; i++ ) { 
       e->jogadas[i] = copia_estado->jogadas[i];
  }
  altera_num_jogadas(e,obter_numero_de_jogadas(copia_estado));


}


int pos(ESTADO * e, ESTADO * copia_estado, char * token) {
    int i = atoi(token);
    int numjogadaspos = 0; 
    if((i>=0)&&(i < obter_numero_de_jogadas(e)) && verificanumero(token[0])==1 ){
                        copia_estado->num_jogadas = obter_numero_de_jogadas(e);
                        altera_num_jogadas(e, (atoi(token) +1));
                        numjogadaspos = obter_numero_de_jogadas(e);
                        atualizapos(e);
                        e->regulapos = 1;
                        altera_num_jogadas(e,obter_numero_de_jogadas(copia_estado));
    }
    else{ 
        printf ("\nComando inválido\n") ;
        numjogadaspos = obter_numero_de_jogadas(e) + 1; 
    } 
    return numjogadaspos;
}

int interpretador(ESTADO *e) {
    int numjogadaspos = 0, t =0;
    ESTADO * estado_copia = calloc(1,sizeof(ESTADO)) ;
    char linha[BUF_SIZE], col[2], lin[2];
  
    mostrar_tabuleiro(e,stdout);

    while(t != 2) { 

        if (e->regulapos==1){
            altera_num_jogadas(e,numjogadaspos);
            mostrar_prompt (e);
            altera_num_jogadas(e,obter_numero_de_jogadas(estado_copia));
        }
        else
            mostrar_prompt (e); 

        if ((fgets(linha, BUF_SIZE, stdin) == NULL) || (!strcmp(linha,"Q\n")))
            return 0;

        else if (strlen(linha) == 3 && sscanf(linha, "%[a-h]%[1-8]", col, lin) == 2) {

                COORDENADA coord = { '8' - *lin , *col -'a'};

                if (e->regulapos == 1){
                    guarda_estado(e, estado_copia);
                    altera_num_jogadas(e,numjogadaspos -2);
                    altera_tabuleiro(e,1); 
                    apagajogpost(e); 
                    altera_num_jogadas(e, numjogadaspos);
                }
                t = jogar ( e , coord );
                
                if (t){
                    mostrar_tabuleiro(e,stdout);
                    e->regulapos = 0;
                }
                else if (e->regulapos == 1) {
                    repor_estado(e, estado_copia);
                    altera_num_jogadas(e,obter_numero_de_jogadas(estado_copia));
                }
        }

        else {
                char * token = strtok(linha," ");
                if(!strcmp(linha,"imprime\n")) mostrar_tabuleiro(estado_copia,stdout);
                 if (!strcmp(linha,"movs\n")) token = "movs";
                 if (!strcmp(linha,"jog\n")) token = "jog";
                COMANDO cmd = verifica_comando(token);
                if( cmd && (cmd == MOVS || cmd == JOG || (token = strtok(NULL, "\n")))) {
                    if(cmd == GRAVAR)
                        gravar(e,token);
                    if(cmd == LER)
                        ler(e,token);
                    if(cmd == MOVS) {
                       if (e->regulapos == 1){
                           altera_num_jogadas(e,numjogadaspos);
                           mostrar_jogadas(e,stdout);
                           altera_num_jogadas(e,obter_numero_de_jogadas(estado_copia));
                       }
                       else  
                            mostrar_jogadas(e,stdout);
                    }
                    if(cmd == POS) {
                        if (pos(e,estado_copia,token) <= obter_numero_de_jogadas(e))
                             numjogadaspos = pos(e, estado_copia ,token);    
                    }
                     if (cmd == JOG){
                        if (e->regulapos == 1){
                         guarda_estado(e, estado_copia);
                         altera_num_jogadas(e,numjogadaspos -2);
                         altera_tabuleiro(e,1); 
                         apagajogpost(e); 
                         altera_num_jogadas(e, numjogadaspos);
                        }

                        COORDENADA coordaefetuar;
                        coordaefetuar = estrategiaparidade(e);
                        jogar(e,coordaefetuar);
                        mostrar_tabuleiro(e,stdout);
                        e->regulapos = 0;

                 // minha AREA
                    }
                }      
                else {
                    printf ("inválido\n");
                    t = 3;
                }
        }
    
                  
        if(t != 3) incrementa_comandos(e);

    }

    free(estado_copia); 
    printarcampeao(e); 
    return 1;

}

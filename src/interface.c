#include <stdio.h>
#include "dados.h"
#include "logica.h"
#include <string.h>
#define BUF_SIZE 1024

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

void atualizapos(ESTADO *e){
       CASA tabcopia[8][8];
 
       e->jogador_atual = 1;//Padrão. O começo de uma nova jogada é sempre do jogador 1.
    
      for (int i= 0; i < 9 - 1; i++){
          for (int j = 0; j < 9-1; j++){
              tabcopia[i][j] = e->tab[i][j];
          }
      }
      e->num_jogadas = e->num_jogadas - 2;
      altera_tabuleiro(e,0);
      mostrar_tabuleiro(e,stdout);
 
      for (int i= 0; i < 9-1; i++){
          for (int j = 0; j < 9-1; j++){
              e->tab[i][j] = tabcopia[i][j];
          }
      }
    
      
      }                               


// Apaga (coloca a zero) jogadas posteriores da posição dada no comando pos.
// Apesar de termos funções que utilizam o "número de jogada" como ponto de paragem
// (tonando meio desnecessário essa etapa de "colocar a zero"),
// é de bom senso colocar a zero os índices que estãp para além da posição em que voltamos. Isto é,
// ao fazer "pos 2", é como se após a segunda rodada tudo fosse anulado, como se voltássemos no tempo.
// Por tanto, seria ligeiramente mal estar as antigas jogadas armazenadas ainda no array.
void apagajogpost(ESTADO *e){
              // em que havia passado apenas uma rodada, isto é, cada jogador
        
    JOGADA jog;
    int i;
    // O início que queremos zerar é a partir do "novo num_jogadas".
    // Novo porque a primeira coisa que foi alterada após o comando pos, foi o num_jogadas
    // para estar de acordo com o inserido.
    // A ideia aqui é acrescentar jogadas a 0.
    for ( i = e->num_jogadas + 1 ; i <= 31 ; i++ ) { 
        jog = (JOGADA) {.jogador1 = (COORDENADA){0,0}, .jogador2 =(COORDENADA){0,0}};
        acrescenta_jogada(e,i,jog);
    }
}

void altera_tabuleiro(ESTADO *e,int regulador){

     COORDENADA guardaultima = e->ultima_jogada;

      if (e-> num_jogadas != -1)
      e->ultima_jogada = obtem_coordenada(e,(e->num_jogadas),2);// Ex: Ao fazer "pos 1"(chamemos 1 de variável "n") queremos voltar para o momento 
      else (e->ultima_jogada = (COORDENADA) {3,4});
   
    for (int h = e ->num_jogadas + 1; h <= 31; h++){
        COORDENADA coord1 = obtem_coordenada(e,h,1);
        COORDENADA coord2 = obtem_coordenada(e,h,2);
      e->tab[coord1.linha][coord1.coluna] = VAZIO;
      e->tab[coord2.linha][coord2.coluna] = VAZIO;
    }   
    COORDENADA coord3 = e->ultima_jogada;
    e->tab[coord3.linha][coord3.coluna] = BRANCA;

    if (regulador == 0){
    e->ultima_jogada = guardaultima;
    }
}
       
//Mostra o prompt no ecrã como também o insere num ficheiro quando feito o comando "gr"
void mostrar_prompt (ESTADO * e, FILE * stream){
    int jogadoratual;
    int numerojogadas;
    int numerocomandos;   // Cada vez que uma rodada e jogadas acontece (ambos jogam) o numero de jogadas aumenta

    jogadoratual = obter_jogador_atual(e);
    numerojogadas = obter_numero_de_jogadas(e);
    numerocomandos = obter_numero_de_comandos (e);

    fprintf (stream,"\nPlayer: %d |Jogada: %d  |comandos: %d  > ", jogadoratual,numerojogadas,numerocomandos);    
   
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

    if ( fp = fopen(nome_ficheiro,"w+") ) {
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


int interpretador(ESTADO *e) {
    int numjogadaspos;
    int guarda_num_jogadas;

    char linha[BUF_SIZE];
    char col[2], lin[2];
    int t =0;
  
    mostrar_tabuleiro(e,stdout);

    while(t != 2) { 

        if (e->regulapos==1){
            e->num_jogadas = numjogadaspos;
            mostrar_prompt (e,stdout);
            e->num_jogadas = guarda_num_jogadas;
        }
        else
            mostrar_prompt (e,stdout); 

        if ((fgets(linha, BUF_SIZE, stdin) == NULL) || (!strcmp(linha,"Q\n")))
            return 0;

        else if (strlen(linha) == 3 && sscanf(linha, "%[a-h]%[1-8]", col, lin) == 2) {

                COORDENADA coord = { '8' - *lin , *col -'a'};
                if (e->regulapos == 1){
                    e->num_jogadas = numjogadaspos - 2;
                     altera_tabuleiro(e,1);
                    apagajogpost(e); 
                    e->num_jogadas = numjogadaspos ;                                          // fizera apenas 1 movimento cada. Por tanto, apenas o índice 0 do 
                }
                else{};
                t = jogar ( e , coord );
                if (t!=0){
                mostrar_tabuleiro(e,stdout);
                e->regulapos = 0;
                }
             }
	         else if (!strcmp(linha,"movs\n")){
                  if (e->regulapos == 1){
                     e->num_jogadas = numjogadaspos;
	                 mostrar_jogadas(e,stdout);
                     e->num_jogadas = guarda_num_jogadas;
                  }
                  else  mostrar_jogadas(e,stdout);
                  }
                  else {
                        char * token = strtok(linha," ");
                        COMANDO cmd = verifica_comando(token);

                        if(cmd && (token = strtok(NULL, "\n"))) {
                            if(cmd == GRAVAR)
                                gravar(e,token);

                            if(cmd == LER)
                                ler(e,token);
                              
                            int i = atoi(token);  
                            if((cmd == POS)&& (i>=0)&&(i< e->num_jogadas)){
                                guarda_num_jogadas = e->num_jogadas;
                                e->num_jogadas = atoi(token) + 1;// transforma a string que representa o número inserido, no próprio valor do inteiro
                                numjogadaspos = e->num_jogadas;
                                atualizapos(e);
                                e->regulapos = 1;
                                e->num_jogadas = guarda_num_jogadas;                           
                            }
                        }   

                        else {
                            printf ("Comando inválido\n");
                            t = 3;
                        }
             
                     }
                  

        if(t != 3) incrementa_comandos(e);
    }

    printarcampeao(e); 
    
    return 1;

}

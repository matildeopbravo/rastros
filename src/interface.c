#include <stdio.h>
#include "dados.h"
#include "logica.h"
#include <string.h>
#define BUF_SIZE 1024

void printarcampeao(ESTADO * estado){

    int campeao;
    int jogadoratual;
    
    COORDENADA ultimajogada;  
    ultimajogada  = (estado -> ultima_jogada);
    int linha,coluna;

    linha = ultimajogada.linha;
    coluna = ultimajogada.coluna;

    jogadoratual = estado -> jogador_atual;

    campeao = verifica_fim (estado,linha,coluna,jogadoratual);

    if (campeao==1) 
        printf ("Parabéns jogador 1, é o vencedor deste jogo!!!! \n");
    else 
        printf ("Parabéns jogador 2, é o vencedor deste jogo!!!! \n");
}

//Mostra o prompt no ecrã como também o insere num ficheiro quando feito o comando "gr"
void mostrar_prompt (ESTADO * e, FILE * stream){
    int jogadoratual;
    int numerojogadas;
    int numerocomandos;   // Cada vez que uma rodada e jogadas acontece (ambos jogam) o numero de jogadas aumenta

    jogadoratual = obter_jogador_atual(e);
    numerojogadas = obter_numero_de_jogadas(e);
    numerocomandos = obter_numero_de_comandos (e);

    fprintf (stream,"Player: %d |Jogada: %d  |comandos: %d  > ", jogadoratual,numerojogadas,numerocomandos);    
   
}
//Mostra o tabuleiro no ecrã como também o insere num ficheiro quando efetuado o comando "gr"
void mostrar_tabuleiro(ESTADO * estado, FILE * stream) {
    int i , j ;

    for ( i = 0 ; i < 8 ; i++ ) {
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
 fprintf (stream,"  abcdefgh\n");    
        
}
//Mostra o histórico de jogadas no ecrã como também os insere num ficheiro após efetuado ocomando "gr"
void mostrar_jogadas (ESTADO * e,  FILE * stream) {

    for(int i = 0; i <  obter_numero_de_jogadas(e); i++) {
        fprintf(stream," %d: ", i + 1);

        if(i == (obter_numero_de_jogadas(e) - 1) && obter_ultimo_jogador(e) == 1)
            fprintf(stream,"%s\n",obtem_jogada(e,i,1));
        else
            fprintf(stream,"%s %s\n",obtem_jogada(e,i,1), obtem_jogada(e,i,2));
    }
}

void gravar (ESTADO * e, char * nome_ficheiro) {
    FILE *  fp = NULL;
    if ((fp  = fopen(nome_ficheiro,"w+"))) {
            mostrar_tabuleiro(e,fp);
            fputc('\n',fp);
            mostrar_prompt(e,fp);
            fprintf(fp,"\n\n");
            mostrar_jogadas(e,fp);
            fputc('\n',fp);
            
    }
    else 
            printf("Erro a gravar ficheiro");

        fclose(fp);
    }

//Auxiliar da função "ler" que lê a parte correspondente ao prompt
void ler_prompt(ESTADO *e, FILE * fp){

 int numerojogadas, jogadoratual, numerocomandos;

        while(fgetc(fp) != 'P');
        fscanf(fp, "%*s %d %*s %d %*s %d" ,&jogadoratual,&numerojogadas,&numerocomandos);

        altera_jogador_atual(e,jogadoratual);
        altera_num_jogadas(e,numerojogadas);
        altera_numero_comandos(e,numerocomandos);

}

COMANDO verifica_comando( char * token ){
        if(!strcmp(token,"gr")) return GRAVAR;
        if(!strcmp(token,"ler")) return LER;
        return 0;
    }

//Auxiliar da função "ler" que lê a parte correspondente ao tabuleiro
void ler_tabuleiro(ESTADO * e, FILE * fp) {
    char ponto;
    for(int i = 0; i < 8 ; i++) {
    while(fgetc(fp) != ' ');
    for(int j = 0; (ponto = fgetc(fp)) != '\n'; j++) {
            if(ponto == '.') 
                altera_casa(e,(COORDENADA) {i,j} , VAZIO);
            else 
                altera_casa(e,(COORDENADA) {i,j} ,ponto);
            if(ponto == '*') altera_ultima_jogada(e,(COORDENADA){i,j});
                
            }
    }   
}

//Auxiliar da função "ler" que lê a parte correspondente as jogadas
void ler_jogadas(ESTADO * e, FILE * fp) {
    char col1 ,col2;
    int lin1,lin2;
    JOGADA jog;
    int num_jogadas = obter_numero_de_jogadas(e); 
    int ultimo_jog = obter_ultimo_jogador(e);

    for(int i = 0; i < num_jogadas; i++) {
        while(fgetc(fp) != ':');
        if(i == (num_jogadas- 1) && ultimo_jog == 1 ) {
            fscanf(fp," %c%d\n",&col1,&lin1);
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
            ler_prompt(e,fp);
            ler_jogadas(e,fp);
            mostrar_tabuleiro(e,stdout);
            mostrar_jogadas(e,stdout);
           
        }
        else
            printf("Erro a ler ficheiro\n"); 
        fclose(fp);
    }


int interpretador(ESTADO *e) {
    char linha[BUF_SIZE];
    char col[2], lin[2];
    int t =0;
  
    mostrar_tabuleiro(e,stdout);

    while(t != 2) { 
        mostrar_prompt (e,stdout);
        if ((fgets(linha, BUF_SIZE, stdin) == NULL) || (!strcmp(linha,"Q\n")))
            return 0;

        else if (strlen(linha) == 3 && sscanf(linha, "%[a-h]%[1-8]", col, lin) == 2) {

            COORDENADA coord = { '8' - *lin , *col -'a'};
            t = jogar ( e , coord );
            mostrar_tabuleiro(e,stdout);
            incrementa_comandos(e);
            
        }
	    else if (!strcmp(linha,"movs\n")) {
	        mostrar_jogadas(e,stdout);
            incrementa_comandos(e); 
       	}
        else {
            char * token = strtok(linha," ");
            COMANDO cmd = verifica_comando(token);

            if(cmd && (token = strtok(NULL, "\n"))) {
               if(cmd == GRAVAR){ 
                    gravar(e,token);
                    incrementa_comandos(e);
               }
               if(cmd == LER) {
                    ler(e,token);
                    incrementa_comandos(e);
                }
            }    
            else {
            printf ("Comando inválido\n");
            }
             
        }
    }
    printarcampeao(e); 
    
    return 1;
}

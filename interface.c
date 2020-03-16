#include <stdio.h>
#include "dados.h"
#include "logica.h"
#include <string.h>
#define BUF_SIZE 1024

void printarcampeao(ESTADO * estado){
    
    COORDENADA ultimajogada;  
    ultimajogada  = (estado -> ultima_jogada);
    int linha,coluna;

    linha = ultimajogada.linha;
    coluna = ultimajogada.coluna;

    if ( linha == 7 && coluna == 0 ) 
         printf ( "Parabéns jogador 1, é o vencedor deste jogo!!!! \n");
    else
        printf ( "Parabéns jogador 2, é o vencedor deste jogo!!!! \n");
}

void prompt (ESTADO * estado){
    int jogadoratual;
    int numerojogadas;   // Cada vez que uma rodada e jogadas acontece (ambos jogam) o numero de jogadas aumenta

    jogadoratual = estado -> jogador_atual;
    numerojogadas = estado -> num_jogadas;

    printf ("-> Player nº %d | Jogada nº %d > ", jogadoratual,numerojogadas);    
}

void mostrar_tabuleiro(ESTADO * estado, FILE * stream) {
    int i , j ;

    for ( i = 0 ; i < 8 ; i++ ) {
        fprintf (stream, "%d ", 8 - i);         // Printa o número de cada linha na tela
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

COMANDO verifica_comando( char * token ){
        if(!strcmp(token,"gr")) return GRAVAR;
        if(!strcmp(token,"ler")) return LER;
        return 0;
    }

void gravar (ESTADO * e, char * nome_ficheiro) {
        FILE *  file_pointer = NULL;

        if ((file_pointer = fopen(nome_ficheiro,"w+"))) 
             mostrar_tabuleiro(e,file_pointer);
        
        else 
            printf("Erro a gravar ficheiro");

        fclose(file_pointer);
    }

   
void ler (ESTADO * e, char * nome_ficheiro) {
        FILE *  file_pointer = NULL;

        if ((file_pointer = fopen(nome_ficheiro,"r"))) {
        //   fscanf(file_pointer,"%d %[^\n]");
        }
        printf("Erro a ler ficheiro\n");
    }


int interpretador(ESTADO *e) {
    char linha[BUF_SIZE];
    char col[2], lin[2];
    int t =0;

    mostrar_tabuleiro(e,stdout);

    while(t != 2) { 
        prompt (e);
        if ((fgets(linha, BUF_SIZE, stdin) == NULL) || (!strcmp(linha,"Q\n")))
            return 0;

        else if (strlen(linha) == 3 && sscanf(linha, "%[a-h]%[1-8]", col, lin) == 2) {

            COORDENADA coord = { '8' - *lin , *col -'a'};
            t = jogar ( e , coord );
            mostrar_tabuleiro(e,stdout);
            
        }
        else {
            char * token = strtok(linha," ");
            COMANDO cmd = verifica_comando(token);

            if(cmd && (token = strtok(NULL, "\n"))) {
               if(cmd == GRAVAR) gravar(e,token);
               if(cmd == LER) ler(e,token); 
            }
             
        }
    }
    printarcampeao(e); 
    
    return 1;
}

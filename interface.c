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
     {
    printf ( "Parabéns jogador 2, é o vencedor deste jogo!!!! \n");
     }
     
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
        fprintf (stream, "%d", 8 - i);         // Printa o número de cada linha na tela
        for ( j = 0 ; j < 8 ; j++ ) {
            if ( i == 0 && j == 7 ) 
                fputc(((obter_estado_casa(estado, (COORDENADA){i,j})) == VAZIO ? '2' : '#'),stream) ;
            else if  ( i == 7 && j == 0 ) 
                fputc(((obter_estado_casa(estado, (COORDENADA){i,j})) == VAZIO ? '1' : '#'),stream) ;
            else {
                if ((obter_estado_casa(estado, (COORDENADA){i,j})) == VAZIO) fputc('.',stream) ;
                else if((obter_estado_casa(estado, (COORDENADA){i,j})) == BRANCA) fputc('*',stream)  ;
                else fputc ('#',stream) ;
            }
            
            }
        fputc('\n',stream) ;
    }
 fprintf (stream," abcdefgh\n");    
        
}

int interpretador(ESTADO *e) {
    char linha[BUF_SIZE];
    char col[2], lin[2];
    int t =0;

    mostrar_tabuleiro(e,stdout);

    while(t != 2) { // enquanto t for 0;
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
            FILE * file_pointer = NULL;

            if(!strcmp(token,"gr")) {
                
                if((token = strtok(NULL, "\n")) && (*token != ' ')) {
                         file_pointer = fopen(token,"w+");
                         mostrar_tabuleiro(e,file_pointer);
                }
            }

            else if(!strcmp(token,"ler")) {
                if((token = strtok(NULL, "\n")) && (*token != ' ')) {
                    file_pointer = fopen(token,"r");
                }
         
            }
            else return 0;
            
            fclose(file_pointer);
          
        }
    }

    printarcampeao(e); 
    
    return 1;
}

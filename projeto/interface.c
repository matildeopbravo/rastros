#include <stdio.h>
#include <stdlib.h>
#include "dados.h"
#include "logica.h"
#include <string.h>
#define BUF_SIZE 1024

int verificanumero (char token){
    int res = 0;
    for (char a = '0';a <='9';a++) {
        if (token == a)
           res = 1;
    }
    return res;
}

void printarcampeao(ESTADO * estado){

    int campeao,jogadoratual;
    COORDENADA ultimajogada; 

    ultimajogada  = obtem_ultima_jogada(estado);
    jogadoratual = obter_jogador_atual(estado);

    campeao = verifica_fim (estado,ultimajogada.linha,ultimajogada.coluna,jogadoratual);

    if (campeao==1) 
        printf ("Parabéns jogador 1, é o vencedor deste jogo!!!! \n");
    else 
        printf ("Parabéns jogador 2, é o vencedor deste jogo!!!! \n");
}

void altera_tabuleiro(ESTADO *estado){
    
    int contador;
    COORDENADA coord1;
    COORDENADA coord2;

    /*Ciclo que coloca o tabuleiro todo a VAZIO*/
    for (int linha = 0;linha < 8;linha++){
        for (int coluna = 0; coluna < 8 ; coluna++){
            altera_casa(estado, (COORDENADA) {linha,coluna}, VAZIO);
        }
    }
    /*Casos especiais*/
    altera_casa(estado,(COORDENADA) {0,7}, DOIS );
    altera_casa(estado,(COORDENADA) {7,0}, UM );
    
    /* Caso especial em que se foi feito "pos 0"*/    
    if (obter_numero_de_jogadas(estado) == 0){
        altera_casa(estado,(COORDENADA) {3,4}, BRANCA);
        altera_ultima_jogada(estado, (COORDENADA) {3,4});
    }
    else {

        /*Ciclo que coloca a PRETO todas as casas do tabuleiro que já foram ocupadas até a e-nésima jogada*/
        for (contador = 0; contador < (obter_numero_de_jogadas(estado)) - 1; contador++){

            coord1 = obtem_coordenada(estado,contador,1);
            coord2 = obtem_coordenada(estado,contador,2);
            altera_casa(estado, coord1, PRETA);
            altera_casa(estado, coord2, PRETA);
        
        } 
        /* Caso o jogador atual for o 2, então falta preencher a BRANCO  a última jogada efetuada*/
        if (obter_jogador_atual(estado) == 2){
            coord1 = obtem_coordenada(estado,contador,1);
            altera_casa(estado,coord1, BRANCA);
            altera_ultima_jogada(estado, coord1);
        }
        /* Caso o jogador atual for o 1, então falta preencher a BRANCO ua última jogada efetuada*/
        if (obter_jogador_atual(estado) == 1){
            coord2 = obtem_coordenada(estado,contador - 1,2);
            altera_casa(estado,coord2,BRANCA);
            altera_ultima_jogada(estado,coord2);

        }
        /* Preenchimento da posição inicial a PRETO é sempre necessário, dado que ela não está presente em nenhuma das listas.
        apenas quando nenhuma jogada foi efetuada ainda é  que não devo fazer nada */
        if ((obter_numero_de_jogadas(estado) == 1 && obter_jogador_atual(estado) == 2)
        || (obter_numero_de_jogadas(estado) > 1)){
            altera_casa(estado, (COORDENADA) {3,4}, PRETA);
        }
    }
}


void mostrar_tabuleiro(ESTADO * estado, FILE * stream) {
    altera_tabuleiro(estado);
    /*Ciclo que printa na tela o tabuleiro mediante o contéudo do tabuleiro*/
    int i , j ;
    for ( i = 0 ; i < 8 ; i++ ) {
        if ( stream == stdout )
             fprintf (stream, "%d ", 8 - i);
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

void mostrar_prompt (ESTADO * e){
    int jogadoratual;
    int numerojogadas;
    int numerocomandos;   // Cada vez que uma rodada e jogadas acontece (ambos jogam) o numero de jogadas aumenta

    jogadoratual = obter_jogador_atual(e);
    numerojogadas = obter_numero_de_jogadas(e);
    numerocomandos = obter_numero_de_comandos (e);

    printf ("\nPlayer: %d |Jogada: %d  |comandos: %d  > ", jogadoratual,numerojogadas,numerocomandos);    
   
}
char * obtem_jogada(ESTADO * e, int indice_jogada, int jogador) {

    char * str = (char*) malloc(sizeof(int) + 2 * sizeof(char));
    COORDENADA c = obtem_coordenada(e,indice_jogada,jogador);
    // sprintf(str,"%c%d",c.coluna + 'a', 8 -  c.linha);
    sprintf(str,"%c%c",c.coluna + 'a',8 - c.linha + '0');
    return(str);

}

void mostrar_jogadas (ESTADO * e,  FILE * stream) {
    int numjogadas;
    if ( stream == stdout )
        fprintf (stream,"\n");

    if (obter_jogador_atual(e) == 1)
    numjogadas = obter_numero_de_jogadas(e)  - 1;
    else numjogadas = obter_numero_de_jogadas(e);

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
        if((obter_numero_de_jogadas(e) !=1) || (obter_jogador_atual(e) != 1))
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
    if(!strcmp(token,"jog2")) return  JOG2;
    return 0;
}


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

void ler_jogadas(ESTADO * e, FILE * fp) {
    char col1 ,col2, c;
    int lin1,lin2;
    JOGADA jog;
    int num_jogadas = obter_numero_de_jogadas(e); 
    int ultimo_jog = obter_ultimo_jogador(e);


    while ( (c = fgetc(fp)) != '\n' && c != EOF  ) ;

    for (int i = 0 ; i < num_jogadas; i++ ) {
        while ( fgetc(fp) != ':' ) ;
        if ( i == (num_jogadas - 1) && ultimo_jog == 1 ) {
            if (fscanf ( fp , " %c%d\n" , &col1 , &lin1 )){} ;
            jog = (JOGADA) {.jogador1 = (COORDENADA){8- lin1,col1 - 'a'}, .jogador2={0}};
        }   
        else {
            if (fscanf(fp," %c%d %c%d\n",&col1,&lin1,&col2,&lin2)){};
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
            if (obter_jogador_atual(e) == 1)
            altera_num_jogadas(e, obter_numero_de_jogadas(e) + 1);
            mostrar_tabuleiro(e,stdout);
            mostrar_jogadas(e,stdout);
               
            fclose(fp);
        }
        else {
        
            printf("Erro a ler ficheiro\n"); 
        }
}

int interpretador(ESTADO *e) {
    int t =0;
    char linha[BUF_SIZE], col[2], lin[2];
    int salva_num_jogadas = 0, salva_jogador_atual = 0;
  
    mostrar_tabuleiro(e,stdout);

    while(t != 2) { // t = 2 coorresponde a vitória

        if (devolve_flagpos(e) ==1){
           alterna_situacao_pos(&salva_num_jogadas,&salva_jogador_atual,e); 
        // guarda jogadas e jogador atual e altera o numero de jogadas para o valor de guardajogadaspos e o jogador atual para o jogado1
           mostrar_prompt (e); 
           recupera_valores(e,salva_jogador_atual,salva_num_jogadas);              
        }
        else
            mostrar_prompt (e); 
        /*leitura do que foi digitado pelo jogador */
        if ((fgets(linha, BUF_SIZE, stdin) == NULL) || (!strcmp(linha,"Q\n")))
            return -1;
        /*situações em que foi digitado algo*/
        // Situação em que foi digitado uma coordenada
        else if (strlen(linha) == 3 && sscanf(linha, "%[a-h]%[1-8]", col, lin) == 2) {

                COORDENADA coord = { '8' - *lin , *col -'a'};

                if (devolve_flagpos(e) == 1){
                    alterna_situacao_pos(&salva_num_jogadas,&salva_jogador_atual,e);                    
                    altera_tabuleiro(e);
                }

                t = jogar ( e,coord);                
                if (t){ // se a jogada for válida então o cenário muda
                    mostrar_tabuleiro(e,stdout);
                    altera_flag(e,0);
                }
                else if (devolve_flagpos(e) == 1) {

                     recupera_valores(e,salva_jogador_atual,salva_num_jogadas);
                }
        }
        // Situações em que foi digitado comandos
        else {
             char * token = strtok(linha," ");
             if (!strcmp(linha,"movs\n")) token = "movs";
             if (!strcmp(linha,"jog\n")) token = "jog";
             if (!strcmp(linha,"jog2\n")) token = "jog2";
            COMANDO cmd = verifica_comando(token);


            if( cmd && (cmd == MOVS || cmd == JOG || cmd == JOG2 || (token = strtok(NULL, "\n")))) {
                /*Situação em que foi digitado o comando gravar*/
        
                if(cmd == GRAVAR) {
                    if (devolve_flagpos(e) == 1){

                    alterna_situacao_pos(&salva_num_jogadas,&salva_jogador_atual,e);
                    altera_tabuleiro(e);
                    
                    }
                        gravar(e,token);

                    if (devolve_flagpos(e)== 1) {
                       recupera_valores(e,salva_jogador_atual,salva_num_jogadas);
                    }
                }

                /*Situação em que foi digitado o comando ler*/
                if(cmd == LER){
                    ler(e,token);
                    altera_flag(e,0);
                }

                /*Situação em que foi digitado o comando movs*/    
                if(cmd == MOVS) {
                    if (devolve_flagpos(e) == 1){

                        alterna_situacao_pos(&salva_num_jogadas,&salva_jogador_atual,e);   
                        mostrar_jogadas(e,stdout);
                        recupera_valores(e,salva_jogador_atual,salva_num_jogadas);
                    }
                    else  
                        mostrar_jogadas(e,stdout);
                }

                if(cmd == POS) {
                    int i = atoi(token);
                    if ((i>=0)&&(i < obter_numero_de_jogadas(e)) && verificanumero(token[0])==1 ) {   
                        salva_num_jogadas = obter_numero_de_jogadas(e); //variável local que repõe o num_jogadas original
                        altera_jogadas_pos(e,i);//componente da struct que armazena o que foi digitado no "Pos"

                        if (i!=0){
                            altera_num_jogadas(e,i+1);
                        }
                        else
                            altera_num_jogadas(e,0); 
                             
                        salva_jogador_atual = obter_jogador_atual(e);
                        altera_jogador_atual(e,1);
                        mostrar_tabuleiro(e,stdout);
                        recupera_valores(e,salva_jogador_atual,salva_num_jogadas);
                        altera_flag(e,1); //Flag de aviso que o comando pos foi dado
                    }  
                    else printf ("inválido\n");
                        
                }

                if((cmd == JOG || cmd == JOG2) && !(token = strtok(NULL,"\n"))) {

                        if (devolve_flagpos(e) == 1){
                            alterna_situacao_pos(&salva_num_jogadas,&salva_jogador_atual,e);
                            //Sei que a jogada nesse comando é sempre válida
                            altera_tabuleiro(e);
                        }

                        COORDENADA coordaefetuar;
                        coordaefetuar = cmd == JOG ? estrategia_paridade(e) : estrategia_floodfill(e);
                        t = jogar(e,coordaefetuar);
                        mostrar_tabuleiro(e,stdout);
                        altera_flag(e,0);
                }
            }      
            else {
                printf ("inválido\n");
                t = 3;
            }
        }
              
        if(t != 3) incrementa_comandos(e);
    }

    printarcampeao(e); 
    return 1;
    
}

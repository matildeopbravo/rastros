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

// Aqui, o argumento "regulador" irá regular e controlar se essa função está a ser chamada na situação de uma "Invocação de fachada"
// ou se já é mesmo para alterar os conteúdos de verdade. Caso o regulador for 0, então ainda não é para alterar tudo,
// nomeadamente a última jogada, que é uma componente da struct principal, deverá ser ainda a do jogo atual e nao da do jogo 
// inserido no comando pos. Por isso é guardado seu valor para no final de tudo, repor ele caso tal função tiver sido invocada num momento em que
// não era o conteúdo propriamente em si que iria ser mudado e apenas trabalhava  para funções que mostram na tela.
void altera_tabuleiro(ESTADO *e,int regulador){

     COORDENADA guardaultima = e->ultima_jogada;

      if (e-> num_jogadas != -1)
      e->ultima_jogada = obtem_coordenada(e,(e->num_jogadas),2);
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

void apagajogpost(ESTADO *e){
        
    JOGADA jog;
    int i;

    for ( i = e->num_jogadas + 1 ; i <= 31 ; i++ ) { 
        jog = (JOGADA) {.jogador1 = (COORDENADA){0,0}, .jogador2 =(COORDENADA){0,0}};
        acrescenta_jogada(e,i,jog);
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
    CASA tabcopia[8][8];
    JOGADA jogadascopia[32];

    char linha[BUF_SIZE];
    char col[2], lin[2];
    int t =0;
  
    mostrar_tabuleiro(e,stdout);

    while(t != 2) { 

// o número de jogadas no prompt será mostrado de acordo com o sinal da flag "regulapos"(sendo explicada sua função e papel na próxima secção do código).
// Caso a flag estuver ativa (sinal 1) então quer dizer que ainda não foi feito jogadas após o antigo comando "pos". Por tanto deve ser mostrado um "prompt" de fachada,
// isto é, onde o conteúdo dele não será fixo ainda, onde deverei mostrar o número de jogadas introduzido no comando pos anterior.
        if (e->regulapos==1){
// O número de jogadas introduzido no comando pos anterior foi guardado na variável numjogadaspos            
            e->num_jogadas = numjogadaspos;
            mostrar_prompt (e,stdout);
// Logo após mostrar o prompt adaptado a um "conteúdo maleável", devo retornar ao antigo conteúdo do número de jogadas,
// que está guardado na variável guarda_num_jogadas.            
            e->num_jogadas = guarda_num_jogadas;
        }
        else
// Caso a flag nao estiver ativada então o prompt a ser mostrado será normal.        
            mostrar_prompt (e,stdout); 

        if ((fgets(linha, BUF_SIZE, stdin) == NULL) || (!strcmp(linha,"Q\n")))
            return 0;

        else if (strlen(linha) == 3 && sscanf(linha, "%[a-h]%[1-8]", col, lin) == 2) {

                COORDENADA coord = { '8' - *lin , *col -'a'};
                if (e->regulapos == 1){
// Este "if" é a chave do funcionamento do comando "pos". Se após ser feito o comando pos, ser introduzida uma nova jogada,
// então o jogo deverá continuar a partir dai(o tal do novo cenário). Mas para ser feita tal jogada, ela se deve basear num "conteúdo
//do jogo" correspondente a essa jogada dada no comando pos anterior. Assim este if , caso a flag estiver ativada, irá fazer o jogo
// voltar no tempo, de modo a jogada a ser feita já tenha em conta o antigo jogo.   

// Uma coisa que deve ser garantida é: caso a jogada efetuada não for válida, então voltamos a estaca zero.
// Ou seja, ainda podemos ter a situação do "novo cenário" não ser esse ainda. Por isso, antes de ativar a função
//que irá realizar a jogada mediante o antigo jogo, deverei guardar as informações do tabuleiro de das jogadas do 
// jogo atual, para caso a jogada não ser válida, não perder o contéudo.
                    for (int i= 0; i < 9 - 1; i++){
                        for (int j = 0; j < 9-1; j++){    // Processo de guardar o tabuleiro atual
                        tabcopia[i][j] = e->tab[i][j];
                         }
                    }

                    for (int  i = 0 ; i <= 31 ; i++ ) {   // Processo de guardar as jogadas atuais
                        jogadascopia[i] = e->jogadas[i];
                    }

// Agora sim, após garantir o tabuleiro e jogadas atuais guardadas, poderei executar as alterações em tais locais,
//Para a função "jogar" receber um estado do jogo novinho em folha, correspondente a quando o jogo estava
// na jogada inserida no comando pos anterior. O número de jogadas possui essa subtração por 2 por conta de
// sua funcionalidade dentro das funções que alteram o tabuleiro e as jogadas (sua compreensão é melhor ser feita dentro da 
//função respetiva)

                    e->num_jogadas = numjogadaspos - 2;
                    altera_tabuleiro(e,1); // o argumento 1 será está explicado na função.
                    apagajogpost(e); 
// Como aquela subtração no número de jogadas tinha um propósito apenas dentro das funções anteriores, então agora
// metemos de volta o número de jogadas certo, correspondente aquele inserido no comando pos anterior.
// Tal número está guardado na variável numjogadaspos.
                    e->num_jogadas = numjogadaspos;                                          // fizera apenas 1 movimento cada. Por tanto, apenas o índice 0 do 
                }
                else{};
                t = jogar ( e , coord );
                
                if (t!=0){
// Aqui é o caso em que a jogada foi efetuada com sucesso, por tanto um novo cenário já está colocado, sendo desnecessário voltar ao antigo.
                mostrar_tabuleiro(e,stdout);
// Reparemos que aqui é o momento em que a flag volta a ser 0, permitindo então a situação de "um novo"
                e->regulapos = 0;
                }
                else if (e->regulapos == 1) {
// Porém... Caso a jogada não ter tido sucesso, e não ser válida então ainda é possível o jogador fazer um comando pos para putro momento do jogo.
// Por isso foi guardado os contéudos antigos dos tabuleiros e jogadas em arrays auxiliares, pois agora tais locais serão repostos, caso
// o momento do jogo a voltar mudar.                    

// Processo de repor o tabuleiro.                    
                for (int i= 0; i < 9-1; i++){
                      for (int j = 0; j < 9-1; j++){
                        e->tab[i][j] = tabcopia[i][j];
                        }
                    }
// Prcoesso de repor as jogadas
                for (int  i = 0 ; i <= 31 ; i++ ) { 
                    e->jogadas[i] = jogadascopia[i];
                    }
// Processo de repor o número de jogadas.
                 e->num_jogadas = guarda_num_jogadas;
                }
             }
	         else if (!strcmp(linha,"movs\n")){

// Assim como nas situações anteriores, a lista de movimentos a ser mostrada irá depender do sinal da flag.
// Caso ela ser 1, deverá ser mostrado os movimentos de "fachada", ou seja, aqueles que se limitam a jogada inserida
// no comando pos, sem alterar o contéudo em si. Assim é trocada o número de jogadas, pois tal componente que será o ponto
// e paragem da função que mostra as jogadas.
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
// Guarda o número de jogadas da partida atual caso o comando "pos" seja inserido diversas vezes seguidos (wentão o ponto de referência deve ser o mesmo)
                                guarda_num_jogadas = e->num_jogadas; 
// Novo número de jogadas mediante o que foi dado no comando. É "+ 1" porque por ex: uma vez dado "pos 2", você quer voltar para                            
// quando havia sido feito 2 jogadas e o número de jogadas então (a ser mostrado no prompt) será a jogada atual: 3.                                
                                e->num_jogadas = atoi(token) + 1;
// A variável "numjogadaspos" irá guardar o numero da jogada atual obtido com o comando "Pos". Isto porque tal número "não será fixo a priori",
// dado que o cenário do jogo só realmente muda quando é feito uma jogada após o comando "Pos". Por tanto após esta seccção do código
// acabar, o número de jogadas voltará a ser o mesmo de antes, porém como a próxima coisa a ser feita poderá ser uma jogada, isto é, uma mudança do cenário,
// Então deverei fazer "começar um jogo de novo" a partir da jogada inserida do "comando pos anterior"- jogada a qual está guardada em tal variável numjogadaspos.
                                numjogadaspos = e->num_jogadas;
// Diferente do que tinha anteriormente, este "atualizapos" será apenas uma função de "fachada". O que queremos aqui é apenas mostrar na tela 
// O jogo em tal jogada inserida. O conteúdo do jogo em si ainda não deve mudar dado que não sabemos ainda se será a apartir desse cenário que o jogo
// continuará(isso dependerá da próxima jogada). Por tanto, tal função está mais atenuada, sendo melhor explicada em seu devido espaço.                                
                                atualizapos(e);
// Após ter sido feito um comand pos, a componenre do regulapos na struct do estado do jogo será mudada. Isto porque ela foi introduzida
//Justamente como "flag" de aviso para as demais parte desta função saber que ao mostrar na tela o jogo, deverá ter em conta se o jogo a ser 
//mostrado será "um jogo apenas de fachada", isto é, sem conteúdo mudado em si e apenas na tela uma jogada anterior, ou se já é mesmo um jogo contínuo, 
// em que são feitas jogadas e os contéudos da struct principal devem ser mudados.                                
                                e->regulapos = 1;
// Como dito anteriormente, após sair desta seccção da função, não sabemos ainda se será a aprtir da jogada introduzida no comando que o jogo deve continuar.
//Devemos então deixar em aberto a hipótese de serem feitos outros comandos "pos" e para isso deve ter em conta o antigo número de jogadas como base.                                
                                e->num_jogadas = guarda_num_jogadas;                           
                            }
                            else if (cmd == POS) printf ("\ncomando inválido\n") ;
                         
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

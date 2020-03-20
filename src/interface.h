#ifndef CAMADA_INTERFACE_H
#define CAMADA_INTERFACE_H

void mostrar_tabuleiro(ESTADO * estado, FILE * stream);

void mostrar_prompt(ESTADO * e,FILE * file_pointer);

void mostrar_jogadas (ESTADO * e,  FILE * stream);

void printar_campeao(ESTADO * estado);

void prompt (ESTADO * estado);

int interpretador(ESTADO *e);

COMANDO verifica_comando( char * token );

void ler_tabuleiro(ESTADO * e, FILE * fp);

void ler_jogadas(ESTADO * e, FILE * fp);

void ler_prompt(ESTADO *e,char * file_pointer);

void gravar (ESTADO * e, char * nome_ficheiro);

void ler (ESTADO * e, char * nome_ficheiro);

#endif
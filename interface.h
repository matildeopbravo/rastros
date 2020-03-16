#ifndef CAMADA_INTERFACE_H
#define CAMADA_INTERFACE_H

void mostrar_tabuleiro(ESTADO * estado, FILE * stream);

void printarcampeao(ESTADO * estado);

void prompt (ESTADO * estado);

int interpretador(ESTADO *e);

COMANDO verifica_comando( char * token );

void gravar (ESTADO * e, char * nome_ficheiro);

void ler (ESTADO * e, char * nome_ficheiro);

#endif

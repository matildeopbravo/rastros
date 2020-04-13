#ifndef LISTAS_H
#define LISTAS_H

typedef struct lista {
    void * valor; 
    LISTA prox;
} *LISTA;

LISTA criar_lista();
LISTA insere_cabeca(LISTA L, void *valor);
void * devolve_cabeca(LISTA L);
LISTA proximo(LISTA L);
LISTA remove_cabeca(LISTA L);
int lista_esta_vazia(LISTA L);

#endif

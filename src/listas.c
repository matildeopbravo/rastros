#include <stdio.h>
#include <stdlib.h>
#include "listas.h"

LISTA criar_lista() {
    return NULL;
 }

LISTA insere_cabeca(LISTA L, void *valor) {

    LISTA novo = malloc(sizeof(struct lista));
    novo->valor = valor;
    novo->prox = L;

    return novo;
}
void * devolve_cabeca(LISTA L) {
    
    return L->valor;
}

LISTA proximo(LISTA L) {
   return L->prox; 
}
LISTA remove_cabeca (LISTA L) {
    LISTA r = L;
    free(L);
    return r->prox;
}

int lista_esta_vazia(LISTA L) {
    return(!L);
}

    

 

#include <stdio.h>
#include <stdlib.h>
#include "listas.h"
#include "dados.h"

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
    if(!L) return NULL;
    LISTA r = L -> prox;
    free(L);
    return r;
}

int lista_esta_vazia(LISTA L) {
    return(!L);
}

int comprimento_lista(LISTA L) {
    int i = 0;
    for(     ; L ; L = L-> prox,i++);        
    return i;
    
}
void liga_lista(LISTA Lprincipal, LISTA Lacrescenta) {
    Lprincipal->prox=Lacrescenta;
}


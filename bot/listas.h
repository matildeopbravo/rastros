/**
@file listas.h
Definição da lista ligada que armazena as possíveis jogadas a serem efetuadas e funções úteis para tal.
*/

#ifndef LISTAS_H
#define LISTAS_H
/**
\brief Lista que vai armazenar as possíveis jogadas a se efetuar
*/
typedef struct lista {/** apontador para um valor de qualquer tipo*/
    void * valor;  /** apontador para o proximo elemento da lista*/
    struct lista *  prox;
} *LISTA;
/**
\brief Inicializa uma lista ligada
*/
LISTA criar_lista();
/**
\brief Insere um elemento na lista ligada(na primeira posição)
*/
LISTA insere_cabeca(LISTA L, void *valor);
/**
\brief Devolve o primeiro valor da lista ligada
*/
void * devolve_cabeca(LISTA L);
/**
\brief Devolve o endereço da segunda componente da lista ligada
*/
LISTA proximo(LISTA L);
/**
\brief remove o primeiro elemento da lista ligada
*/
LISTA remove_cabeca(LISTA L);
/**
\brief verifica se a lista está vazia. Devolve 1 se estiver
*/
int lista_esta_vazia(LISTA L);

/**
\brief Calcula o comprimento da lista ligada
*/
int comprimento_lista(LISTA L); 
    
#endif

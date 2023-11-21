#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pilha_int.h"

void pilha_int_inicializar(struct pilha_int *p){
    p->p = NULL;
    p->tam = 0;
    p->topo = 0;
}

void pilha_int_empilhar(struct pilha_int *p, const int num){

    if (p->topo == p->tam){
        int *auxptr = NULL;
        p->tam += PILHA_TAM_INCREMENTO;
        auxptr = realloc(p->p, p->tam*sizeof(int));
        if (auxptr == NULL){
            fprintf(stderr, "Erro alocando pilha de inteiros! Abortando programa...\n");
            exit(0);
        }
        p->p = auxptr;
    }
    p->p[p->topo++] = num;
}

int pilha_int_topo(struct pilha_int *p){
    if (p->topo > 0)
        return p->p[p->topo-1];
    else {
        fprintf(stderr, "Pilha de inteiros vazia não tem topo!\n");
        exit(1);
    }
    return 0;
}

int pilha_int_vazia(struct pilha_int *p){
    return p->topo == 0;
}

void pilha_int_desempilhar(struct pilha_int *p){
    p->topo--;
}

void pilha_int_destruir(struct pilha_int *p){
    p->topo = 0;
    p->tam = 0;
    free(p->p);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../tabela_simb/simbolo.h"
#include "pilha_simb_ptr.h"

void pilha_simb_ptr_inicializar(struct pilha_simb_ptr *p){
    p->p = NULL;
    p->tam = 0;
    p->topo = 0;
}

void pilha_simb_ptr_empilhar(struct pilha_simb_ptr *p, struct simbolo * simb){

    if (p->topo == p->tam){
        struct simbolo **auxptr = NULL;
        p->tam += PILHA_TAM_INCREMENTO;
        auxptr = realloc(p->p, p->tam*sizeof(struct simbolo *));
        if (auxptr == NULL){
            fprintf(stderr, "Erro alocando pilha de inteiros! Abortando programa...\n");
            exit(0);
        }
        p->p = auxptr;
    }
    p->p[p->topo++] = simb;
}

struct simbolo *pilha_simb_ptr_topo(struct pilha_simb_ptr *p){
    if (p->tam > 0)
        return p->p[p->topo-1];
    else {
        fprintf(stderr, "Pilha de inteiros vazia não tem topo!\n");
        exit(1);
    }
    return NULL;
}

int pilha_simb_ptr_vazia(struct pilha_simb_ptr *p){
    return p->topo == 0;
}

void pilha_simb_ptr_desempilhar(struct pilha_simb_ptr *p){
    p->topo--;
}

void pilha_simb_ptr_destruir(struct pilha_simb_ptr *p){
    p->topo = 0;
    p->tam = 0;
    free(p->p);
}

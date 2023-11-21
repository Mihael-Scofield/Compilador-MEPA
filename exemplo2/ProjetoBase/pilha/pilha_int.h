#ifndef __PILHA__
#define __PILHA__

#define PILHA_TAM_INCREMENTO 1024
#define PILHA_MAX_TAM_STRING 32

struct pilha_int {
    int *p;
    unsigned int tam;
    unsigned int topo;
};

void pilha_int_inicializar(struct pilha_int *p);

void pilha_int_empilhar(struct pilha_int *p, const int num);

int pilha_int_topo(struct pilha_int *p);

int pilha_int_vazia(struct pilha_int *p);

void pilha_int_desempilhar(struct pilha_int *p);

void pilha_int_destruir(struct pilha_int *p);

#endif
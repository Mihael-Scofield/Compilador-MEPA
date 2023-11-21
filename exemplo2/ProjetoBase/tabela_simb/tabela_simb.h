#ifndef __TABELA_SIMB__
#define __TABELA_SIMB__

#include <stdbool.h>

#include "simbolo.h"

struct tabela_de_simbolos{
    struct simbolo *simbolos;
    unsigned int qtd;
    unsigned int tam;
};


void inicializa(struct tabela_de_simbolos **ts);

void push(struct tabela_de_simbolos **ts, struct simbolo);

struct simbolo pop(struct tabela_de_simbolos **ts) ;

void remove_n(struct tabela_de_simbolos **ts, int n);

struct simbolo *busca(struct tabela_de_simbolos **ts, const char *nome);

void atribui_tipo(struct tabela_de_simbolos **ts, int categoria, int tipo, int qtd);

#endif

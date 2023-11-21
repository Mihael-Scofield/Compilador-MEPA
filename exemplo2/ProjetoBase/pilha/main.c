#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pilha_int.h"

int main(){

    struct pilha_int pilha;

    pilha_int_inicializar(&pilha);

    pilha_int_empilhar(&pilha, 1);

    pilha_int_empilhar(&pilha, 2);

    printf("A string: %02d\n", pilha_int_topo(&pilha));

    pilha_int_desempilhar(&pilha);
    printf("A string: %02d\n", pilha_int_topo(&pilha));

    pilha_int_desempilhar(&pilha);
    if (pilha_int_vazia(&pilha))
        printf("Pilha vazia\n");
    else 
        printf("A string: %2d\n", pilha_int_topo(&pilha));

    pilha_int_destruir(&pilha);

    return 0;
}
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ts.h"

#define DEBUG 1

void tabela_simbolos_init(tabela_simbolos* ts){
   printf("tabela_simbolos_init\n\n\n\n");
   ts->topo=0;
}

void tabela_simbolos_push(tabela_simbolos* ts, int nv_lex, char* ident_name){
   #ifdef DEBUG
      printf ("tabela_simbolos_push: token %s e %d addrs %p.\n", ident_name, ts->topo, &ts);
   #endif
   t_simbolo* pilha_aux;
   
   // pilha_aux = &(ts.pilha[ts.topo]);
   strcpy(ts->pilha[ts->topo].nome, ident_name);
   ts->pilha[ts->topo].nv_lex=nv_lex;

   printf(" ts topo antes %d\n", ts->topo);
   ts->topo = ts->topo + 1;
   printf(" ts topo depois %d\n", ts->topo);

   // print_pilha(ts);
   return;
}

void print_pilha(tabela_simbolos ts){
   printf("Pilha: ");
   for(int i=0; i < ts.topo; i++){
      printf("%d - [%s], ", i, ts.pilha[i].nome);
   }
   printf(" - tamanho pilha %d\n", ts.topo);
   return;
}

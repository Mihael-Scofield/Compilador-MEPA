#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "compilador.h"
#include "compilador.tab.h"
#include "ts.h"

#define DEBUG 1

void tabela_simbolos_init(tab_simbolos* ts){
   ts->topo=0;
   #ifdef DEBUG
      printf("tabela_simbolos_init\n");
      print_tabela_simbolos(*ts);
   #endif
   
   return;
}


void tabela_simbolos_push(tab_simbolos* ts, char* ident_name,  cat_simb categoria,  int nv_lex, int off_set){
   if(ts->topo==TAM_TS){
      fprintf(stderr, "Muitos Simbolos no Programa corrente. Reajustar numero máximo de simbolos\n");
      exit(-1);
   }
   
   t_simbolo* pilha_aux;
   
   // pilha_aux = &(ts.pilha[ts.topo]);
   strcpy(ts->pilha[ts->topo].identificador, ident_name);
   ts->pilha[ts->topo].categoria=categoria;
   ts->pilha[ts->topo].nv_lex=nv_lex;
   ts->pilha[ts->topo].off_set=off_set;
   ts->pilha[ts->topo].tipo= desc_type;
   ts->topo = ts->topo + 1;

   #ifdef DEBUG
      printf ("tabela_simbolos_push: token %s e %d addrs %p.\n", ident_name, ts->topo, &ts);
      print_tabela_simbolos(*ts);
   #endif

   return;
}

void tabela_simbolos_atualiza_tipo_ultimas_vs(tab_simbolos* ts,  simb_en_type tipo){
   for(int i=1; i<=ts->topo; i++){
      t_simbolo* simb = &ts->pilha[ts->topo-i];
      if (simb->categoria == var_simples){
         simb->tipo= tipo;
      }
      else{
         break;
      }
   }

   #ifdef DEBUG
      printf ("tabela_simbolos_atualiza_tipo:.\n");
      print_tabela_simbolos(*ts);
   #endif

   return;
}

int tabela_simbolos_remove_vs_ultimo_nv_lex(tab_simbolos* ts){
   int num_vars = 0;
   int nv_lex = ts->pilha[ts->topo-1].nv_lex;
   for(int i=1; i<=ts->topo; i++){
      t_simbolo* simb = &ts->pilha[ts->topo-i];
      if (simb->categoria == var_simples && simb->nv_lex ==nv_lex){
         num_vars++;
      }
      else{
         break;
      }
   }
   ts->topo = ts->topo - num_vars;

   #ifdef DEBUG
      printf ("tabela_simbolos_remove_vs_ultimo_nv_lex:.\n");
      print_tabela_simbolos(*ts);
   #endif

   return num_vars;
}

int tabela_simbolos_busca_simbolo(tab_simbolos* ts, char* identificador){
   int nv_lex = ts->pilha[ts->topo-1].nv_lex;
   for(int i=1; i<=ts->topo; i++){
      t_simbolo* simb = &ts->pilha[ts->topo-i];
      if (strcmp(simb->identificador, identificador) == 0){
         #ifdef DEBUG
            printf ("tabela_simbolos_busca_simbolo: Simbolo identificado.\n");
            print_simbolo(*simb);
         #endif
         return ts->topo-i;
      }
   }
   fprintf(stderr, "Erro léxico (%d,%d):Simbolos/Variável \"%s\" não identificada no contexto.\n", nl, nc, identificador);
   exit(-1);
   return -1;
}

void print_tabela_simbolos(tab_simbolos ts){
   printf("Tabela de Simbolos: (topo:%d)\n", ts.topo);
   for(int i=0; i < ts.topo; i++){
      printf("%d - ", i);
      print_simbolo(ts.pilha[i]);
   }
   return;
}


void print_simbolo(t_simbolo simb){
   printf("Ident [%s], ", simb.identificador);
   if(simb.categoria == var_simples){
      printf("CAT [VS], ");
   }
   printf("nv_lex %d, deslocamento %d, ", simb.nv_lex, simb.off_set);
   if(simb.tipo == integer_type){
      printf("TIPO [ inteiro ]");
   }
   printf("\n");
   return;
}
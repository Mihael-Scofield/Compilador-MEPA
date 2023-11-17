#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "compilador.h"
#include "ts.h"

#define DEBUG 1

void tabela_simbolos_init(tab_simbolos* ts){
   ts->topo=-1;
   
   return;
}

void tabela_simbolos_push(tab_simbolos* ts, char* ident_name,  cat_simb categoria,  int nv_lex, int off_set, vs_type tipo, char* rotulo){
   if(ts->topo==TAM_TS){
      fprintf(stderr, "Muitos Simbolos no Programa corrente. Reajustar numero máximo de simbolos\n");
      exit(-1);
   }
   
   t_simbolo* pilha_aux;
   
   ts->topo = ts->topo + 1;
   // pilha_aux = &(ts.pilha[ts.topo]);
   strcpy(ts->pilha[ts->topo].identificador, ident_name);
   ts->pilha[ts->topo].categoria=categoria;
   ts->pilha[ts->topo].nv_lex=nv_lex;
   ts->pilha[ts->topo].off_set=off_set;
   ts->pilha[ts->topo].tipo= tipo;

   return;
}

void tabela_simbolos_atualiza_tipo_ultimas_vs_ou_pf(tab_simbolos* ts,  vs_type tipo){
   cat_simb cat; 
   cat = ts->pilha[ts->topo].categoria;
/*   if (cat!=var_simples && cat!=param_formal){*/
/*      fprintf(stderr, "Erro do Compilador (%d,%d):\n tabela_simbolos_atualiza_tipo_ultimas_vs_ou_pf: tentativa de atribuir tipos a algo diferente de vs ou pf.\n", nl, nc);*/
/*   }*/

   for(int i=ts->topo; i>-1; i--){
      t_simbolo* simb = &ts->pilha[i];
      if (simb->categoria == cat && simb->tipo == desc_type){
         simb->tipo= tipo;
      }
      else{
         break;
      }
   }

   return;
}
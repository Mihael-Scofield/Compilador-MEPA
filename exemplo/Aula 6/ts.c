#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "compilador.h"
#include "compilador.tab.h"
#include "ts.h"

#define DEBUG 1

void tabela_simbolos_init(tab_simbolos* ts){
   ts->topo=-1;
   #ifdef DEBUG
      printf("tabela_simbolos_init\n");
      print_tabela_simbolos(*ts);
   #endif
   
   return;
}

vs_type map_simbolo_vs_type(int simb){
   if (simb == simb_integer){
      return integer_type;
   }
   return desc_type;
}


void tabela_simbolos_push(tab_simbolos* ts, char* ident_name,  cat_simb categoria,  int nv_lex, int off_set, vs_type tipo){
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

   #ifdef DEBUG
      printf ("tabela_simbolos_push: token %s e %d addrs %p.\n", ident_name, ts->topo, &ts);
      print_tabela_simbolos(*ts);
   #endif

   return;
}

void tabela_simbolos_atualiza_tipo_ultimas_vs(tab_simbolos* ts,  vs_type tipo){
   for(int i=0; i<ts->topo+1; i++){
      t_simbolo* simb = &ts->pilha[ts->topo-i];
      if (simb->categoria == var_simples){
         simb->tipo= tipo;
      }
      else{
         break;
      }
   }

   // #ifdef DEBUG
   //    printf ("tabela_simbolos_atualiza_tipo:.\n");
   //    print_tabela_simbolos(*ts);
   // #endif

   return;
}

int tabela_simbolos_remove_vs_ultimo_nv_lex(tab_simbolos* ts){
   int num_vars = 0;
   int nv_lex = ts->pilha[ts->topo].nv_lex;
   for(int i=0; i<ts->topo+1; i++){
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
   int nv_lex = ts->pilha[ts->topo].nv_lex;
   for(int i=0; i<ts->topo+1; i++){
      t_simbolo* simb = &ts->pilha[ts->topo-i];
      if (strcmp(simb->identificador, identificador) == 0){
         #ifdef DEBUG
            printf ("tabela_simbolos_busca_simbolo: Simbolo identificado.\n");
            print_simbolo(*simb);
         #endif
         if (simb->categoria==proc_cs){
            fprintf(stderr, "Erro léxico (%d,%d): Procedimento \"%s\" não pode ser alvo de atribuição.\n", nl, nc, identificador);
         }
         if (simb->categoria==param_formal){
            fprintf(stderr, "Erro léxico (%d,%d): Parametro Formal \"%s\" não pode ser alvo de atribuição.\n", nl, nc, identificador);
         }
         return ts->topo-i;
      }
   }
   fprintf(stderr, "Erro léxico (%d,%d):Simbolos/Variável \"%s\" não identificada no contexto.\n", nl, nc, identificador);
   exit(-1);
   return -1;
}

int ts_push_pi_cat_nvlex_tipo(tab_simbolos* ts, pilha_ident* pi, cat_simb cat, int nv_lex, vs_type tipo){
   int num_var = pi->topo+1;
   int off_set;
   if(ts->topo>-1 && nv_lex== ts->pilha[ts->topo].nv_lex){
      off_set = ts->pilha[ts->topo].off_set;
   }
   else{
      off_set=-1;
   }

   for(int i=0; i<num_var; i++){
      off_set++;
      tabela_simbolos_push(ts, pi->pilha[i], cat, nv_lex, off_set, desc_type);
   }
   tabela_simbolos_atualiza_tipo_ultimas_vs(ts, tipo);
   pilha_identificador_reset(pi);
   #ifdef DEBUG
      printf ("ts_push_pi_cat_nvlex_tipo:.");
      print_tabela_simbolos(*ts);
   #endif
   return num_var;
}

void print_tabela_simbolos(tab_simbolos ts){
   printf("Tabela de Simbolos: (topo:%d e tamanho: %d)\n", ts.topo, ts.topo+1);
   for(int i=0; i < ts.topo+1; i++){
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

/*PILHA não sei se coloco em outro arquivo ainda*/
void pilha_identificador_push(pilha_ident* pi, char*  identi){
   pi->topo++;
   strncpy(pi->pilha[pi->topo], identi, TAM_TOKEN);
   #ifdef DEBUG
      printf ("pilha_identificador_push:.\n");
      print_pilha_identificador(pi);
   #endif
   return;
}

void pilha_identificador_pop_n(pilha_ident* pi, int n){
   pi->topo = pi->topo - n;
   return;
}

void pilha_identificador_reset(pilha_ident* pi){
   pi->topo =-1;
   return;
}

void print_pilha_identificador(pilha_ident* pi){
   for (int i=0; i<pi->topo; i++){
      printf("[%d] - %s \n", i, pi->pilha[i]);
   }
   return;
}
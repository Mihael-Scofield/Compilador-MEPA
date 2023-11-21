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
   switch (simb){
      case simb_integer:
         return integer_type;
      case simb_boolean:
         return bool_type;
      default:
         return desc_type;
   }
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
      if (simb->categoria == var_simples && simb->tipo == desc_type){
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


void map_simbolos_comando_relacao(int simb){
   switch (simb){
      case simb_igual:
         geraCodigo (NULL, "CMIG");
         return;
      case simb_diferente:
         geraCodigo (NULL, "CMDG");
         return;
      case simb_menor_igual_que:
         geraCodigo (NULL, "CMEG");
         return;
      case simb_maior_igual_que:
         geraCodigo (NULL, "CMAG");
         return;
      case simb_menor_que:
         geraCodigo (NULL, "CMME");
         return;
      case simb_maior_que:
         geraCodigo (NULL, "CMMA");
         return;
      default:
         fprintf(stderr, "Simbolos Relacional não identificado. ERRO DE COMPILADOR!!!!\n");
         return;
   }
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

   switch (simb.tipo){
      case integer_type:
         printf("TIPO [ inteiro ]");
         break;
      case bool_type:
         printf("TIPO [ booleano ]");
         break;
      default:
         break;;
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


/*PILHA não sei se coloco em outro arquivo ainda*/
void pilha_vs_type_push(pilha_vs_type* pi, vs_type tipo){
   pi->topo++;
   pi->pilha[pi->topo]=tipo;
   #ifdef DEBUG
      printf ("pilha_vs_type_push:.\n");
      print_pilha_vs_type(pi);
   #endif
   return;
}

vs_type pilha_vs_type_pop(pilha_vs_type* pi){
   int aux = pi->topo;
   pi->topo = aux - 1;
   return pi->pilha[aux];
}

void pilha_vs_type_reset(pilha_vs_type* pi){
   pi->topo =-1;
   return;
}

void print_pilha_vs_type(pilha_vs_type* pi){
   for (int i=0; i<pi->topo+1; i++){
      switch (pi->pilha[i]){
      case integer_type:
         printf("[ inteiro ]");
         break;
      case bool_type:
         printf("[ booleano ]");
         break;
      default:
         break;;
      }
   }
   printf("\n");
   return;
}

void resolveTipoTermoFatores(pilha_vs_type* piT, pilha_vs_type* piF){
   vs_type f1 = pilha_vs_type_pop(piF);
   vs_type f2 = pilha_vs_type_pop(piF);
   if(f1==f2){
      pilha_vs_type_push(piT,f1);
   }
   else{
      fprintf(stderr, "Erro Semântico (%d,%d): Termo possui fatores de dois tipos diferentes.\n", nl, nc);
      exit(-1);
   }
   return;
}

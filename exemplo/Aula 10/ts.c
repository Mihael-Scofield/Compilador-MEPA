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

   if(rotulo!=NULL){
      strcpy(ts->pilha[ts->topo].rotulo, rotulo);
   }

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

void tabela_simbolos_remove_procedimentos_internos_do_nv_lex(tab_simbolos* ts, int nv_lex){
   for(int i=ts->topo; i>-1; i--){
      t_simbolo* simb = &ts->pilha[i];
      if (simb->categoria == proc_cs && simb->nv_lex >nv_lex){
         ts->topo--;
      }
      else{
         break;
      }
   }

   #ifdef DEBUG
      printf ("tabela_simbolos_remove_procedimentos_internos_do_nv_lex:.\n");
      print_tabela_simbolos(*ts);
   #endif
   return ;
}

int tabela_simbolos_remove_vs_ultimo_nv_lex(tab_simbolos* ts){
   int num_vars = 0;
   int nv_lex = ts->pilha[ts->topo].nv_lex;
   for(int i=ts->topo; i>-1; i--){
      t_simbolo* simb = &ts->pilha[i];
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
   for(int i=ts->topo; i>-1; i--){
      t_simbolo* simb = &ts->pilha[i];
      #ifdef DEBUG
         printf ("tabela_simbolos_busca_simbolo: Procurando Simbolo\n");
         printf ("tabela_simbolos_busca_simbolo:\n Comparando %s com %s .\n", simb->identificador, identificador);
      #endif
      if (strcmp(simb->identificador, identificador) == 0){
         #ifdef DEBUG
            printf ("tabela_simbolos_busca_simbolo: Simbolo identificado.\n");
            print_simbolo(*simb);
         #endif
         return i;
      }
   }
   fprintf(stderr, "Erro léxico (%d,%d):Simbolos/Variável \"%s\" não identificada no contexto.\n", nl, nc, identificador);
   exit(-1);
   return -1;
}

int ts_push_pi_cat_nvlex_tipo(tab_simbolos* ts, p_str* pi, cat_simb cat, int nv_lex, vs_type tipo){
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
      tabela_simbolos_push(ts, pi->pilha[i], cat, nv_lex, off_set, desc_type, NULL);
   }
   tabela_simbolos_atualiza_tipo_ultimas_vs(ts, tipo);
   pilha_string_reset(pi);
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
   
   switch (simb.categoria){
      case var_simples:
         printf("CAT [VS], nv_lex %d, deslocamento %d, ", simb.nv_lex, simb.off_set);
         break;
      case proc_cs:
         printf("CAT [PROC], nv_lex %d, rótulo %s ", simb.nv_lex, simb.rotulo);
         break;
      default:
         break;;
   }

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
void pilha_string_push(p_str* pi, char*  identi){
   pi->topo++;
   strncpy(pi->pilha[pi->topo], identi, TAM_TOKEN);
   #ifdef DEBUG
      printf ("pilha_string_push:.\n");
      print_pilha_string(pi);
   #endif
   return;
}

void pilha_string_pop_n(p_str* pi, int n){
   pi->topo = pi->topo - n;
   return;
}

void pilha_string_reset(p_str* pi){
   pi->topo =-1;
   return;
}

void print_pilha_string(p_str* pi){
   for (int i=0; i<pi->topo+1; i++){
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

void pilhas_vs_type_reset(pilha_vs_type* pi1, pilha_vs_type* pi2){
   pi1->topo =-1;
   pi2->topo =-1;
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
         printf("[ desconhecido ]");
         break;;
      }
   }
   printf("\n");
   return;
}

void resolveTipoTermoFatores(pilha_vs_type* piT, pilha_vs_type* piF){
   #ifdef DEBUG
      if (piT==piF){
         printf("MESMA Pilha \n");
      }
      printf("pilha 1 topo antes  %d\n Pilha1\n", piT->topo);
      print_pilha_vs_type(piT);
      printf("pilha 2 topo antes  %d\n Pilha2\n", piF->topo);
      print_pilha_vs_type(piF);
   #endif

   vs_type f1 = pilha_vs_type_pop(piF);

   #ifdef DEBUG
      if (piT==piF){
         printf("MESMA Pilha \n");
      }
      printf("pilha 1 topo antes  %d\n Pilha1\n", piT->topo);
      print_pilha_vs_type(piT);
      printf("pilha 2 topo antes  %d\n Pilha2\n", piF->topo);
      print_pilha_vs_type(piF);
   #endif

   vs_type f2 = pilha_vs_type_pop(piF);

   #ifdef DEBUG
      printf("f1 %d\n", f1);
      printf("f2 %d\n", f2);
   #endif

   if(f1==f2){
      pilha_vs_type_push(piT,f1);
   }
   else{
      fprintf(stderr, "Erro Semântico (%d,%d): Termo possui fatores de dois tipos diferentes.\n", nl, nc);
      exit(-1);
   }
   printf("%d topo depois\n", piT->topo);
   return;
}

void resolveTipoP1P2toP1(pilha_vs_type* pi1, pilha_vs_type* pi2){
   #ifdef DEBUG
      if (pi1==pi2){
         printf("resolveTipoP1P2toP1:MESMA Pilha \n");
      }
      else{
         printf("resolveTipoP1P2toP1:Pilhas Diferentes \n");
      }
      printf("pilha 1 topo antes  %d\n Pilha1\n", pi1->topo);
      print_pilha_vs_type(pi1);
      printf("pilha 2 topo antes  %d\n Pilha2\n", pi2->topo);
      print_pilha_vs_type(pi2);
   #endif

   vs_type f1 = pilha_vs_type_pop(pi1);

   #ifdef DEBUG
      printf("Depois pop f1\n");
      printf("pilha 1 topo antes  %d\n Pilha1\n", pi1->topo);
      print_pilha_vs_type(pi1);
      printf("pilha 2 topo antes  %d\n Pilha2\n", pi2->topo);
      print_pilha_vs_type(pi2);
   #endif

   vs_type f2 = pilha_vs_type_pop(pi2);

   #ifdef DEBUG
      printf("Depois pop f2\n");
      printf("pilha 1 topo antes  %d\n Pilha1\n", pi1->topo);
      print_pilha_vs_type(pi1);
      printf("pilha 2 topo antes  %d\n Pilha2\n", pi2->topo);
      print_pilha_vs_type(pi2);
      printf("f1 %d\n", f1);
      printf("f2 %d\n", f2);
   #endif

   if(f1==f2){
      pilha_vs_type_push(pi1,f1);
   }
   else{
      fprintf(stderr, "Erro Semântico (%d,%d): Termo possui fatores de dois tipos diferentes.\n", nl, nc);
      exit(-1);
   }
   printf("%d topo depois\n", pi1->topo);
   return;
}


void geraRotulo(p_str* p_rot, int* n_rotulos){
   int nw_topo;
   int n_rot = (* n_rotulos);
   p_rot->topo = p_rot->topo + 1;
   nw_topo = p_rot->topo;
   if(n_rot>9){
      sprintf(p_rot->pilha[nw_topo], "R%d", n_rot);
   }
   else{
      sprintf(p_rot->pilha[nw_topo], "R0%d", n_rot);
   }
   print_pilha_string(p_rot);
   (* n_rotulos) ++;
   return;
}

void gera2Rotulos(p_str* p_rot, int* n_rotulos){
   geraRotulo(p_rot, n_rotulos);
   geraRotulo(p_rot, n_rotulos);
   return;
}


void verifica_left_elem_categoria_vs(tab_simbolos* ts, int indx){
   t_simbolo* simb = &ts->pilha[indx];
   if (simb->categoria==proc_cs){
      fprintf(stderr, "Erro léxico (%d,%d): Procedimento \"%s\" não pode ser alvo de atribuição.\n", nl, nc, simb->identificador);
      exit(-1);
   }
   if (simb->categoria==param_formal){
      fprintf(stderr, "Erro léxico (%d,%d): Parametro Formal \"%s\" não pode ser alvo de atribuição.\n", nl, nc, simb->identificador);
      exit(-1);
   }
   return;
}
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "compilador.h"
#include "compilador.tab.h"
#include "ts.h"
#include "io.h"

#define DEBUG 1

void tabela_simbolos_init(tab_simbolos* ts){
   ts->topo=-1;
   #ifdef DEBUG
      printf("tabela_simbolos_init\n");
      print_tabela_simbolos(ts);
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


void tabela_simbolos_push(tab_simbolos* ts, char* ident_name,  cat_simb categoria,  int nv_lex, int off_set, vs_type tipo, char* rotulo, p_type passagem){
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
   ts->pilha[ts->topo].passagem= passagem;
   ts->pilha[ts->topo].n_params= DESCONHECIDO;

   if(rotulo!=NULL){
      strcpy(ts->pilha[ts->topo].rotulo, rotulo);
   }

   #ifdef DEBUG
      printf ("tabela_simbolos_push: token %s e %d addrs %p.\n", ident_name, ts->topo, &ts);
      print_tabela_simbolos(ts);
   #endif

   return;
}

void tabela_simbolos_atualiza_tipo_ultimas_vs_ou_pf(tab_simbolos* ts,  vs_type tipo){
   cat_simb cat; 
   cat = ts->pilha[ts->topo].categoria;
   if (cat!=var_simples && cat!=param_formal){
      fprintf(stderr, "Erro do Compilador (%d,%d):\n tabela_simbolos_atualiza_tipo_ultimas_vs_ou_pf: tentativa de atribuir tipos a algo diferente de vs ou pf.\n", nl, nc);
   }

   for(int i=ts->topo; i>-1; i--){
      t_simbolo* simb = &ts->pilha[i];
      if (simb->categoria == cat && simb->tipo == desc_type){
         simb->tipo= tipo;
      }
      else{
         break;
      }
   }

   #ifdef DEBUG
      printf ("tabela_simbolos_atualiza_tipo:.\n");
      print_tabela_simbolos(ts);
   #endif

   return;
}

int tabela_simbolos_atualiza_offset__ultimos_pfs(tab_simbolos* ts, int nv_lex){
   int num_pfs, off_set;
   num_pfs = 0;
   off_set = -4;
   for(int i=ts->topo; i>-1; i--){
      t_simbolo* simb = &ts->pilha[i];
      if (simb->categoria == param_formal && simb->nv_lex == nv_lex && simb->off_set == DESCONHECIDO){
         num_pfs++;
         simb->off_set= off_set;
         off_set--;
      }
      else{
         break;
      }
   }
   return num_pfs;
}


void tabela_simbolos_atualiza_passagem__ultimos_pfs(tab_simbolos* ts, int nv_lex, p_type pt){
   for(int i=ts->topo; i>-1; i--){
      t_simbolo* simb = &ts->pilha[i];
      if (simb->categoria == param_formal && simb->nv_lex == nv_lex && simb->passagem == desc_ptype){
         simb->passagem= pt;
      }
      else{
         break;
      }
   }
   return;
}

void tabela_simbolos_atualiza_procedimento(tab_simbolos*ts, int nv_lex, int num_param){
   if(ts->topo<num_param ){
      fprintf(stderr, "Erro do Compilador (%d,%d):\n tabela_simbolos_atualiza_procedimento: tabela de simbolos menor que parametros do procedimento.\n", nl, nc);
      exit(-1);
   }
   int indx = ts->topo -num_param;
   t_simbolo* simb_proc = &ts->pilha[ts->topo -num_param];
   if(simb_proc->categoria != proc_cs || simb_proc->nv_lex != nv_lex){
      fprintf(stderr, "Erro do Compilador (%d,%d):\n tabela_simbolos_atualiza_procedimento: procedimento ou parametros fora de ordem.\n", nl, nc);
      exit(-1);
   }
   if(simb_proc->n_params != DESCONHECIDO){
      fprintf(stderr, "Erro do Compilador (%d,%d):\n tabela_simbolos_atualiza_procedimento: procedimento com numero params já conhecido.\n", nl, nc);
      exit(-1);
   }
   simb_proc->n_params = num_param;
   indx++;
   for(int i=0; i<num_param; i++){
      t_simbolo* simb = &ts->pilha[indx+i];
      simb_proc->param_infs[i].tipo = simb->tipo;
      simb_proc->param_infs[i].passagem = simb->passagem;
   }

   return;
}

void tabela_simbolos_atualiza_funcao(tab_simbolos*ts, int nv_lex, int num_param, int simb){
   if(ts->topo<num_param ){
      fprintf(stderr, "Erro do Compilador (%d,%d):\n tabela_simbolos_atualiza_funcao: tabela de simbolos menor que parametros do procedimento.\n", nl, nc);
      exit(-1);
   }
   int indx = ts->topo -num_param;
   t_simbolo* simb_func = &ts->pilha[ts->topo -num_param];
   if(simb_func->categoria != funcao_cs || simb_func->nv_lex != nv_lex){
      fprintf(stderr, "Erro do Compilador (%d,%d):\n tabela_simbolos_atualiza_funcao: procedimento ou parametros fora de ordem.\n", nl, nc);
      exit(-1);
   }
   if(simb_func->n_params != DESCONHECIDO){
      fprintf(stderr, "Erro do Compilador (%d,%d):\n tabela_simbolos_atualiza_funcao: procedimento com numero params já conhecido.\n", nl, nc);
      exit(-1);
   }

   simb_func->tipo = map_simbolo_vs_type(simb);
   simb_func->n_params = num_param;
   simb_func->off_set = -4 -num_param;
   indx++;
   for(int i=0; i<num_param; i++){
      t_simbolo* simb = &ts->pilha[indx+i];
      simb_func->param_infs[i].tipo = simb->tipo;
      simb_func->param_infs[i].passagem = simb->passagem;
   }

   return;
}

int tabela_simbolos_remove_pfs_do_nv_lex(tab_simbolos* ts, int nv_lex){
   int n_pfs=0;
   for(int i=ts->topo; i>-1; i--){
      t_simbolo* simb = &ts->pilha[i];
      if (simb->categoria == param_formal && simb->nv_lex ==nv_lex){
         ts->topo--;
         n_pfs++;
      }
      else{
         break;
      }
   }

   #ifdef DEBUG
      printf ("tabela_simbolos_remove_pfs_do_nv_lex:.\n");
      print_tabela_simbolos(ts);
   #endif
   return n_pfs;
}

void tabela_simbolos_remove_sub_rotinas_internas_do_nv_lex(tab_simbolos* ts, int nv_lex){
   for(int i=ts->topo; i>-1; i--){
      t_simbolo* simb = &ts->pilha[i];
      if ((simb->categoria == proc_cs || simb->categoria == funcao_cs) && simb->nv_lex >nv_lex){
         ts->topo--;
      }
      else{
         break;
      }
   }

   #ifdef DEBUG
      printf ("tabela_simbolos_remove_sub_rotinas_internas_do_nv_lex:.\n");
      print_tabela_simbolos(ts);
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
      print_tabela_simbolos(ts);
   #endif

   return num_vars;
}

int tabela_simbolos_busca_simbolo(tab_simbolos* ts, char* identificador){
   int nv_lex = ts->pilha[ts->topo].nv_lex;
   #ifdef DEBUG
      printf ("tabela_simbolos_busca_simbolo:\n    Procurando Simbolo ...\n");
   #endif
   for(int i=ts->topo; i>-1; i--){
      t_simbolo* simb = &ts->pilha[i];
      #ifdef DEBUG
         printf ("      Comparando %s com %s .\n", simb->identificador, identificador);
      #endif
      if (strcmp(simb->identificador, identificador) == 0){
         #ifdef DEBUG
            printf ("      Simbolo identificado. \"%s\"\n",simb->identificador);
            print_simbolo(simb);
         #endif
         return i;
      }
   }
   fprintf(stderr, "Erro Semântico (%d,%d):Simbolos/Variável \"%s\" não identificada no contexto.\n", nl, nc, identificador);
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
      tabela_simbolos_push(ts, pi->pilha[i], cat, nv_lex, off_set, desc_type, NULL, desc_ptype);
   }
   tabela_simbolos_atualiza_tipo_ultimas_vs_ou_pf(ts, tipo);
   pilha_string_reset(pi);
   #ifdef DEBUG
      printf ("ts_push_pi_cat_nvlex_tipo:.");
      print_tabela_simbolos(ts);
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

void chamada_de_procedimento(tab_simbolos* ts, int proc_indx, int num_vars, int nv_lex, pilha_vs_type* expType){
   t_simbolo* simb = &ts->pilha[proc_indx];
   if(simb->categoria != proc_cs ){
      fprintf(stderr, "Erro do Compilador (%d,%d):\n  chamada_de_procedimento: %s não é procedimento.\n", nl, nc, simb->identificador );
      exit(-1);
   }
   if(simb->n_params != num_vars ){
      fprintf(stderr, "Erro Semântico (%d,%d):\n   Na chamada do Procedimento %s.\n", nl, nc, simb->identificador );
      if(simb->n_params > num_vars){
         fprintf(stderr, "   Poucos argumentos apresentados. [%d]\n", simb->n_params-num_vars);
         exit(-1);
      }
      if(simb->n_params < num_vars){
         fprintf(stderr, "   Muitos argumentos apresentados. [%d]\n", num_vars-simb->n_params);
         exit(-1);
      }
   }
   verificaParametrosTipo(simb, expType);
   geraCodigo2ParamsCharNum(NULL, "CHPR ", simb->rotulo, nv_lex);
   return;
}

void chamada_desvio_funcao(tab_simbolos*  ts, pilha_inf_f* p_Funcoes, int num_vars, int nv_lex, pilha_vs_type* pilha_F, pilha_vs_type* pilha_T){
   if(p_Funcoes->topo<0){
      fprintf(stderr, "Erro do Compilador (%d,%d):\n  chamada_desvio_funcao:\n      Não tem função para chamada de desvio.\n", nl, nc);
      exit(-1);
   }

   t_simbolo* simb = &ts->pilha[p_Funcoes->pilha[p_Funcoes->topo].indx_fun];
   if(simb->categoria != funcao_cs ){
      fprintf(stderr, "Erro do Compilador (%d,%d):\n  chamada_de_procedimento: %s não é procedimento.\n", nl, nc, simb->identificador );
      exit(-1);
   }

   printf("chamada_desvio_funcao\n    simb:\n");
   print_simbolo(simb);

   if(simb->n_params != num_vars ){
      fprintf(stderr, "Erro Semântico (%d,%d):\n   Na chamada da Função %s.\n", nl, nc, simb->identificador );
      if(simb->n_params > num_vars){
         fprintf(stderr, "   Poucos argumentos apresentados. [%d]\n", simb->n_params-num_vars);
         exit(-1);
      }
      if(simb->n_params < num_vars){
         fprintf(stderr, "   Muitos argumentos apresentados. [%d]\n", num_vars-simb->n_params);
         exit(-1);
      }
   }
   verificaParametrosTipo(simb, pilha_T);
   geraCodigo2ParamsCharNum(NULL, "CHPR ", simb->rotulo, nv_lex);
   return;
}

void verificaParametrosTipo(t_simbolo* simb, pilha_vs_type* expType){
   if(simb->categoria!=funcao_cs && simb->categoria!=proc_cs){
      fprintf(stderr, "Erro do Compilador (%d,%d):\n  verificaParametrosTipo: %s não é sub-rotina.\n", nl, nc, simb->identificador);
      exit(-1);
   }
   int aux_indx = (expType->topo)-(simb->n_params)+1;
   for(int i=0; i<simb->n_params; i++){
      printf("i=%d; i+offset:= %d\n", i ,aux_indx+i );
      if(expType->pilha[aux_indx+i] != addrs_type){
         if(expType->pilha[i] != simb->param_infs[i].tipo){
            fprintf(stderr, "Erro Semântico (%d,%d):\nverificaParametrosTipo\n   Na chamada de Sub Rotina %s.\n", nl, nc, simb->identificador );
            fprintf(stderr, "   Argumento %d deveria ser de outro tipo. \n", i+1);
            exit(-1);
         }
      }
      if(expType->pilha[aux_indx+i] == addrs_type){
         if(simb->param_infs[i].passagem != ref_ptype){
            fprintf(stderr, "Erro Compilador (%d,%d):\nverificaParametrosTipo\n   Na chamada de Sub Rotina %s.\n", nl, nc, simb->identificador );
            fprintf(stderr, "   Argumento %d não deveria ser um endereço. \n", i+1);
            exit(-1);
         }
      }
   }
   pilha_vs_type_n_pop(expType, simb->n_params);
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

void pilha_int_push(pilha_int* pi, int  n){
   pi->topo++;
   pi->pilha[pi->topo] = n;
   // #ifdef DEBUG
   //    printf ("pilha_int_push:.\n");
   //    print_pilha_string(pi);
   // #endif
   return;
}

void pilha_inf_fun_push(pilha_inf_f* pi, int  n){
   pi->topo++;
   pi->pilha[pi->topo].indx_fun = n;
   pi->pilha[pi->topo].num_p = 0;
   return;
}

void pilha_string_pop_n(p_str* pi, int n){
   pi->topo = pi->topo - n;
   return;
}

void pilha_int_pop(pilha_int* pi){
   pi->topo--;
   return;
}

void pilha_inf_fun_pop(pilha_inf_f* pi){
   pi->topo--;
   return;
}

void pilha_string_reset(p_str* pi){
   pi->topo =-1;
   return;
}

void pilha_inteiros_reset(pilha_int* pi){
   pi->topo =-1;
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

void pilha_vs_type_n_pop(pilha_vs_type* pi, int n){
   pi->topo = pi->topo - n;
   return;
}

void pilha_vs_type_reset(pilha_vs_type* pi){
   pi->topo =-1;
   return;
}

void pilha_inf_fun_reset(pilha_inf_f* pi){
   pi->topo =-1;
   return;
}

void pilhas_vs_type_reset(pilha_vs_type* pi1, pilha_vs_type* pi2){
   pi1->topo =-1;
   pi2->topo =-1;
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

   if(f1==addrs_type || f2==addrs_type ){
      fprintf(stderr, "Erro Semântico (%d,%d): Valores passados por referência não podem receber expressões.\n", nl, nc);
      exit(-1);
   }

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

   if(f1==addrs_type || f2==addrs_type ){
      fprintf(stderr, "Erro Semântico (%d,%d): Valores passados por referência não podem receber expressões.\n", nl, nc);
      exit(-1);
   }

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
      fprintf(stderr, "Erro Semântico (%d,%d): Procedimento \"%s\" não pode ser alvo de atribuição.\n", nl, nc, simb->identificador);
      exit(-1);
   }
   return;
}

void carrega_identidade_ou_aloca_mem_para_funcao(tab_simbolos* ts, char* token, int  l_elem, int indx_pmf, pilha_vs_type* p_fator, pilha_inf_f* p_funcoes){

   int indx_pmr = tabela_simbolos_busca_simbolo(ts, token);
   if(p_funcoes->topo!=-1){
      carrega_identidade_em_funcao(ts, indx_pmr, l_elem, p_fator, p_funcoes);
      return;
   }

   
   // Se l_elem==DESCONHECIDO ou exprecoes como while, write, read e if.
   // if(l_elem==L_READ || l_elem==L_WRITE || l_elem==DESCONHECIDO){
   if(l_elem<0 ){
      t_simbolo* param_real = &ts->pilha[indx_pmr];
      carrega_identidade_em_atribuicao(param_real, p_fator, l_elem, p_funcoes, indx_pmr);
      return;
   }
   
   
   t_simbolo* simb_l_elem = &ts->pilha[l_elem];
   #ifdef DEBUG
      printf("carrega_identidade_valor_endereco_vi:\n");
      printf("    O elemento da esquerda é:\n    ");
      print_simbolo(simb_l_elem);
   #endif

   
   // Quando elemento da esquerda ser varivel simples ou parametro formal, ou variavel funcao.
   // Ou seja, quando for atribuicao.
   if(simb_l_elem->categoria==var_simples || simb_l_elem->categoria==param_formal || simb_l_elem->categoria==funcao_cs){
      t_simbolo* param_real = &ts->pilha[indx_pmr];
      carrega_identidade_em_atribuicao(param_real, p_fator, l_elem, p_funcoes, indx_pmr);
   }

   if(simb_l_elem->categoria==proc_cs){
      // (ts, indx_var, l_elem, indx_param, p_fator, p_funcoes)
      carrega_identidade_em_procedimento(ts, simb_l_elem, indx_pmr, indx_pmf,  p_fator, p_funcoes);
   }
   return;
}

void carrega_identidade_em_procedimento(tab_simbolos* ts, t_simbolo* simb_proc,  int indx_pmr, int indx_pmf, pilha_vs_type* p_fator, pilha_inf_f* p_funcoes){
   // Quando For procedimento
   if(indx_pmf>(simb_proc->n_params-1)){
      fprintf(stderr, "Erro do Compilador (%d,%d):\n carrega_identidade_valor_endereco_vi: procedimento \"%s\" não tem %d parametros.\n", nl, nc, simb_proc->identificador, indx_pmf+1);
      exit(-1);
   }
   t_simbolo* param_real = &ts->pilha[indx_pmr];
   t_pinf* param_formal = &simb_proc->param_infs[indx_pmf];
   carrega_identidade_em_sub_rotina(simb_proc, param_real, param_formal, p_fator, indx_pmr, indx_pmf, p_funcoes);
   return;
}

void carrega_identidade_em_funcao(tab_simbolos* ts, int indx_pmr, int  l_elem, pilha_vs_type* p_fator, pilha_inf_f* p_funcoes){
   printf("carrega_identidade_em_funcao:\n");
   t_simbolo* simb_func = &ts->pilha[p_funcoes->pilha[p_funcoes->topo].indx_fun];
   printf(" Pilha de Funcões:\n");
   print_pilha_inf_func(p_funcoes);
   if(simb_func->categoria!=funcao_cs){
      fprintf(stderr, "Erro do Compilador (%d,%d):\n carrega_identidade_em_funcao: Indx na pilha de funcoes corresponde a \"%s\" que não é função.\n", nl, nc, simb_func->identificador);
      exit(-1);
   }
   int indx_pmf = p_funcoes->pilha[p_funcoes->topo].num_p;
   t_simbolo* param_real = &ts->pilha[indx_pmr];
   t_pinf* param_formal = &simb_func->param_infs[indx_pmf];
   carrega_identidade_em_sub_rotina(simb_func, param_real, param_formal, p_fator, indx_pmr, indx_pmf, p_funcoes);
   return;
}

void carrega_identidade_em_sub_rotina(t_simbolo* simb_subrotina, t_simbolo* p_real, t_pinf* p_formal, pilha_vs_type* pilha_fator, int indx_pmr, int indx_pmf, pilha_inf_f* p_funcoes){

   #ifdef DEBUG
      printf("carrega_identidade_em_sub_rotina:\n");
      printf("      Sub rotinta:");
      print_simbolo(simb_subrotina);
      printf("      Preal:");
      print_simbolo(p_real);
      printf("      Pformal:");
      print_param_inf(p_formal);
      printf("\ncarrega_identidade_em_funcao:END\n");
   #endif

   // Se funcao gera AMEM
   if(p_real->categoria==funcao_cs){
      if(p_real->tipo!=p_formal->tipo){
         fprintf(stderr, "Erro do Semântico (%d,%d):\n      carrega_identidade_sub_rotina: parametro %d da sub-rotina \"%s\" é diferente do tipo da função %s.\n", nl, nc, indx_pmf+1, simb_subrotina->identificador, p_real->identificador);
         exit(-1);
      }
      if(p_formal->passagem==ref_ptype){
         fprintf(stderr, "Erro do Semântico (%d,%d):\n      carrega_identidade_sub_rotina: parametro %d da sub-rotina \"%s\" é por referencia e não aceita funções.\n", nl, nc, indx_pmf+1, simb_subrotina->identificador);
         exit(-1);
      }
      geraCodigo1ParamNum(NULL, "AMEM ", 1);
      pilha_inf_fun_push(p_funcoes ,indx_pmr);
      print_pilha_inf_func(p_funcoes);
      // Em atribuicao o tipo é visto depois de calcular a função
      // pilha_vs_type_push(pilha_fator, p_real->tipo);
      return;
   }

   // (VS ou PF vlr) *
   if(
      p_real->categoria==var_simples || 
      (p_real->categoria==param_formal &&  p_real->passagem==valor_ptype) 
   ){
      // (VS ou PF vlr) com PF vlr
      if(p_formal->passagem==valor_ptype){
         geraCodigo2ParamsNum(NULL, "CRVL ", p_real->nv_lex, p_real->off_set);
         pilha_vs_type_push(pilha_fator, p_real->tipo);
         return;
      }

      // (VS ou PF vlr) com PF ref
      if(p_formal->passagem==ref_ptype){
         geraCodigo2ParamsNum(NULL, "CREN ", p_real->nv_lex, p_real->off_set);
         verifica_tipo_do_tipo_referencia(p_real, p_formal);
         pilha_vs_type_push(pilha_fator, addrs_type);
         return;
      }
   }

   // (PF ref) *
   if(p_real->categoria==param_formal &&  p_real->passagem==ref_ptype){
      // (VS ou PF vlr) com PF vlr
      if(p_formal->passagem==valor_ptype){
         geraCodigo2ParamsNum(NULL, "CRVI ", p_real->nv_lex, p_real->off_set);
         pilha_vs_type_push(pilha_fator, p_real->tipo);
         return;
      }

      // (VS ou PF vlr) com PF ref
      if(p_formal->passagem==ref_ptype){
         geraCodigo2ParamsNum(NULL, "CRVL ", p_real->nv_lex, p_real->off_set);
         verifica_tipo_do_tipo_referencia(p_real, p_formal);
         pilha_vs_type_push(pilha_fator, addrs_type);
         return;
      }
   }

   //Nao eh para chegar aqui
   fprintf(stderr, "Erro do Compilador (%d,%d):\n carrega_identidade_em_sub_rotina: Caso não esperado.\n", nl, nc);
   exit(-1);
   return;
}

void carrega_identidade_em_atribuicao(t_simbolo* p_real, pilha_vs_type* p_fator, int l_elem, pilha_inf_f* p_funcoes, int indx_param){
   printf("\n\n\ncarrega_identidade_em_atribuicao:\n");
   printf("    P_Real\n  ");
   print_simbolo(p_real);
   printf("    indx_var %d\n", indx_param);
   // Se for funcao e não for o elemento da esquerda gera AMEM e puxa tipo
   if(p_real->categoria==funcao_cs && l_elem!=DESCONHECIDO){
      geraCodigo1ParamNum(NULL, "AMEM ", 1);
      pilha_inf_fun_push(p_funcoes ,indx_param);
      print_pilha_inf_func(p_funcoes);
      return;
   }

   if(p_real->categoria ==param_formal){
      if(p_real->passagem == ref_ptype){
         geraCodigo2ParamsNum(NULL, "CRVI ", p_real->nv_lex, p_real->off_set);
         pilha_vs_type_push(p_fator, p_real->tipo);
         return;
      }
      if(p_real->passagem == valor_ptype){
         geraCodigo2ParamsNum(NULL, "CRVL ", p_real->nv_lex, p_real->off_set);
         pilha_vs_type_push(p_fator, p_real->tipo);
         return;
      }
   }
   if(p_real->categoria ==var_simples){
      geraCodigo2ParamsNum(NULL, "CRVL ", p_real->nv_lex, p_real->off_set);
      pilha_vs_type_push(p_fator, p_real->tipo);
      return;
   }
   
   if(p_real->categoria ==proc_cs){
      fprintf(stderr, "Erro do Semântico (%d,%d):\n carrega_identidade_atribuicao_ou_aloca_mem_para_funcao:\n", nl, nc);
      fprintf(stderr, "  \"%s\" é um procedimento e não retorna valores para atribuição ou como parametro.\n",p_real->identificador );
      exit(-1);
   }
   
   //Nao eh para chegar aqui
   fprintf(stderr, "Erro do Compilador (%d,%d):\n carrega_identidade_atribuicao_ou_aloca_mem_para_funcao: Caso não esperado.\n", nl, nc);
   exit(-1);
   return;
}

void armazena_identidade_vlr_vlrInd(tab_simbolos* ts, int  l_elem, pilha_vs_type* p_fator, pilha_vs_type* p_termo){
   t_simbolo* simb_l_elem = &ts->pilha[l_elem];
   #ifdef DEBUG
      printf("carrega_identidade_valor_endereco_vi:\n");
      printf("    O elemento da esquerda é:\n    ");
      print_simbolo(simb_l_elem);
   #endif

   pilha_vs_type_push(p_termo, ts->pilha[l_elem].tipo);
   resolveTipoTermoFatores(p_termo, p_termo);
   pilhas_vs_type_reset(p_fator, p_termo);

   
   if(simb_l_elem->categoria==proc_cs){
      fprintf(stderr, "Erro do Compilador (%d,%d):\n armazena_identidade_vlr_vlrInd: procedimento \"%s\" não deveria receber atribuição.\n", nl, nc, simb_l_elem->identificador);
      exit(-1);
   }

   if(simb_l_elem->categoria==param_formal){
      switch (simb_l_elem->passagem){
         case ref_ptype:
            geraCodigo2ParamsNum(NULL, "ARMI ", simb_l_elem->nv_lex, simb_l_elem->off_set);
            return;
         case valor_ptype:
            geraCodigo2ParamsNum(NULL, "ARMI ", simb_l_elem->nv_lex, simb_l_elem->off_set);
            return;
         //desc_ptype
         default:
            fprintf(stderr, "Erro do Compilador (%d,%d):\n armazena_identidade_vlr_vlrInd: parametro formal \"%s\" não deveria possuir tipo de passagem.\n", nl, nc, simb_l_elem->identificador);
            exit(-1);
      }
   }

   // Categoria Variavel Simples
   geraCodigo2ParamsNum(NULL, "ARMZ ", simb_l_elem->nv_lex, simb_l_elem->off_set);
   return;

}


void verifica_tipo_do_tipo_referencia(t_simbolo* p_real, t_pinf* p_form){
   if(p_real->tipo!=p_form->tipo){
      fprintf(stderr, "Erro Semântico (%d,%d):\n   Na chamada do Procedimento.\n", nl, nc);
      fprintf(stderr, "   Argumento %s deveria ser de outro tipo. \n", p_real->identificador);
      exit(-1);
   }
   return;
}


void verifica_ultimo_termo_booleano(pilha_vs_type* pi){
   if(pi->pilha[pi->topo]!=bool_type){
      fprintf(stderr, "Erro Semântico (%d,%d):\n   Em expressão condicional.\n", nl, nc);
      fprintf(stderr, "   Expressão deveria \"retornar\" um booleano. \n");
      exit(-1);
   }
   return;
}

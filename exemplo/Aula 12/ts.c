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

void tabela_simbolos_remove_pfs_do_nv_lex(tab_simbolos* ts, int nv_lex){
   for(int i=ts->topo; i>-1; i--){
      t_simbolo* simb = &ts->pilha[i];
      if (simb->categoria == param_formal && simb->nv_lex ==nv_lex){
         ts->topo--;
      }
      else{
         break;
      }
   }

   #ifdef DEBUG
      printf ("tabela_simbolos_remove_pfs_do_nv_lex:.\n");
      print_tabela_simbolos(ts);
   #endif
   return ;
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
   for(int i=ts->topo; i>-1; i--){
      t_simbolo* simb = &ts->pilha[i];
      #ifdef DEBUG
         printf ("tabela_simbolos_busca_simbolo: Procurando Simbolo\n");
         printf ("tabela_simbolos_busca_simbolo:\n Comparando %s com %s .\n", simb->identificador, identificador);
      #endif
      if (strcmp(simb->identificador, identificador) == 0){
         #ifdef DEBUG
            printf ("tabela_simbolos_busca_simbolo: Simbolo identificado.\n");
            print_simbolo(simb);
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
   geraCodigo2ParamsCharNum(NULL, "CHPR ", ts->pilha[proc_indx].rotulo, nv_lex);
   return;
}

void verificaParametrosTipo(t_simbolo* simb, pilha_vs_type* expType){
   for(int i=expType->topo; i>-1; i--){
      if(expType->pilha[i] != addrs_type){
         if(expType->pilha[i] != simb->param_infs[i].tipo){
            fprintf(stderr, "Erro Semântico (%d,%d):\n   Na chamada do Procedimento %s.\n", nl, nc, simb->identificador );
            fprintf(stderr, "   Argumento %d deveria ser de outro tipo. \n", i+1);
            exit(-1);
         }
      }
      if(expType->pilha[i] == addrs_type){
         if(simb->param_infs[i].passagem != ref_ptype){
            fprintf(stderr, "Erro Compilador (%d,%d):\n   Na chamada do Procedimento %s.\n", nl, nc, simb->identificador );
            fprintf(stderr, "   Argumento %d não deveria ser um endereço. \n", i+1);
            exit(-1);
         }
      }
   }
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
      fprintf(stderr, "Erro léxico (%d,%d): Procedimento \"%s\" não pode ser alvo de atribuição.\n", nl, nc, simb->identificador);
      exit(-1);
   }
   return;
}

void carrega_identidade_valor_endereco_vi(tab_simbolos* ts, char* token, int  l_elem, int indx_param, pilha_vs_type* p_fator){
   int indx_var = tabela_simbolos_busca_simbolo(ts, token);
   // Se l_elem==DESCONHECIDO exprecoes de while, write, read e if.
   t_simbolo* param_real = &ts->pilha[indx_var];
   if(l_elem==DESCONHECIDO){
      carrega_identidade_atribuicao(param_real, p_fator);
      return;
   }
   
   t_simbolo* simb_l_elem = &ts->pilha[l_elem];
   // Quando elemento da esquerda ser varivel simples ou parametro formal.
   // Ou seja, quando for atribuicao.
   if(simb_l_elem->categoria==var_simples || simb_l_elem->categoria==param_formal){
      carrega_identidade_atribuicao(param_real, p_fator);
   }

   if(simb_l_elem->categoria==proc_cs){
      // Quando For procedimento
      if(indx_param>(simb_l_elem->n_params-1)){
         fprintf(stderr, "Erro do Compilador (%d,%d):\n carrega_identidade_valor_endereco_vi: procedimento \"%s\" não tem %d parmetros.\n", nl, nc, simb_l_elem->identificador, indx_param+1);
         exit(-1);
      }
      t_pinf* param_formal = &simb_l_elem->param_infs[indx_param];
      carrega_identidade_procedimento(param_real, param_formal, p_fator);
   }
   return;
}

void carrega_identidade_procedimento(t_simbolo* p_real, t_pinf* p_form, pilha_vs_type* p_fator){

   // (VS ou PF vlr) *
   if(
      p_real->categoria==var_simples || 
      (p_real->categoria==param_formal &&  p_real->passagem==valor_ptype) 
   ){
      // (VS ou PF vlr) com PF vlr
      if(p_form->passagem==valor_ptype){
         geraCodigo2ParamsNum(NULL, "CRVL ", p_real->nv_lex, p_real->off_set);
         pilha_vs_type_push(p_fator, p_real->tipo);
         return;
      }

      // (VS ou PF vlr) com PF ref
      if(p_form->passagem==ref_ptype){
         geraCodigo2ParamsNum(NULL, "CREN ", p_real->nv_lex, p_real->off_set);
         verifica_tipo_do_tipo_referencia(p_real, p_form);
         pilha_vs_type_push(p_fator, addrs_type);
         return;
      }
   }

   // (PF ref) *
   if(p_real->categoria==param_formal &&  p_real->passagem==ref_ptype){
      // (VS ou PF vlr) com PF vlr
      if(p_form->passagem==valor_ptype){
         geraCodigo2ParamsNum(NULL, "CRVI ", p_real->nv_lex, p_real->off_set);
         pilha_vs_type_push(p_fator, p_real->tipo);
         return;
      }

      // (VS ou PF vlr) com PF ref
      if(p_form->passagem==ref_ptype){
         geraCodigo2ParamsNum(NULL, "CRVL ", p_real->nv_lex, p_real->off_set);
         verifica_tipo_do_tipo_referencia(p_real, p_form);
         pilha_vs_type_push(p_fator, addrs_type);
         return;
      }
   }

   //Nao eh para chegar aqui
   fprintf(stderr, "Erro do Compilador (%d,%d):\n carrega_identidade_procedimento: Caso não esperado.\n", nl, nc);
   exit(-1);
   return;
}


void carrega_identidade_atribuicao(t_simbolo* p_real, pilha_vs_type* p_fator){
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
      fprintf(stderr, "Erro do Léxico (%d,%d):\n carrega_identidade_atribuicao:\n", nl, nc);
      fprintf(stderr, "  \"%s\" é um procedimento e não retorna valores para atribuição ou como parametro.\n",p_real->identificador );
      exit(-1);
   }
   
   //Nao eh para chegar aqui
   fprintf(stderr, "Erro do Compilador (%d,%d):\n carrega_identidade_atribuicao: Caso não esperado.\n", nl, nc);
   exit(-1);
   return;
}

void armazena_identidade_vlr_vlrInd(tab_simbolos* ts, int  l_elem, pilha_vs_type* p_fator, pilha_vs_type* p_termo){
   pilha_vs_type_push(p_termo, ts->pilha[l_elem].tipo);
   resolveTipoTermoFatores(p_termo, p_termo);
   pilhas_vs_type_reset(p_fator, p_termo);

   t_simbolo* simb_l_elem = &ts->pilha[l_elem];
   if(simb_l_elem->categoria==proc_cs){
      fprintf(stderr, "Erro do Compilador (%d,%d):\n armazena_identidade_vlr_vlrInd: procedimento \"%s\" não deveria receber atribuição.\n", nl, nc, simb_l_elem->identificador);
      exit(-1);
   }

   if(simb_l_elem->categoria==param_formal){
      switch (simb_l_elem->passagem){
         case ref_ptype:
            geraCodigo2ParamsNum(NULL, "ARMI ", ts->pilha[l_elem].nv_lex, ts->pilha[l_elem].off_set);
            return;
         case valor_ptype:
            geraCodigo2ParamsNum(NULL, "ARMI ", ts->pilha[l_elem].nv_lex, ts->pilha[l_elem].off_set);
            return;
         //desc_ptype
         default:
            fprintf(stderr, "Erro do Compilador (%d,%d):\n armazena_identidade_vlr_vlrInd: parametro formal \"%s\" não deveria possuir tipo de passagem.\n", nl, nc, simb_l_elem->identificador);
            exit(-1);
      }
   }

   // Categoria Variavel Simples
   geraCodigo2ParamsNum(NULL, "ARMZ ", ts->pilha[l_elem].nv_lex, ts->pilha[l_elem].off_set);
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
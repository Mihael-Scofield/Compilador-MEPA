#ifndef __TABELA_DE_SIMBOLS_H__
#define __TABELA_DE_SIMBOLS_H__

#include "compilador.h"

#define TAM_TS 100
#define TAM_IDENT 20

typedef enum categoria_simbolos {
  var_simples, param_formal, proc_cs
} cat_simb;

typedef enum variavel_simples_type {
  desc_type, integer_type //desc - desconhecido
} vs_type;                //simb_enum_type

// Estrutura que define Simbolo
typedef struct t_simbolo
{
  char identificador[TAM_IDENT];
  cat_simb categoria;
  int nv_lex;
  int off_set; //deslocamenteo
  vs_type tipo;
  // passagem // TODO para parametro formal
  // rotulo   // Todo para procedimento
} t_simbolo;

// Estrutura que define a Tabela de Simbolos (TS)
typedef struct tabela_simbolos
{
  int topo;
  t_simbolo pilha[TAM_TS];
} tab_simbolos;

// Estrutura Pilha de Identificadores. Empilha identificadores. 
typedef struct pilha_de_identificadores
{
  int topo;
  char pilha[TAM_IDENT][TAM_IDENT];
} pilha_ident;


void tabela_simbolos_init(tab_simbolos* ts);

/*!
  \brief Apeenda Simbolo na Tabela de Simbolos
  
  \param nv_lex nivel lexico
  \param ident_name o nome do simpolo, aka token, adicionado.

*/
void tabela_simbolos_push(tab_simbolos* ts, char* ident_name,  cat_simb categoria,  int nv_lex, int off_set, vs_type tipo);

void tabela_simbolos_atualiza_tipo_ultimas_vs(tab_simbolos* ts, vs_type tipo);

int tabela_simbolos_remove_vs_ultimo_nv_lex(tab_simbolos* ts);

int tabela_simbolos_busca_simbolo(tab_simbolos* ts, char* identificador);

int ts_push_pi_cat_nvlex_tipo(tab_simbolos* ts, pilha_ident* pi, cat_simb cat, int nv_lex, vs_type tipo);

vs_type map_simbolo_vs_type(int simb);


/*!
  \brief Print pilha da tabela de simbolos
  
  \param ts tabela de simbolo.
*/
void print_tabela_simbolos(tab_simbolos ts);

void print_simbolo(t_simbolo simb);


void pilha_identificador_push(pilha_ident* pi, char*  identi);
void pilha_identificador_pop_n(pilha_ident* pi, int n);
void pilha_identificador_reset(pilha_ident* pi);
void print_pilha_identificador(pilha_ident* pi);


#endif
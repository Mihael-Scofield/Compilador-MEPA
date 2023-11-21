#ifndef __TABELA_DE_SIMBOLS_H__
#define __TABELA_DE_SIMBOLS_H__

#include "compilador.h"

#define TAM_TS 100
#define TAM_IDENT 20

typedef enum categoria_simbolos {
  var_simples, param_formal, proc_cs
} cat_simb;

typedef enum variavel_simples_type {
  desc_type,    //desc - desconhecido
  integer_type, bool_type 
} vs_type;      //simb_enum_type

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
typedef struct pilha_de_strings
{
  int topo;
  char pilha[TAM_IDENT][TAM_IDENT];
} p_str;

// Estrutura Pilha de Identificadores. Empilha identificadores. 
typedef struct pilha_de_variavel_simples_tipo
{
  int topo;
  vs_type pilha[TAM_IDENT];
} pilha_vs_type;


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

int ts_push_pi_cat_nvlex_tipo(tab_simbolos* ts, p_str* pi, cat_simb cat, int nv_lex, vs_type tipo);

vs_type map_simbolo_vs_type(int simb);

// void map_simbolos_comando_relacao(simbolos simb);
void map_simbolos_comando_relacao(int simb);

/*!
  \brief Print pilha da tabela de simbolos
  
  \param ts tabela de simbolo.
*/
void print_tabela_simbolos(tab_simbolos ts);

void print_simbolo(t_simbolo simb);


void pilha_string_push(p_str* pi, char*  identi);
void pilha_string_pop_n(p_str* pi, int n);
void pilha_string_reset(p_str* pi);
void print_pilha_string(p_str* pi);


void pilha_vs_type_push(pilha_vs_type* pi, vs_type tipo);
vs_type pilha_vs_type_pop(pilha_vs_type* pi);
void pilha_vs_type_reset(pilha_vs_type* pi);
void pilhas_vs_type_reset(pilha_vs_type* pi1, pilha_vs_type* pi2);
void print_pilha_vs_type(pilha_vs_type* pi);

void resolveTipoTermoFatores(pilha_vs_type* piT, pilha_vs_type* piF);
void resolveTipoP1P2toP1(pilha_vs_type* pi1, pilha_vs_type* pi2);
void gera2Rotulos(p_str* p_rot);


#endif
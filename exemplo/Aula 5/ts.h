#ifndef __TABELA_DE_SIMBOLS_H__
#define __TABELA_DE_SIMBOLS_H__

#define TAM_TS 100
#define TAM_IDENT 20

typedef enum categoria_simbolos {
  var_simples, param_formal, proc_cs
} cat_simb;

typedef enum simbolo_type {
  desc_type, integer_type //desc - desconhecido
} simb_en_type; //simb_enum_type

// Estrutura que define Simbolo
typedef struct t_simbolo
{
  char identificador[TAM_IDENT];
  cat_simb categoria;
  int nv_lex;
  int off_set; //deslocamenteo
  simb_en_type tipo;
  // passagem // TODO para parametro formal
  // rotulo   // Todo para procedimento
} t_simbolo;

// Estrutura que define a Tabela de Simbolos (TS)
typedef struct tabela_simbolos
{
  int topo;
  t_simbolo pilha[TAM_TS];
} tab_simbolos;


void tabela_simbolos_init(tab_simbolos* ts);

/*!
  \brief Apeenda Simbolo na Tabela de Simbolos
  
  \param nv_lex nivel lexico
  \param ident_name o nome do simpolo, aka token, adicionado.

*/
void tabela_simbolos_push(tab_simbolos* ts, char* ident_name,  cat_simb categoria,  int nv_lex, int off_set);

void tabela_simbolos_atualiza_tipo_ultimas_vs(tab_simbolos* ts,  simb_en_type tipo);

int tabela_simbolos_remove_vs_ultimo_nv_lex(tab_simbolos* ts);

int tabela_simbolos_busca_simbolo(tab_simbolos* ts, char* identificador);

/*!
  \brief Print pilha da tabela de simbolos
  
  \param ts tabela de simbolo.
*/
void print_tabela_simbolos(tab_simbolos ts);

void print_simbolo(t_simbolo simb);
#endif
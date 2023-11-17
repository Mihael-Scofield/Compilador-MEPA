#ifndef __TABELA_DE_SIMBOLS_H__
#define __TABELA_DE_SIMBOLS_H__

#define TAM_TS 100
#define TAM_IDENT 20
#define NUM_PARAM_MAX 20
#define DESCONHECIDO -1000
#define L_READ -999
#define L_WRITE -998

typedef enum categoria_simbolos {
  var_simples, param_formal, proc_cs, funcao_cs
} cat_simb;

typedef enum variavel_simples_type {
  desc_type,    //desc - desconhecido
  integer_type, bool_type,
  addrs_type    // se carregar como endereço não pode fazer operação
} vs_type;      //simb_enum_type

typedef enum passagem_type {
  desc_ptype, valor_ptype, ref_ptype
} p_type;

// Estrutura que define Simbolo
typedef struct t_simbolo
{
  char identificador[TAM_IDENT];
  cat_simb categoria;
  int nv_lex;
  int off_set; //deslocamenteo
  vs_type tipo;
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

void tabela_simbolos_push(
  tab_simbolos* ts,
  char* ident_name,
  cat_simb categoria,
  int nv_lex,
  int off_set,
  vs_type tipo,
  char* rotulo;
);

//----------------Funções de Tabela de Simbolos----------------------//
void tabela_simbolos_atualiza_tipo_ultimas_vs_ou_pf(tab_simbolos* ts, vs_type tipo);

#endif
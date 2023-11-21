#ifndef __TABELA_DE_SIMBOLS_H__
#define __TABELA_DE_SIMBOLS_H__

#define TAM_TS 100
#define TAM_IDENT 20
#define NUM_PARAM_MAX 20
#define DESCONHECIDO -1000

typedef enum categoria_simbolos {
  var_simples, param_formal, proc_cs
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
typedef struct tipo_parametro_informacao
{
  vs_type tipo;
  p_type passagem;
} t_pinf;


// Estrutura que define Simbolo
typedef struct t_simbolo
{
  char identificador[TAM_IDENT];
  cat_simb categoria;
  int nv_lex;
  int off_set; //deslocamenteo
  vs_type tipo;
  //para parametro formal 
  p_type passagem;
  //para procedimento
  char rotulo[TAM_IDENT];
  int n_params;
  t_pinf param_infs[NUM_PARAM_MAX];
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
void tabela_simbolos_push(
  tab_simbolos* ts,
  char* ident_name,
  cat_simb categoria,
  int nv_lex,
  int off_set,
  vs_type tipo,
  char* rotulo,
  p_type passagem
);


//----------------Funções de Tabela de Simbolos----------------------//
void tabela_simbolos_atualiza_tipo_ultimas_vs_ou_pf(tab_simbolos* ts, vs_type tipo);

//Tabela de Simbolos Atualiza
int tabela_simbolos_atualiza_offset__ultimos_pfs(tab_simbolos* ts, int nv_lex);
void tabela_simbolos_atualiza_passagem__ultimos_pfs(tab_simbolos* ts, int nv_lex, p_type pt);
void tabela_simbolos_atualiza_procedimento(tab_simbolos*ts, int nv_lex, int num_param);

//Tabela de Simbolos Remove
void tabela_simbolos_remove_pfs_do_nv_lex(tab_simbolos* ts, int nv_lex);
void tabela_simbolos_remove_procedimentos_internos_do_nv_lex(tab_simbolos* ts, int nv_lex);
int tabela_simbolos_remove_vs_ultimo_nv_lex(tab_simbolos* ts);

//Tabela de Simbolos Busca
int tabela_simbolos_busca_simbolo(tab_simbolos* ts, char* identificador);

//Tabela de Simbolos Atualiza em Batch
int ts_push_pi_cat_nvlex_tipo(tab_simbolos* ts, p_str* pi, cat_simb cat, int nv_lex, vs_type tipo);

//---------------- FIM Funções de Tabela de Simbolos----------------------//

//----------------Funções de Pilhas ----------------------//

void pilha_string_push(p_str* pi, char*  identi);
void pilha_string_pop_n(p_str* pi, int n);
void pilha_string_reset(p_str* pi);

void pilha_vs_type_push(pilha_vs_type* pi, vs_type tipo);
vs_type pilha_vs_type_pop(pilha_vs_type* pi);
void pilha_vs_type_reset(pilha_vs_type* pi);
void pilhas_vs_type_reset(pilha_vs_type* pi1, pilha_vs_type* pi2);


//---------------- FIM Funções de Pilhas----------------------//


//----------------Funções de Rótulos ----------------------//

void resolveTipoTermoFatores(pilha_vs_type* piT, pilha_vs_type* piF);
void resolveTipoP1P2toP1(pilha_vs_type* pi1, pilha_vs_type* pi2);
void geraRotulo(p_str* p_rot, int* n_rotulos);
void gera2Rotulos(p_str* p_rot, int* n_rotulos);


//---------------- FIM Funções de Rótulos----------------------//



// Auxiliar para gerarCodigo/Procedimento-----------------------
void chamada_de_procedimento(tab_simbolos* ts, int proc_indx, int num_vars, int nv_lex, pilha_vs_type* expType);
void carrega_identidade_valor_endereco_vi(tab_simbolos* ts, char* token, int  l_elem, int num_var, pilha_vs_type* p_fator);
void carrega_identidade_procedimento(t_simbolo* param_real, t_pinf* param_formal, pilha_vs_type* p_fator);
void carrega_identidade_atribuicao(t_simbolo* param_real, pilha_vs_type* p_fator);
void armazena_identidade_vlr_vlrInd(tab_simbolos* ts, int  l_elem, pilha_vs_type* p_fator, pilha_vs_type* p_termo);

// VERIFICAÇÕES -----------------------
void verifica_left_elem_categoria_vs(tab_simbolos* ts, int indx);
void verifica_tipo_do_tipo_referencia(t_simbolo* p_real, t_pinf* p_form);
void verificaParametrosTipo(t_simbolo* simb, pilha_vs_type* expType);


// MAPS -------------------------------
vs_type map_simbolo_vs_type(int simb);
// void map_simbolos_comando_relacao(simbolos simb);
void map_simbolos_comando_relacao(int simb);

#endif
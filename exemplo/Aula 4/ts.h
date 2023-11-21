#ifndef __TABELA_DE_SIMBOLS_H__
#define __TABELA_DE_SIMBOLS_H__

#define TAM_TS 100
#define TAM_IDENT 20

// Estrutura que define Simbolo
typedef struct t_simbolo
{
  char nome[TAM_IDENT];
  int nv_lex;
  
} t_simbolo;

// Estrutura que define a Tabela de Simbolos (TS)
typedef struct tabela_simbolos
{
  int topo;
  t_simbolo pilha[TAM_TS];


} tabela_simbolos;



#endif


void tabela_simbolos_init(tabela_simbolos* ts);

/*!
  \brief Apeenda Simbolo na Tabela de Simbolos
  
  \param nv_lex nivel lexico
  \param ident_name o nome do simpolo, aka token, adicionado.

*/
void tabela_simbolos_push(tabela_simbolos* ts, int nv_lex, char* ident_name);

/*!
  \brief Print pilha da tabela de simbolos
  
  \param ts ponteiro para o semaforo.
*/
void print_pilha(tabela_simbolos ts);
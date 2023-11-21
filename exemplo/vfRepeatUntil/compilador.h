#ifndef __COMPILADOR_H__
#define __COMPILADOR_H__


/* -------------------------------------------------------------------
 *            Arquivo: compilador.h
 * -------------------------------------------------------------------
 *              Autor: Bruno Muller Junior
 *               Data: 08/2007
 *      Atualizado em: [09/08/2020, 19h:01m]
 *
 * -------------------------------------------------------------------
 *
 * Tipos, protótipos e variáveis globais do compilador (via extern)
 *
 * ------------------------------------------------------------------- */

#define TAM_TOKEN 16
#define TAM_TS 100
#define TAM_IDENT 20
#include "ts.h"
#include "io.h"

typedef enum simbolos {
  simb_program, simb_var, simb_begin, simb_end,
  simb_identificador, simb_ponto, simb_virgula,
  simb_ponto_e_virgula, simb_dois_pontos, simb_atribuicao,
  simb_mais, simb_menos, simb_or, simb_multiplicar,
  simb_dividir, simb_and, simb_abre_parenteses, 
  simb_fecha_parenteses, simb_label, simb_type,
  simb_integer, simb_boolean, simb_array, simb_of, simb_procedure,
  simb_function, simb_if, simb_then, simb_else,
  simb_goto, simb_while, simb_repeat, simb_until, simb_numero, simb_igual,
  simb_diferente, simb_menor_igual_que, simb_maior_igual_que,
  simb_menor_que, simb_maior_que, simb_read, simb_write,
  simb_not, simb_true, simb_false, simb_do, simb_dividirb,
  simb_dois_pontos_seq
} simbolos;

/* -------------------------------------------------------------------
 * variáveis globais
 * ------------------------------------------------------------------- */

extern simbolos simbolo, relacao;
extern char token[TAM_TOKEN];
extern int nivel_lexico;
extern int desloc;
extern int nl;
extern int nc;
extern int l_elem;
extern int operacao;


/* -------------------------------------------------------------------
 * prototipos globais
 * ------------------------------------------------------------------- */

void finalizaCompilador();
void geraCodigo (char*, char*);
void geraCodigoParams (char* rot, char* comando, char* arg);
void geraCodigo1ParamNum (char* rot, char* comando, int arg);
void geraCodigo2ParamsNum (char* rot, char* comando, int arg1, int arg2);
void geraCodigo2ParamsCharNum(char* rot, char* comando, char* arg1, int arg2);
void geraCodigoOperacao(simbolos operacao);
void geraCodigoREAD(tab_simbolos* ts, p_str* pi);
void geraCodigoWRITE(tab_simbolos* ts, p_str* pi);
int yylex();
void yyerror(const char *s);


#endif
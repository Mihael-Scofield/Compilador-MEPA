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

typedef enum simbolos {
  simb_program, simb_var, simb_begin, simb_end,
  simb_identificador, simb_numero, simb_ponto,
  simb_virgula, simb_ponto_e_virgula, simb_dois_pontos,
  simb_atribuicao, simb_mais, simb_menos, simb_or, simb_multiplicar,
  simb_dividir, simb_and, simb_abre_parenteses, simb_fecha_parenteses,
  simb_label, simb_type, simb_integer, simb_array, simb_of, simb_procedure,
  simb_function, simb_if, simb_then, simb_else, simb_goto,
  simb_while, 
} simbolos;


/* -------------------------------------------------------------------
 * variáveis globais
 * ------------------------------------------------------------------- */

extern simbolos simbolo, relacao;
extern char token[TAM_TOKEN];
extern int nivel_lexico;
extern int desloc;
extern int nl;


/* -------------------------------------------------------------------
 * prototipos globais
 * ------------------------------------------------------------------- */

void geraCodigo (char*, char*);
int yylex();
void yyerror(const char *s);

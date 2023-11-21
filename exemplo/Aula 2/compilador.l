
/* -------------------------------------------------------------------
 *            Arquivo: compilador.l
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

%{


#include<stdio.h>
#include<string.h>

#include "compilador.h"
#include "compilador.tab.h"

//#define IMPRIME(STR) {};
#define IMPRIME(STR) printf("%s    # %s \n", STR, token);

int nl = 1;

%}

pulo_linha [\n]

descarte [\t ]+

ident [a-zA-Z][a-zA-Z0-9]*

numero [0-9]+

comentario "(*".*"*)"

%%

{pulo_linha} {nl++;}

{descarte}

{comentario}

program { 
  simbolo  = simb_program;
  strncpy (token, yytext, TAM_TOKEN);
  IMPRIME("program ");
  return PROGRAM;
}

var { 
  simbolo = simb_var;
  strncpy (token, yytext, TAM_TOKEN);
  IMPRIME("var  ");
  return VAR;
}

begin { 
  simbolo = simb_begin;
  strncpy (token, yytext, TAM_TOKEN);
  IMPRIME("begin ");
  return T_BEGIN;
}

label { 
  simbolo = simb_label;
  strncpy (token, yytext, TAM_TOKEN);
  IMPRIME("label ");
  return LABEL;
 }

type { 
  simbolo = simb_type;
  strncpy (token, yytext, TAM_TOKEN);
  IMPRIME("type ");
  return TYPE;
 }

integer { 
  simbolo = simb_integer;
  strncpy (token, yytext, TAM_TOKEN);
  IMPRIME(" inteiro ");
  return INTEIRO;
 }

array {
  simbolo = simb_array;
  strncpy (token, yytext, TAM_TOKEN);
  IMPRIME("array ");
  return ARRAY;
}

of { 
  simbolo = simb_of;
  strncpy (token, yytext, TAM_TOKEN);
  IMPRIME("of ");
  return OF;
 }

procedure { 
  simbolo = simb_procedure;
  strncpy (token, yytext, TAM_TOKEN);
  IMPRIME("procedure ");
  return PROCEDURE;
 }

function { 
  simbolo = simb_function;
  strncpy (token, yytext, TAM_TOKEN);
  IMPRIME("function ");
  return FUNCTION;
 }

if { 
  simbolo = simb_if;
  strncpy (token, yytext, TAM_TOKEN);
  IMPRIME("if ");
  return IF;
 }

then { 
  simbolo = simb_then;
  strncpy (token, yytext, TAM_TOKEN);
  IMPRIME("then ");
  return THEN;
 }

else { 
  simbolo = simb_else;
  strncpy (token, yytext, TAM_TOKEN);
  IMPRIME("else ");
  return ELSE;
 }

goto { 
  simbolo = simb_goto;
  strncpy (token, yytext, TAM_TOKEN);
  IMPRIME("goto ");
  return GOTO;
 }

while { 
  simbolo = simb_while;
  strncpy (token, yytext, TAM_TOKEN);
  IMPRIME("while ");
  return WHILE;
 }

end { 
  simbolo = simb_end;
  strncpy (token, yytext, TAM_TOKEN);
  IMPRIME("end  ");
  return T_END;
 }

:= { 
  simbolo = simb_atribuicao;
  strncpy (token, yytext, TAM_TOKEN);
  IMPRIME(" atribuicao  ");
  return ATRIBUICAO;
}

\+ { 
  simbolo = simb_mais;
  strncpy (token, yytext, TAM_TOKEN);
  IMPRIME(" mais  ");
  return MAIS;
}

\- { 
  simbolo = simb_menos;
  strncpy (token, yytext, TAM_TOKEN);
  IMPRIME(" menos  ");
  return MENOS;
}

or { 
  simbolo = simb_or;
  strncpy (token, yytext, TAM_TOKEN);
  IMPRIME(" or  ");
  return OR;
}

\* { 
  simbolo = simb_multiplicar;
  strncpy (token, yytext, TAM_TOKEN);
  IMPRIME(" vezes  ");
  return MULTIPLICA;
}

\/ { 
  simbolo = simb_dividir;
  strncpy (token, yytext, TAM_TOKEN);
  IMPRIME(" divide  ");
  return DIVIDE;
}

and { 
  simbolo = simb_and;
  strncpy (token, yytext, TAM_TOKEN);
  IMPRIME(" and  ");
  return AND;
}

\; { 
  simbolo = simb_ponto_e_virgula;
  strncpy (token, yytext, TAM_TOKEN);
  IMPRIME(" pt_virgula  ");
  return PONTO_E_VIRGULA;
}

\: { 
  simbolo = simb_dois_pontos;
  strncpy (token, yytext, TAM_TOKEN);
  IMPRIME(" dois pontos ");
  return DOIS_PONTOS;
}

\, { 
  simbolo = simb_virgula;
  strncpy (token, yytext, TAM_TOKEN);
  IMPRIME(" virgula  ");
  return VIRGULA;
}

\. { 
  simbolo = simb_ponto;
  strncpy (token, yytext, TAM_TOKEN);
  IMPRIME(" ponto  ");
  return PONTO;
}

\( { 
  simbolo = simb_abre_parenteses;
  strncpy (token, yytext, TAM_TOKEN);
  IMPRIME(" abre_parenteses  ");
  return ABRE_PARENTESES;
}

\) { 
  simbolo = simb_fecha_parenteses;
  strncpy (token, yytext, TAM_TOKEN);
  IMPRIME(" fecha_parenteses ");
  return FECHA_PARENTESES;
}

{ident} { 
  simbolo = simb_identificador;
  strncpy (token, yytext, TAM_TOKEN);
  IMPRIME(" ident  ");
  return IDENT;
}

%%

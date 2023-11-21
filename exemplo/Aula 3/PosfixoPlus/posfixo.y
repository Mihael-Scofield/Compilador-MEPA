
%{
#include <stdio.h>
#include "posfixo.h"
%}

%token IDENT_I MAIS MENOS ASTERISCO DIV ABRE_PARENTESES FECHA_PARENTESES IDENT_B AND OR

%%

expr       : expr MAIS termo {printf ("+"); } |
             expr MENOS termo {printf ("-"); } |
             expr OR termo  {printf ("or"); } | 
             termo
;

termo      : IDENT_I operador IDENT_B {yyerror("Operando com variaveis de tipos incompativeis.\n"); } |
             IDENT_B operador IDENT_I {yyerror("Operando com variaveis de tipos incompativeis.\n"); } |
             termo ASTERISCO fator  {printf ("*"); } | 
             termo DIV fator  {printf ("/"); }|
             termo AND fator  {printf ("and"); } |
             fator
;

operador   : MAIS |
             MENOS |
             OR |
             ASTERISCO |
             DIV |
             AND 
;


fator      : IDENT_I {printf ("A"); } | 
             IDENT_B {printf ("B"); }
;


%%

int main (int argc, char** argv) {
   yyparse();
   printf("\n");
}



%{
#include <stdio.h>
%}

%token INT BOOL MAIS MENOS ASTERISCO DIV ABRE_PARENTESES FECHA_PARENTESES
%token OR AND

%%

geral : expr | bool_expr ;

expr       : expr MAIS termo {printf ("+"); } |
             expr MENOS termo {printf ("-"); } | 
             termo
;

bool_expr  : bool_expr OR bool_termo {printf ("∨"); } |
             bool_termo
;

termo      : termo ASTERISCO fator_int  {printf ("*"); }| 
             termo DIV fator_int  {printf ("/"); }|
             fator_int
;

bool_termo : bool_termo AND bool_fator {printf ("∧"); } |
             bool_fator
;

fator_int      : INT {printf ("A"); }
;

bool_fator      : BOOL {printf ("B"); }
;


%%

main (int argc, char** argv) {
   yyparse();
   printf("\n");
}


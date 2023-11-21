
// Testar se funciona corretamente o empilhamento de par�metros
// passados por valor ou por refer�ncia.


%{
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "compilador.h"
#include "ts.h"

int num_vars;
int nivel_lexico;
tabela_simbolos ts;
char char_aux1[20];
char char_aux2[20];


%}

%token PROGRAM VAR T_BEGIN LABEL TYPE INTEIRO ARRAY OF  PROCEDURE
%token FUNCTION IF THEN ELSE GOTO WHILE T_END ATRIBUICAO MAIS MENOS
%token OR MULTIPLICA DIVIDE AND PONTO_E_VIRGULA DOIS_PONTOS VIRGULA
%token PONTO ABRE_PARENTESES FECHA_PARENTESES IDENT

%%

programa    :{
               geraCodigo (NULL, "INPP");
             }
             PROGRAM IDENT
             ABRE_PARENTESES lista_idents FECHA_PARENTESES PONTO_E_VIRGULA
             bloco PONTO {
               finalizaCompilador();
               geraCodigo (NULL, "PARA");
             }
;

bloco       :
              parte_declara_vars
              {
              }

              comando_composto
              ;




parte_declara_vars:  var
;


var         : { } VAR declara_vars
            |
;

declara_vars: declara_vars declara_var
            | declara_var
;

declara_var : { }
              lista_id_var DOIS_PONTOS
              tipo
              { /* AMEM */
               //   itoa(ts.topo, char_aux, 10);
               strcpy(char_aux1, "MEPA ");
               sprintf(char_aux2, "%d", ts.topo);
               strcat(char_aux1, char_aux2);
               geraCodigo (NULL, char_aux1);
              }
              PONTO_E_VIRGULA
;

tipo        : IDENT {
               
               }
;

lista_id_var: lista_id_var VIRGULA IDENT
              {
                  /* insere �ltima vars na tabela de s�mbolos */ 
                  /*nivel_lexico*/
                  tabela_simbolos_push(&ts, nivel_lexico, token );
                  // tabela_simbolos_push(ts, )

              }
            | IDENT 
               { 
                  /* insere vars na tabela de s�mbolos */
                  tabela_simbolos_push(&ts, nivel_lexico, token);
            
              }
;

lista_idents: lista_idents VIRGULA IDENT
            | IDENT
;


comando_composto: T_BEGIN comandos T_END

comandos:
;


%%

void yyerror(const char *s){
   fprintf(stderr, "%s\n", s);
   return;
}

int main (int argc, char** argv) {
   FILE* fp;
   extern FILE* yyin;

   if (argc<2 || argc>2) {
         printf("usage compilador <arq>a %d\n", argc);
         return(-1);
      }

   fp=fopen (argv[1], "r");
   if (fp == NULL) {
      printf("usage compilador <arq>b\n");
      return(-1);
   }


/* -------------------------------------------------------------------
 *  Inicia a Tabela de S�mbolos
 * ------------------------------------------------------------------- */

   tabela_simbolos_init(&ts);
   nivel_lexico=0;

   yyin=fp;

   if(yyparse()!=0){
      fprintf(stderr, "Nao consegui montar arvore de derivação.\n");
      fprintf(stderr, "Erro (%d,%d): Token \"%s\" não esperado.\n",nl, nc, token);
   }

   return 0;
}

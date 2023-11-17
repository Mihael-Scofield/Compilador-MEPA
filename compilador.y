
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
int nv_lex;
tab_simbolos ts;

%}

%token PROGRAM ABRE_PARENTESES FECHA_PARENTESES
%token VIRGULA PONTO_E_VIRGULA DOIS_PONTOS PONTO
%token T_BEGIN T_END VAR IDENT ATRIBUICAO
%token LABEL NUMERO INTEIRO BOLLEANO

%%

/*01 - Regra de inicializacao */
programa : {
      geraCodigo (NULL, "INPP");
   }
   PROGRAM IDENT
   ABRE_PARENTESES lista_idents FECHA_PARENTESES PONTO_E_VIRGULA
   bloco PONTO {
      geraCodigo (NULL, "PARA");
   }
;

/*02 - Regra de tratamento dos blocos */
/*Bloco tem muitos Ous quebrar em vários blocos*/
bloco :
   parte_de_declaracao_de_rotulos_init
   parte_declara_vars_init
;

/*03 - Declara rotulos*/
parte_de_declaracao_de_rotulos_init:
   LABEL parte_de_declaracao_de_rotulos PONTO_E_VIRGULA
   |
;

/*03.2 - Declara rotulo*/
parte_de_declaracao_de_rotulos:
   parte_de_declaracao_de_rotulos VIRGULA numero
   | numero
;

/*06 - Declaracao de tipo */ 
tipo : 
   INTEIRO { tabela_simbolos_atualiza_tipo_ultimas_vs_ou_pf(&ts, integer_type); }
;

/*06.b Tomaz- Adaptado só inteiro*/ 
tipo_func : 
   INTEIRO
   | BOLLEANO
;

/*08 - Regra para declaracao de var basica*/
parte_declara_vars_init:
   VAR {
      num_vars = 0; // Para ignorar os parametros formais iniciais até aula futura.
   }
   parte_declara_vars {
      geraCodigo1ParamNum(NULL, "AMEM ", num_vars);
      num_vars = 0;
   }|
;

parte_declara_vars:
   parte_declara_vars declara_var PONTO_E_VIRGULA
   | declara_var PONTO_E_VIRGULA
;

/*09 - Regra de declaracao de var direta */
declara_var : 
   lista_idents_dec_var DOIS_PONTOS tipo
;

/*10 - Rotulos */
lista_idents: 
   lista_idents VIRGULA IDENT
   | IDENT
;

/*10.2 - Rotulos diretos */
lista_idents_dec_var: 
   lista_idents_dec_var VIRGULA IDENT
   {
      tabela_simbolos_push(&ts, token, var_simples, nv_lex, num_vars, desc_type, NULL, desc_ptype);
      num_vars++;
   }
   | IDENT 
   {
      tabela_simbolos_push(&ts, token, var_simples, nv_lex, num_vars, desc_type, NULL, desc_ptype);
      num_vars++;
   }
;

/*10.3 - parametros formais */
lista_idents_param_formal: 
   lista_idents_param_formal VIRGULA IDENT
   {
      //Nao se sabe o offset ainda. DESCONHECIDO só para colocar algo
      tabela_simbolos_push(&ts, token, param_formal, nv_lex, DESCONHECIDO, desc_type, NULL, desc_ptype);
   }
   | IDENT 
   {
      //Nao se sabe o offset ainda. -1000 só para colocar algo
      tabela_simbolos_push(&ts, token, param_formal, nv_lex, DESCONHECIDO, desc_type, NULL, desc_ptype);
   }
;

/*10.4 - parametros de leitura*/
lista_idents_read: 
   lista_idents_read VIRGULA IDENT
   {
      int indx_simb = tabela_simbolos_busca_simbolo(&ts, token);
      geraCodigo (NULL, "LEIT");
      geraCodigo2ParamsNum(NULL, "ARMZ ", ts.pilha[indx_simb].nv_lex, ts.pilha[indx_simb].off_set);
   }
   | IDENT
   {
      int indx_simb = tabela_simbolos_busca_simbolo(&ts, token);
      geraCodigo (NULL, "LEIT");
      geraCodigo2ParamsNum(NULL, "ARMZ ", ts.pilha[indx_simb].nv_lex, ts.pilha[indx_simb].off_set);
   }
;

/*32. Declaracao de rotulos numero a numero */
numero:
   NUMERO {
      geraCodigoParams(NULL, "CRCT ", token);
   }
;



%%

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

   yyin=fp;
   yyparse();

   return 0;
}

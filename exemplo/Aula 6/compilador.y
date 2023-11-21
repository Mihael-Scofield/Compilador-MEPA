
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
int l_elem; // Variável da Esquerda left_element. indexador da variável de atribuição.
// int operacao; // operacao ou tipo XD
// cat_simb categoria;
tab_simbolos ts;
// pilha_ident pi;
vs_type vs_tipo;

%}

%token PROGRAM VAR T_BEGIN LABEL TYPE INTEIRO ARRAY OF  PROCEDURE
%token FUNCTION IF THEN ELSE GOTO WHILE T_END ATRIBUICAO MAIS MENOS
%token OR MULTIPLICA DIVIDE AND PONTO_E_VIRGULA DOIS_PONTOS VIRGULA
%token PONTO ABRE_PARENTESES FECHA_PARENTESES NUMERO IDENT 
%token IGUAL DIFERENTE MENOR_IGUAL_QUE MAIOR_IGUAL_QUE MENOR_QUE 
%token MAIOR_QUE READ WRITE NOT

%%

/*01. Tomaz*/
programa :
   {
      geraCodigo (NULL, "INPP");
      // categoria = param_formal;
   }
   PROGRAM IDENT
   ABRE_PARENTESES lista_idents FECHA_PARENTESES PONTO_E_VIRGULA
   bloco PONTO 
   {
      finalizaCompilador();
      geraCodigo (NULL, "PARA");
   }
;

/*02. Tomaz*/
bloco :
   VAR 
   {
      num_vars = 0; // Para ignorar os parametros formais iniciais até aula futura.
      // pilha_identificador_reset(&pi); // Para ignorar os parametros formais iniciais até aula futura.
      // categoria = var_simples;
   }
   parte_declara_vars {
      geraCodigo1ParamNum(NULL, "AMEM ", num_vars);
      num_vars = 0;
   } comando_composto
   | comando_composto

;

/*6. Tomaz- Adaptado só inteiro*/ 
// tipo : 
//    INTEIRO
// ;

/*08. Tomaz*/
//Com soh integer. Se quiser colocar em duas linhas vai dar ruim.
// Tirei VAR da regra para tornar mais fácil a composição da regra.
parte_declara_vars :
   parte_declara_vars declara_var PONTO_E_VIRGULA
   | declara_var PONTO_E_VIRGULA
;

/*09. Tomaz*/
declara_var : 
   { vs_tipo=integer_type; }
   lista_idents_dec_var DOIS_PONTOS INTEIRO
;

/*10. Tomaz*/
lista_idents: 
   lista_idents VIRGULA identificador
   | identificador
;

/*10.b Tomaz*/
lista_idents_dec_var: 
   lista_idents_dec_var VIRGULA IDENT
   {
      tabela_simbolos_push(&ts, token, var_simples, nv_lex, num_vars, vs_tipo);
      num_vars++;
   }
   | IDENT 
   {
      tabela_simbolos_push(&ts, token, var_simples, nv_lex, num_vars, vs_tipo);
      num_vars++;
   }
;

/*10.c Tomaz*/
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

/*16.1 Tomaz*/
comando_composto: 
   T_BEGIN comandos T_END 
   {
      /*DMEM*/
      geraCodigo1ParamNum(NULL, "DMEM ", tabela_simbolos_remove_vs_ultimo_nv_lex(&ts));
   }
;

/*16.2 Tomaz*/
comandos:
   comandos comando PONTO_E_VIRGULA
   |comando PONTO_E_VIRGULA
;

/*17. Tomaz*/
comando:
   numero comando_sem_rotulo
   | comando_sem_rotulo
;

/*18. Tomaz - atribuição ou chamada de procedimento ou ...... Por enquanto só atribuição, chamada_de_procedimento - TODO*/
comando_sem_rotulo:
   atribuicao
   | chamada_de_procedimento
;

/*19. Tomaz*/
atribuicao:
   varivel
   {
      l_elem = tabela_simbolos_busca_simbolo(&ts, token);
   }
   ATRIBUICAO expressao
   {
      geraCodigo2ParamsNum(NULL, "ARMZ ", ts.pilha[l_elem].nv_lex, ts.pilha[l_elem].off_set);
   }
;

/*20. Tomaz*/
/*chamada_de_procedimento: <identificador>[(<lista de expressões>)] */
/*Por enquanto só READ and WRITE*/
chamada_de_procedimento:
   READ ABRE_PARENTESES lista_idents_read FECHA_PARENTESES
   | WRITE ABRE_PARENTESES lista_de_expressoes_write FECHA_PARENTESES
;

/*24. Tomaz */
// lista_de_expressoes:
//    lista_de_expressoes VIRGULA expressao
//    | expressao
// ;

/*24.b Tomaz */
lista_de_expressoes_write:
   lista_de_expressoes_write VIRGULA expressao {geraCodigo (NULL, "IMPR");}
   | expressao {geraCodigo (NULL, "IMPR");}
;

/*25. Tomaz*/
expressao:
   expressao_simples
   | relacao expressao_simples
;

/*26. Tomaz - TODO comparadores não estão nem no lex ainda TODO*/
relacao:
   IGUAL
   | DIFERENTE
   | MENOR_IGUAL_QUE
   | MAIOR_IGUAL_QUE
   | MENOR_QUE 
   | MAIOR_QUE
;

/*27.1 Tomaz - deve ter uma maneira melhor de fazer!*/
expressao_simples: /*[+|-]<termo>{(+|-|or) <termo>}*/
   MAIS termo termos
   |
   MENOS termo
   {
      /*A multiplicação pode ser aplicada no fim de uma divisão e multiplicação.*/
      /*Não poderia com o AND, mas o semântico deve dar erro nesse caso.*/
      geraCodigo1ParamNum(NULL, "CRCT ", -1); 
      geraCodigo (NULL, "MULT");
   }
   termos
   |
   termo termos
   |
   MAIS termo
   |
   MENOS
   termo
   {
      /*A multiplicação pode ser aplicada no fim de uma divisão e multiplicação.*/
      /*Não poderia com o AND, mas o semântico deve dar erro nesse caso.*/
      geraCodigo1ParamNum(NULL, "CRCT ", -1); 
      geraCodigo (NULL, "MULT");
   }
   | termo
;

/*27.2 Tomaz - Para lidar com repetição*/
termos:
   termos MAIS termo { geraCodigo (NULL, "SOMA"); }
   | termos MENOS termo { geraCodigo (NULL, "SUBT"); }
   | termos OR termo { geraCodigo (NULL, "DISJ"); }
   | MAIS termo { geraCodigo (NULL, "SOMA"); }
   | MENOS termo { geraCodigo (NULL, "SUBT"); }
   | OR termo { geraCodigo (NULL, "DISJ"); }
;

/*28. Tomaz*/
termo:
   fator MULTIPLICA fator { geraCodigo (NULL, "MULT");}
   |fator DIVIDE fator { geraCodigo (NULL, "DIVI");}
   |fator AND fator { geraCodigo (NULL, "CONJ");}
   | fator
;

/*29. Tomaz - Por enquanto só variável e Número - TODO*/
fator:
   varivel 
   {
      int indx_var = tabela_simbolos_busca_simbolo(&ts, token);
      geraCodigo2ParamsNum(NULL, "CRVL ", ts.pilha[indx_var].nv_lex, ts.pilha[indx_var].off_set);
   }
   |numero
   // |chamada_de_funcao
   |ABRE_PARENTESES expressao FECHA_PARENTESES
   |NOT fator
;

/*30. Tomaz - ou IDENT [lista de expressões ] ....... Por enquanto só IDENT - TODO*/
varivel:
   IDENT
;

/*31. Tomaz */
// chamada_de_funcao:
//    IDENT | IDENT lista_de_expressoes
// ;

/*32. Tomaz - TODO */
numero:
   NUMERO
   {
      geraCodigoParams(NULL, "CRCT ", token);
   }
;

/*34. Tomaz - Esse cóidigo pode ser passado para o 10 e a regra 34 já foi resolvido no .l 
   Porém, time que ganhando não se mexe. XD!
*/
identificador: 
   IDENT {
      // pilha_identificador_push(&pi, token);
      // tabela_simbolos_push(&ts, token,  categoria, nv_lex, num_vars);
      // num_vars++;
   }
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

   fp = fopen (argv[1], "r");
   if (fp == NULL) {
      printf("usage compilador <arq>b\n");
      return(-1);
   }


/* -------------------------------------------------------------------
 *  Inicia a Tabela de S�mbolos
 * ------------------------------------------------------------------- */

   tabela_simbolos_init(&ts);
   num_vars = 0;
   nv_lex = 0;
   l_elem = -1;
   // operacao = -1;
   vs_tipo = desc_type;
   // pilha_identificador_reset(&pi);

   yyin = fp;

   if(yyparse()!=0){
      fprintf(stderr, "Nao consegui montar arvore de derivação.\n");
      fprintf(stderr, "Erro (%d,%d): Token \"%s\" não esperado.\n",nl, nc, token);
   }

   return 0;
}

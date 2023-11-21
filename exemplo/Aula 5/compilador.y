
// Testar se funciona corretamente o empilhamento de par�metros
// passados por valor ou por refer�ncia.


%{
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "compilador.h"
#include "ts.h"

int num_vars = 0;
int nv_lex = 0;
int indx_var_atrib = 0; // indexador da variável de atribuição.
int operacao = -1;
cat_simb categoria;
tab_simbolos ts;


%}

%token PROGRAM VAR T_BEGIN LABEL TYPE INTEIRO ARRAY OF  PROCEDURE
%token FUNCTION IF THEN ELSE GOTO WHILE T_END ATRIBUICAO MAIS MENOS
%token OR MULTIPLICA DIVIDE AND PONTO_E_VIRGULA DOIS_PONTOS VIRGULA
%token PONTO ABRE_PARENTESES FECHA_PARENTESES NUMERO IDENT 
%token IGUAL DIFERENTE MENOR_IGUAL_QUE MAIOR_IGUAL_QUE MENOR_QUE 
%token MAIOR_QUE

%%

/*01. Tomaz*/
programa :
   {
      geraCodigo (NULL, "INPP");
      categoria = param_formal;
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
   parte_declara_vars
   {
   }
   comando_composto
;

/*6. Tomaz- Adaptado só inteiro*/ 
tipo : 
   INTEIRO {
      tabela_simbolos_atualiza_tipo_ultimas_vs(&ts, integer_type);
   }
;

/*08. Tomaz*/
//Com soh integer. Se quiser colocar em duas linhas vai dar ruim.
parte_declara_vars :  
   {
      num_vars = 0; // Para ignorar os parametros formais iniciais até aula futura.
      categoria = var_simples;
   }
   VAR declara_var
;


/*09. Tomaz*/
declara_var : 
   { }
   lista_idents DOIS_PONTOS tipo
   {
      /* AMEM */
      geraCodigo1ParamNum(NULL, "AMEM ", num_vars);
      num_vars=0;
   }
   PONTO_E_VIRGULA
;

/*10. Tomaz*/
lista_idents: 
   lista_idents VIRGULA identificador
   | identificador
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

/*18. Tomaz - atribuição ou chamada de procedimento ou ...... Por enquanto só atribuição - TODO*/
comando_sem_rotulo:
   atribuicao
;

/*19. Tomaz*/
atribuicao:
   varivel
   {
      indx_var_atrib = tabela_simbolos_busca_simbolo(&ts, token);
   }
   ATRIBUICAO expressao
   {
      geraCodigoOperacao(operacao);
      geraCodigo2ParamsNum(NULL, "ARMZ ", ts.pilha[indx_var_atrib].nv_lex, ts.pilha[indx_var_atrib].off_set);
   }
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
   | MENOS termo termos
   | termo termos
   | MAIS termo
   | MENOS termo
   | termo
;

/*27.2 Tomaz - Para lidar com repetição*/
termos:
   operacoes_pri1 
   termo termos
   | operacoes_pri1
   termo
;

/*27.3 Tomaz - Para simplificar Operações com prioridade menor */
operacoes_pri1:
   MAIS { operacao =simbolo;}
   | MENOS { operacao =simbolo;}
   | OR  { operacao =simbolo;}
;

/*28.1 Tomaz*/
termo:
   fator fatores
   | fator
;

/*28.2 Tomaz*/
fatores:
   MULTIPLICA fator
   |DIVIDE fator
   |AND fator
;

/*29. Tomaz - Por enquanto só variável e Número - TODO*/
fator:
   varivel
   {
      int indx_var = tabela_simbolos_busca_simbolo(&ts, token);
      geraCodigo2ParamsNum(NULL, "CRVL ", ts.pilha[indx_var].nv_lex, ts.pilha[indx_var].off_set);
   }
   |numero 
;

/*30. Tomaz - ou IDENT [lista de expressões ] ....... Por enquanto só IDENT - TODO*/
varivel:
   IDENT {
      
      
   }
;

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
      tabela_simbolos_push(&ts, token,  categoria, nv_lex, num_vars);
      num_vars++;
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
   nv_lex = 0;

   yyin = fp;

   if(yyparse()!=0){
      fprintf(stderr, "Nao consegui montar arvore de derivação.\n");
      fprintf(stderr, "Erro (%d,%d): Token \"%s\" não esperado.\n",nl, nc, token);
   }

   return 0;
}

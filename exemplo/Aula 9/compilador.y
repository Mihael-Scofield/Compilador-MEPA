
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
p_str p_rotulos;
// vs_type vs_tipo;

pilha_vs_type pilha_E;
pilha_vs_type pilha_T;
pilha_vs_type pilha_F;

%}

%token PROGRAM VAR T_BEGIN LABEL TYPE INTEIRO ARRAY OF  PROCEDURE
%token FUNCTION IF THEN ELSE GOTO WHILE T_END ATRIBUICAO MAIS MENOS
%token OR MULTIPLICA DIVIDE AND PONTO_E_VIRGULA DOIS_PONTOS VIRGULA
%token PONTO ABRE_PARENTESES FECHA_PARENTESES NUMERO IDENT 
%token IGUAL DIFERENTE MENOR_IGUAL_QUE MAIOR_IGUAL_QUE MENOR_QUE 
%token MAIOR_QUE READ WRITE NOT BOLLEANO T_TRUE T_FALSE DO DIVIDEB

//Copiado do código professor
%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

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
tipo : 
   INTEIRO { tabela_simbolos_atualiza_tipo_ultimas_vs(&ts, integer_type); }
   | BOLLEANO { tabela_simbolos_atualiza_tipo_ultimas_vs(&ts, bool_type); }
;

/*08. Tomaz*/
//Com soh integer. Se quiser colocar em duas linhas vai dar ruim.
// Tirei VAR da regra para tornar mais fácil a composição da regra.
parte_declara_vars :
   parte_declara_vars declara_var PONTO_E_VIRGULA
   | declara_var PONTO_E_VIRGULA
;

/*09. Tomaz*/
declara_var : 
   lista_idents_dec_var DOIS_PONTOS tipo
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
      tabela_simbolos_push(&ts, token, var_simples, nv_lex, num_vars, desc_type);
      num_vars++;
   }
   | IDENT 
   {
      tabela_simbolos_push(&ts, token, var_simples, nv_lex, num_vars, desc_type);
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

comando_composto_while: 
   T_BEGIN comandos T_END
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
   | comando_repetitivo
   | comando_composto
   | comando_condicional
;

/*19. Tomaz*/
atribuicao:
   varivel
   {
      l_elem = tabela_simbolos_busca_simbolo(&ts, token);
      pilhas_vs_type_reset(&pilha_F, &pilha_T);
   }
   ATRIBUICAO expressao
   {
      geraCodigo2ParamsNum(NULL, "ARMZ ", ts.pilha[l_elem].nv_lex, ts.pilha[l_elem].off_set);
      pilha_vs_type_push(&pilha_T, ts.pilha[l_elem].tipo);
      resolveTipoTermoFatores(&pilha_T,&pilha_T);
      pilhas_vs_type_reset(&pilha_F, &pilha_T);
   }
;

/*20. Tomaz*/
/*chamada_de_procedimento: <identificador>[(<lista de expressões>)] */
/*Por enquanto só READ and WRITE*/
chamada_de_procedimento:
   READ ABRE_PARENTESES lista_idents_read FECHA_PARENTESES
   | WRITE ABRE_PARENTESES lista_de_expressoes_write FECHA_PARENTESES
;

/*22.a Tomaz*/
comando_condicional:
   if_then
   cond_else 
   { 
      geraCodigo(p_rotulos.pilha[p_rotulos.topo], "NADA");  //R01: NADA // Fim do ELSE
      pilha_string_pop_n(&p_rotulos,2); 
   }
;

/*22.b Tomaz*/
if_then:
   IF 
   {
      pilhas_vs_type_reset(&pilha_F, &pilha_T);
   }
   expressao 
   {
      pilhas_vs_type_reset(&pilha_F, &pilha_T);
      gera2Rotulos(&p_rotulos);
      geraCodigoParams(NULL, "DSVF ", p_rotulos.pilha[p_rotulos.topo-1]);  //DSVF ROO
   }
      THEN comando_sem_rotulo
   {
      geraCodigoParams(NULL, "DSVS ", p_rotulos.pilha[p_rotulos.topo]);    //DSVS R01 //Fim do Then desvio Fim ELSE
      geraCodigo(p_rotulos.pilha[p_rotulos.topo-1], "NADA");               //ROO: NADA // Começo do ELSE
   }
;

/*22.c Tomaz*/
cond_else:
   ELSE comando_sem_rotulo
   | %prec LOWER_THAN_ELSE
;

/*23. Tomaz */
comando_repetitivo:
   WHILE
   {
      gera2Rotulos(&p_rotulos);
      geraCodigo(p_rotulos.pilha[p_rotulos.topo-1], "NADA");
   }
   expressao 
   {
      geraCodigoParams(NULL, "DSVF ", p_rotulos.pilha[p_rotulos.topo]); 
      pilhas_vs_type_reset(&pilha_F, &pilha_T); 
   } DO comando_composto_while 
   {
      geraCodigoParams(NULL, "DSVS ", p_rotulos.pilha[p_rotulos.topo-1]); 
      geraCodigo(p_rotulos.pilha[p_rotulos.topo], "NADA");
      pilha_string_pop_n(&p_rotulos,2);
   }
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

/*25. Tomaz - MODIFICADO 25 e 26*/
expressao:
   expressao relacao 
   | expressao_simples
;

/*26. Tomaz - TODO comparadores não estão nem no lex ainda TODO*/
relacao:
   IGUAL expressao_simples { geraCodigo (NULL, "CMIG"); resolveTipoTermoFatores(&pilha_T,&pilha_T); }
   | DIFERENTE expressao_simples { geraCodigo (NULL, "CMDG"); resolveTipoTermoFatores(&pilha_T,&pilha_T); }
   | MENOR_IGUAL_QUE expressao_simples { geraCodigo (NULL, "CMEG"); resolveTipoTermoFatores(&pilha_T,&pilha_T); }
   | MAIOR_IGUAL_QUE expressao_simples { geraCodigo (NULL, "CMAG"); resolveTipoTermoFatores(&pilha_T,&pilha_T); }
   | MENOR_QUE expressao_simples { geraCodigo (NULL, "CMME"); resolveTipoTermoFatores(&pilha_T,&pilha_T); }
   | MAIOR_QUE expressao_simples { geraCodigo (NULL, "CMMA"); resolveTipoTermoFatores(&pilha_T,&pilha_T);}
;

/*27.1 Tomaz - deve ter uma maneira melhor de fazer!*/
expressao_simples: /*[+|-]<termo>{(+|-|or) <termo>}*/
   MAIS termo termos {resolveTipoTermoFatores(&pilha_T,&pilha_T);}
   |
   MENOS termo
   {
      /*A multiplicação pode ser aplicada no fim de uma divisão e multiplicação.*/
      /*Não poderia com o AND, mas o semântico deve dar erro nesse caso.*/
      geraCodigo1ParamNum(NULL, "CRCT ", -1); 
      geraCodigo (NULL, "MULT");
   }
   termos {
      resolveTipoTermoFatores(&pilha_T,&pilha_T);
   }
   |
   termo termos {
      resolveTipoTermoFatores(&pilha_T,&pilha_T);
   }
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
   termo MULTIPLICA fator 
   { 
      resolveTipoP1P2toP1(&pilha_T,&pilha_F);
      geraCodigo (NULL, "MULT");
   }
   |termo DIVIDE fator 
   { 
     
      resolveTipoP1P2toP1(&pilha_T,&pilha_F);
      geraCodigo (NULL, "DIVI");
   }
   |termo AND fator 
   {
      resolveTipoP1P2toP1(&pilha_T,&pilha_F);
      geraCodigo (NULL, "CONJ");
   }
   | fator {
      pilha_vs_type_push(&pilha_T, pilha_vs_type_pop(&pilha_F));
   }
;

/*29. Tomaz - Por enquanto só variável e Número - TODO*/
fator:
   varivel 
   {
      int indx_var = tabela_simbolos_busca_simbolo(&ts, token);
      geraCodigo2ParamsNum(NULL, "CRVL ", ts.pilha[indx_var].nv_lex, ts.pilha[indx_var].off_set);
      pilha_vs_type_push(&pilha_F, ts.pilha[indx_var].tipo);
   }
   |numero { pilha_vs_type_push(&pilha_F, integer_type);}
   |vlr_booleano { pilha_vs_type_push(&pilha_F, bool_type);}
   // |chamada_de_funcao
   |ABRE_PARENTESES expressao FECHA_PARENTESES
   |NOT fator { geraCodigo(NULL, "NEGA");}
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

/*32.b Tomaz - TODO */
vlr_booleano:
   T_TRUE {geraCodigo1ParamNum(NULL, "CRCT ", 1);}
   |T_FALSE {geraCodigo1ParamNum(NULL, "CRCT ", 0);}
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
   // vs_tipo = desc_type;
   pilha_string_reset(&p_rotulos);

   pilha_vs_type_reset(&pilha_E);
   pilha_vs_type_reset(&pilha_T);
   pilha_vs_type_reset(&pilha_F);

   yyin = fp;

   if(yyparse()!=0){
      fprintf(stderr, "Nao consegui montar arvore de derivação.\n");
      fprintf(stderr, "Erro (%d,%d): Token \"%s\" não esperado.\n",nl, nc, token);
   }

   return 0;
}

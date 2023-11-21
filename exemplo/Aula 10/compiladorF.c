
/* -------------------------------------------------------------------
 *            Aquivo: compilador.c
 * -------------------------------------------------------------------
 *              Autor: Bruno Muller Junior
 *               Data: 08/2007
 *      Atualizado em: [09/08/2020, 19h:01m]
 *
 * -------------------------------------------------------------------
 *
 * Funções auxiliares ao compilador
 *
 * ------------------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compilador.h"
#include "ts.h"


/* -------------------------------------------------------------------
 *  variáveis globais
 * ------------------------------------------------------------------- */

simbolos simbolo, relacao;
char token[TAM_TOKEN];

FILE* fp=NULL;
void geraCodigo (char* rot, char* comando) {

  if (fp == NULL) {
    fp = fopen ("MEPA", "w");
  }
  printf("GGeraCodigo %s \n", comando);
  fflush(NULL);

  if ( rot == NULL ) {
    fprintf(fp, "     %s\n", comando); fflush(fp);
  } else {
    fprintf(fp, "%s: %s\n", rot, comando); fflush(fp);
  }
}

void geraCodigoParams (char* rot, char* comando, char* arg) {
  // 20 é suficiente até agora MEPA sempre tem 4 o que deixa numeros com até 15 digitos.
  if (strlen(arg) > 14){
    fprintf(stderr, "geraCodigo1Param: Numero \"%s\" muito grande para comendo MEPA.\n", arg);
    exit(-1);
  }
  char strg_aux[20];
  strcpy(strg_aux, comando);
  strcat(strg_aux, arg);
  geraCodigo (rot, strg_aux);

  return;
}

void geraCodigo1ParamNum (char* rot, char* comando, int arg) {
  // 20 é suficiente até agora MEPA sempre tem 4 o que deixa numeros com até 15 digitos.
  if (arg > 1.0E15){
    fprintf(stderr, "geraCodigo1Param: Numero %d muito grande para comendo MEPA.\n", arg);
    exit(-1);
  }
  char strg_aux[20];

  // itoa(num_vars, char_aux2, 10); //Warning ! TODO- Testar DINF
  sprintf(strg_aux, "%d", arg);
  geraCodigoParams(rot, comando, strg_aux);
  return;
}

void geraCodigo2ParamsNum(char* rot, char* comando, int arg1, int arg2) {
  // 20 é suficiente até agora MEPA sempre tem 4 o que deixa numeros com até 15 digitos.
  if (arg1 > 1.0E15){
    fprintf(stderr, "geraCodigo1Param: Numero %d muito grande para comendo MEPA.\n", arg1);
    exit(-1);
  }
  if (arg2 > 1.0E15){
    fprintf(stderr, "geraCodigo1Param: Numero %d muito grande para comendo MEPA.\n", arg2);
    exit(-1);
  }
  char strg_aux1[20];
  char strg_aux2[20];

  // itoa(num_vars, char_aux2, 10); //Warning ! TODO- Testar DINF
  sprintf(strg_aux1, "%d,", arg1);
  sprintf(strg_aux2, "%d", arg2);
  strcat(strg_aux1, strg_aux2);
  geraCodigoParams(rot, comando, strg_aux1);
  return;
}

void geraCodigo2ParamsCharNum(char* rot, char* comando, char* arg1, int arg2) {
  char strg_aux[20];
  strcpy(strg_aux, comando);
  strcat(strg_aux, arg1);
  strcat(strg_aux, ",");
  geraCodigo1ParamNum(rot, strg_aux, arg2);
  return;
}

void geraCodigoOperacao(simbolos operacao){
  // simb_mais, simb_menos, simb_or, simb_multiplicar,
  // simb_dividir, simb_and,  simb_igual, - TODO todas as operações
  switch (operacao)
  {
    case -1:
      return;
    case simb_mais:
      geraCodigo (NULL, "SOMA ");
      break;
    case simb_menos:
      geraCodigo (NULL, "SUBT ");
      break;
    case simb_multiplicar:
      geraCodigo (NULL, "MULT ");
      break;
    case simb_dividir:
      geraCodigo (NULL, "DIVI ");
      break;
    default:
      geraCodigo (NULL, "NAO IMPLEMENTADA ");
      break;
  }
}

int imprimeErro ( char* erro ) {
  fprintf (stderr, "Erro na linha %d - %s\n", nl, erro);
  exit(-1);
}

void finalizaCompilador(){
   printf("Finalizando...\n");
   return;
}


/*READ and WRITE - meio estranho eles ter um geraCódigo próprio, mas fica mais limpo o código*/
void geraCodigoREAD(tab_simbolos* ts, p_str* pi){
  for(int i=0; i<pi->topo+1; i++){
    int indx_simb = tabela_simbolos_busca_simbolo(ts, pi->pilha[i]);
    geraCodigo(NULL, "LEIT");
    geraCodigo2ParamsNum(NULL, "ARMZ ", ts->pilha[indx_simb].nv_lex, ts->pilha[indx_simb].off_set);
  }
  pilha_string_reset(pi);
  return;
}

void geraCodigoWRITE(tab_simbolos* ts, p_str* pi){
  for(int i=0; i<pi->topo+1; i++){
    int indx_simb = tabela_simbolos_busca_simbolo(ts, pi->pilha[i]);
    geraCodigo2ParamsNum(NULL, "CRVL ", ts->pilha[indx_simb].nv_lex, ts->pilha[indx_simb].off_set);
    geraCodigo(NULL, "IMPR");
  }
  pilha_string_reset(pi);
  return;
}
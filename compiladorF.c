
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

  if ( rot == NULL ) {
    fprintf(fp, "     %s\n", comando); fflush(fp);
  } else {
    fprintf(fp, "%s: %s \n", rot, comando); fflush(fp);
  }
}

void geraCodigoParams (char* rot, char* comando, char* arg) {
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
  if (arg > 1.0E15){
    fprintf(stderr, "geraCodigo1Param: Numero %d muito grande para comendo MEPA.\n", arg);
    exit(-1);
  }
  char strg_aux[20];

  sprintf(strg_aux, "%d", arg);
  geraCodigoParams(rot, comando, strg_aux);
  return;
}

int imprimeErro ( char* erro ) {
  fprintf (stderr, "Erro na linha %d - %s\n", nl, erro);
  exit(-1);
}

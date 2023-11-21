#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ts.h"
#include "io.h"

#define DEBUG 1

void print_tabela_simbolos(tab_simbolos ts){
   printf("Tabela de Simbolos: (topo:%d e tamanho: %d)\n", ts.topo, ts.topo+1);
   for(int i=0; i < ts.topo+1; i++){
      printf("%d - ", i);
      print_simbolo(ts.pilha[i]);
   }
   return;
}

void print_simbolo(t_simbolo simb){
   printf("Ident [%s], ", simb.identificador);
   
   switch (simb.categoria){
      case var_simples:
         printf("CAT [ VS ], nv_lex %d, deslocamento ", simb.nv_lex);
         print_numero_format(simb.off_set);
         printf(", ");
         print_vs_tipo(simb.tipo);
         break;
      case param_formal:
         printf("CAT [ PF ], nv_lex %d, deslocamento ", simb.nv_lex );
         print_numero_format(simb.off_set);
         printf(", ");
         print_vs_tipo(simb.tipo);
         printf(", ");
         print_tipo_passagem(simb.passagem);
         break;
      case proc_cs:
         printf("CAT [PROC], nv_lex %d, rótulo %s, n# params ", simb.nv_lex, simb.rotulo);
         print_numero_format(simb.n_params);
         if(simb.n_params>0){
            print_params_infs(simb);
         }
         break;
      default:
         break;;
   }
   printf("\n");
   return;
}

void print_pilha_string(p_str* pi){
   for (int i=0; i<pi->topo+1; i++){
      printf("[%d] - %s \n", i, pi->pilha[i]);
   }
   return;
}

void print_pilha_vs_type(pilha_vs_type* pi){
   for (int i=0; i<pi->topo+1; i++){
      switch (pi->pilha[i]){
      case integer_type:
         printf("[ inteiro ]");
         break;
      case bool_type:
         printf("[ booleano ]");
         break;
      default:
         printf("[ desconhecido ]");
         break;;
      }
   }
   printf("\n");
   return;
}

void print_tipo_passagem(p_type pt){
   switch (pt){
      case valor_ptype:
         printf("passagem [ valor  ]");
         break;
      case variavel_ptype:
         printf("passagem [variavel]");
         break;
      default:
         printf("passagem [ ?????? ]");
         break;
   }
   return;
}

void print_vs_tipo(vs_type vst){
   switch (vst){
      case integer_type:
         printf("TIPO [ inteiro  ]");
         break;
      case bool_type:
         printf("TIPO [ booleano ]");
         break;
      default:
         printf("TIPO [ ???????? ]");
         break;
   }
   return;
}

void print_numero_format(int n){
   if(n==DESCONHECIDO){
      printf("[???]");
      return;
   }
   if(n>9){
      printf("[ %d]", n);
      return;
   }
   if(n<-9){
      printf("[%d]", n);
      return;
   }
   if(n<0){
      printf("[ %d]", n);
      return;
   }
   printf("[  %d]", n);
   return;
}

void print_params_infs(t_simbolo simb){
   printf(" { ");
   for(int i=0; i<simb.n_params; i++){
      printf(" [ ");
      print_vs_tipo(simb.param_infs[i].tipo);
      printf(", ");
      print_tipo_passagem(simb.param_infs[i].passagem);
      printf(" ], ");
   }
   printf(" } ");
   return;
}
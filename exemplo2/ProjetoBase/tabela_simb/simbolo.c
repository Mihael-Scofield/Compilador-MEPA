#include <stdlib.h>
#include <string.h>

#include "simbolo.h"

struct simbolo cria_simbolo(char *ident, int cat, int niv, struct cat_conteudo conteudo){
    struct simbolo s;
    s.identificador = malloc(strlen(ident)+1); 
    strcpy(s.identificador, ident);

    s.categoria = cat;
    s.nivel = niv;
    s.conteudo = conteudo;
    return s;
}

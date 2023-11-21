#ifndef __SIMBOLO__
#define __SIMBOLO__

enum tipo_simbolo{
    variavel,
    parametro,
    procedimento,
    funcao
};

enum tipo_variavel{
    pas_integer,
    pas_float,
    pas_boolean,
    undefined_type
};

enum tipo_passagem{
    parametro_copia,
    parametro_ref
};


/* Três tipos de símbolos */
struct variavel{
    int tipo;
    int deslocamento;
};

struct parametro{
    int tipo;
    int deslocamento;
    int passagem;
};

struct procedimento{
    int rotulo;
    int qtd_parametros;
    struct parametro lista[128];
};

/*------------------------*/

struct simbolo{
    char *identificador;
    int categoria;
    int nivel;
    struct cat_conteudo{
        struct variavel var;
        struct parametro param;
        struct procedimento proc;
    } conteudo;
};

struct simbolo cria_simbolo(char *ident, int cat, int niv, struct cat_conteudo tipo);

#endif

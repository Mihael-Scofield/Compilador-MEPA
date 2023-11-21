/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 6 "compilador.y"

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
int n_rotulos;
// vs_type vs_tipo;

pilha_vs_type pilha_E;
pilha_vs_type pilha_T;
pilha_vs_type pilha_F;
pilha_inf_f p_Funcoes;


#line 96 "compilador.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "compilador.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_PROGRAM = 3,                    /* PROGRAM  */
  YYSYMBOL_VAR = 4,                        /* VAR  */
  YYSYMBOL_T_BEGIN = 5,                    /* T_BEGIN  */
  YYSYMBOL_LABEL = 6,                      /* LABEL  */
  YYSYMBOL_TYPE = 7,                       /* TYPE  */
  YYSYMBOL_INTEIRO = 8,                    /* INTEIRO  */
  YYSYMBOL_ARRAY = 9,                      /* ARRAY  */
  YYSYMBOL_OF = 10,                        /* OF  */
  YYSYMBOL_PROCEDURE = 11,                 /* PROCEDURE  */
  YYSYMBOL_FUNCTION = 12,                  /* FUNCTION  */
  YYSYMBOL_IF = 13,                        /* IF  */
  YYSYMBOL_THEN = 14,                      /* THEN  */
  YYSYMBOL_ELSE = 15,                      /* ELSE  */
  YYSYMBOL_GOTO = 16,                      /* GOTO  */
  YYSYMBOL_WHILE = 17,                     /* WHILE  */
  YYSYMBOL_T_END = 18,                     /* T_END  */
  YYSYMBOL_ATRIBUICAO = 19,                /* ATRIBUICAO  */
  YYSYMBOL_MAIS = 20,                      /* MAIS  */
  YYSYMBOL_MENOS = 21,                     /* MENOS  */
  YYSYMBOL_OR = 22,                        /* OR  */
  YYSYMBOL_MULTIPLICA = 23,                /* MULTIPLICA  */
  YYSYMBOL_DIVIDE = 24,                    /* DIVIDE  */
  YYSYMBOL_AND = 25,                       /* AND  */
  YYSYMBOL_PONTO_E_VIRGULA = 26,           /* PONTO_E_VIRGULA  */
  YYSYMBOL_DOIS_PONTOS = 27,               /* DOIS_PONTOS  */
  YYSYMBOL_VIRGULA = 28,                   /* VIRGULA  */
  YYSYMBOL_PONTO = 29,                     /* PONTO  */
  YYSYMBOL_ABRE_PARENTESES = 30,           /* ABRE_PARENTESES  */
  YYSYMBOL_FECHA_PARENTESES = 31,          /* FECHA_PARENTESES  */
  YYSYMBOL_NUMERO = 32,                    /* NUMERO  */
  YYSYMBOL_IDENT = 33,                     /* IDENT  */
  YYSYMBOL_IGUAL = 34,                     /* IGUAL  */
  YYSYMBOL_DIFERENTE = 35,                 /* DIFERENTE  */
  YYSYMBOL_MENOR_IGUAL_QUE = 36,           /* MENOR_IGUAL_QUE  */
  YYSYMBOL_MAIOR_IGUAL_QUE = 37,           /* MAIOR_IGUAL_QUE  */
  YYSYMBOL_MENOR_QUE = 38,                 /* MENOR_QUE  */
  YYSYMBOL_MAIOR_QUE = 39,                 /* MAIOR_QUE  */
  YYSYMBOL_READ = 40,                      /* READ  */
  YYSYMBOL_WRITE = 41,                     /* WRITE  */
  YYSYMBOL_NOT = 42,                       /* NOT  */
  YYSYMBOL_BOLLEANO = 43,                  /* BOLLEANO  */
  YYSYMBOL_T_TRUE = 44,                    /* T_TRUE  */
  YYSYMBOL_T_FALSE = 45,                   /* T_FALSE  */
  YYSYMBOL_DO = 46,                        /* DO  */
  YYSYMBOL_DIVIDEB = 47,                   /* DIVIDEB  */
  YYSYMBOL_DOIS_PONTOS_SEQ = 48,           /* DOIS_PONTOS_SEQ  */
  YYSYMBOL_LOWER_THAN_ELSE = 49,           /* LOWER_THAN_ELSE  */
  YYSYMBOL_YYACCEPT = 50,                  /* $accept  */
  YYSYMBOL_programa = 51,                  /* programa  */
  YYSYMBOL_52_1 = 52,                      /* $@1  */
  YYSYMBOL_bloco = 53,                     /* bloco  */
  YYSYMBOL_parte_de_declaracao_de_rotulos_init = 54, /* parte_de_declaracao_de_rotulos_init  */
  YYSYMBOL_parte_de_declaracao_de_rotulos = 55, /* parte_de_declaracao_de_rotulos  */
  YYSYMBOL_parte_de_definicao_de_tipos_init = 56, /* parte_de_definicao_de_tipos_init  */
  YYSYMBOL_parte_de_definicao_de_tipos = 57, /* parte_de_definicao_de_tipos  */
  YYSYMBOL_definicao_de_tipo = 58,         /* definicao_de_tipo  */
  YYSYMBOL_tipo = 59,                      /* tipo  */
  YYSYMBOL_tipo_func = 60,                 /* tipo_func  */
  YYSYMBOL_indice = 61,                    /* indice  */
  YYSYMBOL_parte_declara_vars_init = 62,   /* parte_declara_vars_init  */
  YYSYMBOL_63_2 = 63,                      /* $@2  */
  YYSYMBOL_parte_declara_vars = 64,        /* parte_declara_vars  */
  YYSYMBOL_declara_var = 65,               /* declara_var  */
  YYSYMBOL_lista_idents = 66,              /* lista_idents  */
  YYSYMBOL_lista_idents_dec_var = 67,      /* lista_idents_dec_var  */
  YYSYMBOL_lista_idents_param_formal = 68, /* lista_idents_param_formal  */
  YYSYMBOL_lista_idents_read = 69,         /* lista_idents_read  */
  YYSYMBOL_parte_de_declaracao_de_sub_rotinas_init = 70, /* parte_de_declaracao_de_sub_rotinas_init  */
  YYSYMBOL_parte_de_declaracao_de_sub_rotinas = 71, /* parte_de_declaracao_de_sub_rotinas  */
  YYSYMBOL_declaracao_de_procedimento = 72, /* declaracao_de_procedimento  */
  YYSYMBOL_73_3 = 73,                      /* $@3  */
  YYSYMBOL_74_4 = 74,                      /* $@4  */
  YYSYMBOL_75_5 = 75,                      /* $@5  */
  YYSYMBOL_76_6 = 76,                      /* $@6  */
  YYSYMBOL_declaracao_de_procedimento_pf = 77, /* declaracao_de_procedimento_pf  */
  YYSYMBOL_declaracao_de_funcao = 78,      /* declaracao_de_funcao  */
  YYSYMBOL_79_7 = 79,                      /* $@7  */
  YYSYMBOL_80_8 = 80,                      /* $@8  */
  YYSYMBOL_81_9 = 81,                      /* $@9  */
  YYSYMBOL_82_10 = 82,                     /* $@10  */
  YYSYMBOL_declaracao_de_funcao_pf = 83,   /* declaracao_de_funcao_pf  */
  YYSYMBOL_parametros_formais = 84,        /* parametros_formais  */
  YYSYMBOL_secao_de_parametros_formais = 85, /* secao_de_parametros_formais  */
  YYSYMBOL_secao_de_parametros_formais_vars = 86, /* secao_de_parametros_formais_vars  */
  YYSYMBOL_comando_composto = 87,          /* comando_composto  */
  YYSYMBOL_comando_composto_while = 88,    /* comando_composto_while  */
  YYSYMBOL_comandos = 89,                  /* comandos  */
  YYSYMBOL_comandos_end = 90,              /* comandos_end  */
  YYSYMBOL_comando = 91,                   /* comando  */
  YYSYMBOL_comando_sem_rotulo = 92,        /* comando_sem_rotulo  */
  YYSYMBOL_93_11 = 93,                     /* $@11  */
  YYSYMBOL_atribuicao_ou_chamda_de_procedimento = 94, /* atribuicao_ou_chamda_de_procedimento  */
  YYSYMBOL_95_12 = 95,                     /* $@12  */
  YYSYMBOL_atribuicao = 96,                /* atribuicao  */
  YYSYMBOL_97_13 = 97,                     /* $@13  */
  YYSYMBOL_chamada_de_procedimento = 98,   /* chamada_de_procedimento  */
  YYSYMBOL_chamada_de_procedimento_RW = 99, /* chamada_de_procedimento_RW  */
  YYSYMBOL_100_14 = 100,                   /* $@14  */
  YYSYMBOL_101_15 = 101,                   /* $@15  */
  YYSYMBOL_chamada_subrotina_args = 102,   /* chamada_subrotina_args  */
  YYSYMBOL_comando_condicional = 103,      /* comando_condicional  */
  YYSYMBOL_if_then = 104,                  /* if_then  */
  YYSYMBOL_105_16 = 105,                   /* $@16  */
  YYSYMBOL_106_17 = 106,                   /* $@17  */
  YYSYMBOL_cond_else = 107,                /* cond_else  */
  YYSYMBOL_comando_repetitivo = 108,       /* comando_repetitivo  */
  YYSYMBOL_109_18 = 109,                   /* $@18  */
  YYSYMBOL_110_19 = 110,                   /* $@19  */
  YYSYMBOL_lista_de_expressoes_sr = 111,   /* lista_de_expressoes_sr  */
  YYSYMBOL_lista_de_expressoes_write = 112, /* lista_de_expressoes_write  */
  YYSYMBOL_expressao = 113,                /* expressao  */
  YYSYMBOL_relacao = 114,                  /* relacao  */
  YYSYMBOL_expressao_simples = 115,        /* expressao_simples  */
  YYSYMBOL_116_20 = 116,                   /* $@20  */
  YYSYMBOL_termos = 117,                   /* termos  */
  YYSYMBOL_termo = 118,                    /* termo  */
  YYSYMBOL_fator = 119,                    /* fator  */
  YYSYMBOL_varivel_ou_cmd_func = 120,      /* varivel_ou_cmd_func  */
  YYSYMBOL_121_21 = 121,                   /* $@21  */
  YYSYMBOL_chamada_subrotina_func_args = 122, /* chamada_subrotina_func_args  */
  YYSYMBOL_numero = 123,                   /* numero  */
  YYSYMBOL_vlr_booleano = 124              /* vlr_booleano  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   222

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  50
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  75
/* YYNRULES -- Number of rules.  */
#define YYNRULES  137
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  238

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   304


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    47,    47,    47,    65,    74,    75,    80,    81,    86,
      87,    92,    93,    98,   104,   105,   106,   107,   112,   113,
     118,   126,   125,   136,   140,   141,   146,   151,   152,   157,
     162,   171,   176,   185,   191,   202,   203,   208,   209,   210,
     216,   222,   226,   231,   215,   245,   246,   252,   258,   263,
     269,   251,   283,   284,   290,   291,   296,   297,   298,   303,
     307,   315,   320,   325,   326,   327,   332,   333,   339,   344,
     344,   351,   352,   353,   354,   358,   360,   360,   372,   371,
     386,   392,   391,   397,   396,   404,   405,   410,   421,   425,
     420,   442,   443,   449,   454,   448,   467,   478,   488,   493,
     494,   499,   506,   511,   512,   513,   514,   515,   516,   521,
     524,   523,   534,   538,   540,   548,   553,   554,   555,   556,
     557,   558,   563,   568,   574,   579,   586,   587,   588,   590,
     595,   601,   600,   609,   622,   633,   641,   642
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "PROGRAM", "VAR",
  "T_BEGIN", "LABEL", "TYPE", "INTEIRO", "ARRAY", "OF", "PROCEDURE",
  "FUNCTION", "IF", "THEN", "ELSE", "GOTO", "WHILE", "T_END", "ATRIBUICAO",
  "MAIS", "MENOS", "OR", "MULTIPLICA", "DIVIDE", "AND", "PONTO_E_VIRGULA",
  "DOIS_PONTOS", "VIRGULA", "PONTO", "ABRE_PARENTESES", "FECHA_PARENTESES",
  "NUMERO", "IDENT", "IGUAL", "DIFERENTE", "MENOR_IGUAL_QUE",
  "MAIOR_IGUAL_QUE", "MENOR_QUE", "MAIOR_QUE", "READ", "WRITE", "NOT",
  "BOLLEANO", "T_TRUE", "T_FALSE", "DO", "DIVIDEB", "DOIS_PONTOS_SEQ",
  "LOWER_THAN_ELSE", "$accept", "programa", "$@1", "bloco",
  "parte_de_declaracao_de_rotulos_init", "parte_de_declaracao_de_rotulos",
  "parte_de_definicao_de_tipos_init", "parte_de_definicao_de_tipos",
  "definicao_de_tipo", "tipo", "tipo_func", "indice",
  "parte_declara_vars_init", "$@2", "parte_declara_vars", "declara_var",
  "lista_idents", "lista_idents_dec_var", "lista_idents_param_formal",
  "lista_idents_read", "parte_de_declaracao_de_sub_rotinas_init",
  "parte_de_declaracao_de_sub_rotinas", "declaracao_de_procedimento",
  "$@3", "$@4", "$@5", "$@6", "declaracao_de_procedimento_pf",
  "declaracao_de_funcao", "$@7", "$@8", "$@9", "$@10",
  "declaracao_de_funcao_pf", "parametros_formais",
  "secao_de_parametros_formais", "secao_de_parametros_formais_vars",
  "comando_composto", "comando_composto_while", "comandos", "comandos_end",
  "comando", "comando_sem_rotulo", "$@11",
  "atribuicao_ou_chamda_de_procedimento", "$@12", "atribuicao", "$@13",
  "chamada_de_procedimento", "chamada_de_procedimento_RW", "$@14", "$@15",
  "chamada_subrotina_args", "comando_condicional", "if_then", "$@16",
  "$@17", "cond_else", "comando_repetitivo", "$@18", "$@19",
  "lista_de_expressoes_sr", "lista_de_expressoes_write", "expressao",
  "relacao", "expressao_simples", "$@20", "termos", "termo", "fator",
  "varivel_ou_cmd_func", "$@21", "chamada_subrotina_func_args", "numero",
  "vlr_booleano", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-163)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-111)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -163,    21,    23,  -163,   -22,    32,     1,  -163,    50,     3,
      40,  -163,    78,    57,    67,   108,  -163,    49,  -163,  -163,
     129,   161,  -163,    57,   134,   140,  -163,  -163,    37,  -163,
       4,   129,   136,  -163,  -163,   162,   159,  -163,  -163,  -163,
       6,  -163,  -163,  -163,  -163,   136,   145,    76,   139,   141,
      47,  -163,  -163,     4,   163,   127,   150,  -163,     4,   144,
    -163,  -163,  -163,  -163,  -163,  -163,  -163,  -163,    10,   152,
     153,  -163,  -163,   165,  -163,  -163,     4,    57,  -163,  -163,
    -163,   151,   154,    53,    53,   164,   155,   156,  -163,   166,
    -163,  -163,    47,  -163,  -163,  -163,    59,   167,    59,   160,
     -13,   -13,    53,  -163,   -13,  -163,  -163,    90,  -163,   110,
    -163,  -163,  -163,  -163,    90,  -163,  -163,   158,  -163,   149,
      53,  -163,  -163,  -163,   157,     1,     1,  -163,    85,    11,
    -163,  -163,  -163,    13,    22,   110,   122,    71,   168,  -163,
      53,    53,    53,    53,    53,    53,   175,  -163,   -13,   -13,
     -13,   -13,   -13,   -13,   100,   148,    53,    53,  -163,  -163,
    -163,    51,    62,    90,   112,   131,   133,     4,   169,    59,
    -163,    78,  -163,  -163,  -163,  -163,   100,   116,  -163,    53,
    -163,  -163,  -163,  -163,  -163,  -163,  -163,    47,   132,   132,
     132,  -163,  -163,  -163,   -13,   -13,   -13,   186,    90,    63,
      90,   170,  -163,    53,  -163,     4,   171,   172,  -163,  -163,
    -163,  -163,   173,   100,    83,  -163,   132,   132,   132,    47,
    -163,    53,  -163,  -163,    90,  -163,  -163,  -163,   174,    78,
    -163,    28,    90,  -163,  -163,  -163,   180,  -163
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       2,     0,     0,     1,     0,     0,     0,    28,     0,     0,
       0,    27,     6,     0,     0,    10,   135,     0,     8,     3,
       0,    23,     5,     0,     0,     0,    12,    21,    36,     7,
       0,     9,     0,    40,    47,     0,    35,    38,    39,    14,
       0,    15,    13,    11,    30,    22,     0,     0,     0,     0,
       0,     4,    37,     0,     0,     0,     0,    25,     0,     0,
      41,    48,    88,    93,    69,    81,    83,    73,     0,     0,
      65,    71,    74,    92,    72,    17,     0,     0,    24,    26,
      29,    46,    53,     0,     0,    76,     0,     0,    61,    67,
      68,    64,     0,    87,    16,    20,     0,     0,     0,     0,
       0,     0,     0,   131,     0,   136,   137,    89,   102,   115,
     125,   126,   127,   128,    94,    78,    70,    86,    75,     0,
       0,    66,    63,    91,     0,     0,     0,    32,     0,     0,
      55,    56,    42,     0,     0,   113,   114,     0,   134,   130,
       0,     0,     0,     0,     0,     0,     0,   101,     0,     0,
       0,     0,     0,     0,   112,     0,     0,    98,    77,    80,
      34,     0,     0,   100,     0,     0,     0,     0,     0,     0,
      45,     6,    52,    18,    19,    49,   109,     0,   129,    98,
     132,   103,   104,   105,   106,   107,   108,     0,   119,   120,
     121,   122,   123,   124,     0,     0,     0,     0,    79,     0,
      97,     0,    82,     0,    84,     0,     0,     0,    60,    31,
      54,    43,     0,   111,     0,    90,   116,   117,   118,     0,
      95,     0,    85,    33,    99,    59,    58,    57,     0,     6,
     133,     0,    96,    44,    50,    62,     0,    51
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -163,  -163,  -163,  -162,  -163,  -163,  -163,  -163,   176,   -51,
    -163,  -163,  -163,  -163,  -163,   177,    -8,  -163,    72,  -163,
    -163,  -163,   178,  -163,  -163,  -163,  -163,  -163,  -163,  -163,
    -163,  -163,  -163,  -163,    97,    39,  -163,   181,  -163,   -18,
    -163,   -67,   -68,  -163,  -163,  -163,  -163,  -163,  -163,  -163,
    -163,  -163,  -163,  -163,  -163,  -163,  -163,  -163,  -163,  -163,
    -163,    18,  -163,   -80,  -163,     8,  -163,  -121,   -95,   -94,
    -163,  -163,  -163,    -5,  -163
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,     2,    14,    15,    17,    21,    25,    26,    42,
     175,    54,    28,    32,    45,    46,     8,    47,   128,   161,
      35,    36,    37,    48,    81,   171,   228,    97,    38,    49,
      82,   212,   236,    99,   129,   130,   131,    67,   220,    68,
     122,    69,    70,    85,   116,   117,   118,   156,   158,    71,
      86,    87,   159,    72,    73,    83,   146,    93,    74,    84,
     155,   199,   162,   200,   147,   108,   177,   154,   109,   110,
     111,   138,   180,   112,   113
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      90,    89,    75,   107,   114,   135,   136,    79,    18,   211,
     139,     5,    39,    40,   176,    50,    53,   102,    29,    16,
     103,     3,   137,    62,   123,    94,     4,    63,    88,   104,
     173,   105,   106,    50,     7,    55,    11,   169,    16,   169,
     163,    62,   170,    64,   172,    63,   235,    41,    33,    34,
      65,    66,    50,   188,   189,   190,   213,   191,   192,   193,
      62,    64,     6,   124,    63,   174,    12,   234,    65,    66,
     125,   126,    95,   100,   101,    22,   198,    23,     9,   201,
      64,    10,   202,   102,    13,    16,   103,    65,    66,    16,
     203,   221,   127,   204,   222,   104,    19,   105,   106,   216,
     217,   218,   178,    58,    59,   140,   141,   142,   143,   144,
     145,   221,   167,   168,   230,    20,   208,   165,   166,   215,
     194,   195,   196,   224,   140,   141,   142,   143,   144,   145,
     148,   149,   150,   151,   152,   153,   148,   149,   150,   205,
     168,   232,  -110,  -110,  -110,   151,   152,   153,   181,   182,
     183,   184,   185,   186,   225,   151,   152,   153,   206,     9,
     207,     9,    24,    90,    89,    27,    31,    50,    30,    44,
      33,    57,    60,    76,    61,    77,    78,    80,    91,   -68,
      92,    96,   160,   115,    98,   119,   120,   134,   157,   187,
     127,   219,   121,   132,   197,   133,   164,   214,   179,   229,
     233,   231,   209,   223,   226,   227,   237,    43,   210,     0,
       0,     0,     0,     0,    52,     0,    51,     0,     0,     0,
       0,     0,    56
};

static const yytype_int16 yycheck[] =
{
      68,    68,    53,    83,    84,   100,   101,    58,    13,   171,
     104,    33,     8,     9,   135,     5,    10,    30,    23,    32,
      33,     0,   102,    13,    92,    76,     3,    17,    18,    42,
       8,    44,    45,     5,    33,    40,    33,    26,    32,    26,
     120,    13,    31,    33,    31,    17,    18,    43,    11,    12,
      40,    41,     5,   148,   149,   150,   177,   151,   152,   153,
      13,    33,    30,     4,    17,    43,    26,   229,    40,    41,
      11,    12,    77,    20,    21,    26,   156,    28,    28,    28,
      33,    31,    31,    30,     6,    32,    33,    40,    41,    32,
      28,    28,    33,    31,    31,    42,    29,    44,    45,   194,
     195,   196,    31,    27,    28,    34,    35,    36,    37,    38,
      39,    28,    27,    28,    31,     7,   167,   125,   126,   187,
      20,    21,    22,   203,    34,    35,    36,    37,    38,    39,
      20,    21,    22,    23,    24,    25,    20,    21,    22,    27,
      28,   221,    20,    21,    22,    23,    24,    25,   140,   141,
     142,   143,   144,   145,   205,    23,    24,    25,    27,    28,
      27,    28,    33,   231,   231,     4,    26,     5,    34,    33,
      11,    26,    33,    10,    33,    48,    26,    33,    26,    26,
      15,    30,    33,    19,    30,    30,    30,    27,    30,    14,
      33,     5,    26,    26,    46,    98,   124,   179,    30,    26,
      26,   219,    33,    33,    33,    33,    26,    31,   169,    -1,
      -1,    -1,    -1,    -1,    36,    -1,    35,    -1,    -1,    -1,
      -1,    -1,    45
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    51,    52,     0,     3,    33,    30,    33,    66,    28,
      31,    33,    26,     6,    53,    54,    32,    55,   123,    29,
       7,    56,    26,    28,    33,    57,    58,     4,    62,   123,
      34,    26,    63,    11,    12,    70,    71,    72,    78,     8,
       9,    43,    59,    58,    33,    64,    65,    67,    73,    79,
       5,    87,    72,    10,    61,   123,    65,    26,    27,    28,
      33,    33,    13,    17,    33,    40,    41,    87,    89,    91,
      92,    99,   103,   104,   108,    59,    10,    48,    26,    59,
      33,    74,    80,   105,   109,    93,   100,   101,    18,    91,
      92,    26,    15,   107,    59,   123,    30,    77,    30,    83,
      20,    21,    30,    33,    42,    44,    45,   113,   115,   118,
     119,   120,   123,   124,   113,    19,    94,    95,    96,    30,
      30,    26,    90,    92,     4,    11,    12,    33,    68,    84,
      85,    86,    26,    84,    27,   118,   118,   113,   121,   119,
      34,    35,    36,    37,    38,    39,   106,   114,    20,    21,
      22,    23,    24,    25,   117,   110,    97,    30,    98,   102,
      33,    69,   112,   113,    68,    66,    66,    27,    28,    26,
      31,    75,    31,     8,    43,    60,   117,   116,    31,    30,
     122,   115,   115,   115,   115,   115,   115,    14,   118,   118,
     118,   119,   119,   119,    20,    21,    22,    46,   113,   111,
     113,    28,    31,    28,    31,    27,    27,    27,    59,    33,
      85,    53,    81,   117,   111,    92,   118,   118,   118,     5,
      88,    28,    31,    33,   113,    59,    33,    33,    76,    26,
      31,    89,   113,    26,    53,    18,    82,    26
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    50,    52,    51,    53,    54,    54,    55,    55,    56,
      56,    57,    57,    58,    59,    59,    59,    59,    60,    60,
      61,    63,    62,    62,    64,    64,    65,    66,    66,    67,
      67,    68,    68,    69,    69,    70,    70,    71,    71,    71,
      73,    74,    75,    76,    72,    77,    77,    79,    80,    81,
      82,    78,    83,    83,    84,    84,    85,    85,    85,    86,
      86,    87,    88,    89,    89,    89,    90,    90,    91,    93,
      92,    92,    92,    92,    92,    94,    95,    94,    97,    96,
      98,   100,    99,   101,    99,   102,   102,   103,   105,   106,
     104,   107,   107,   109,   110,   108,   111,   111,   111,   112,
     112,   113,   113,   114,   114,   114,   114,   114,   114,   115,
     116,   115,   115,   115,   115,   115,   117,   117,   117,   117,
     117,   117,   118,   118,   118,   118,   119,   119,   119,   119,
     119,   121,   120,   122,   122,   123,   124,   124
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     9,     5,     3,     0,     3,     1,     3,
       0,     3,     1,     3,     1,     1,     4,     3,     1,     1,
       3,     0,     3,     0,     3,     2,     3,     3,     1,     3,
       1,     3,     1,     3,     1,     1,     0,     2,     1,     1,
       0,     0,     0,     0,    10,     3,     0,     0,     0,     0,
       0,    12,     3,     0,     3,     1,     1,     4,     4,     4,
       3,     3,     3,     3,     2,     1,     1,     0,     1,     0,
       3,     1,     1,     1,     1,     1,     0,     2,     0,     3,
       1,     0,     5,     0,     5,     3,     0,     2,     0,     0,
       6,     2,     0,     0,     0,     6,     3,     1,     0,     3,
       1,     2,     1,     2,     2,     2,     2,     2,     2,     3,
       0,     4,     2,     2,     2,     1,     3,     3,     3,     2,
       2,     2,     3,     3,     3,     1,     1,     1,     1,     3,
       2,     0,     3,     3,     0,     1,     1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* $@1: %empty  */
#line 47 "compilador.y"
   {
      geraCodigo (NULL, "INPP");
      // categoria = param_formal;
   }
#line 1395 "compilador.tab.c"
    break;

  case 3: /* programa: $@1 PROGRAM IDENT ABRE_PARENTESES lista_idents FECHA_PARENTESES PONTO_E_VIRGULA bloco PONTO  */
#line 54 "compilador.y"
   {
      tabela_simbolos_remove_sub_rotinas_internas_do_nv_lex(&ts, nv_lex);
      geraCodigo1ParamNum(NULL, "DMEM ", tabela_simbolos_remove_vs_ultimo_nv_lex(&ts));
      finalizaCompilador();
      geraCodigo (NULL, "PARA");
   }
#line 1406 "compilador.tab.c"
    break;

  case 14: /* tipo: INTEIRO  */
#line 104 "compilador.y"
           { tabela_simbolos_atualiza_tipo_ultimas_vs_ou_pf(&ts, integer_type); }
#line 1412 "compilador.tab.c"
    break;

  case 15: /* tipo: BOLLEANO  */
#line 105 "compilador.y"
              { tabela_simbolos_atualiza_tipo_ultimas_vs_ou_pf(&ts, bool_type); }
#line 1418 "compilador.tab.c"
    break;

  case 21: /* $@2: %empty  */
#line 126 "compilador.y"
   {
      num_vars = 0; // Para ignorar os parametros formais iniciais até aula futura.
      // pilha_identificador_reset(&pi); // Para ignorar os parametros formais iniciais até aula futura.
      // categoria = var_simples;
   }
#line 1428 "compilador.tab.c"
    break;

  case 22: /* parte_declara_vars_init: VAR $@2 parte_declara_vars  */
#line 132 "compilador.y"
   {
      geraCodigo1ParamNum(NULL, "AMEM ", num_vars);
      num_vars = 0;
   }
#line 1437 "compilador.tab.c"
    break;

  case 29: /* lista_idents_dec_var: lista_idents_dec_var VIRGULA IDENT  */
#line 158 "compilador.y"
   {
      tabela_simbolos_push(&ts, token, var_simples, nv_lex, num_vars, desc_type, NULL, desc_ptype);
      num_vars++;
   }
#line 1446 "compilador.tab.c"
    break;

  case 30: /* lista_idents_dec_var: IDENT  */
#line 163 "compilador.y"
   {
      tabela_simbolos_push(&ts, token, var_simples, nv_lex, num_vars, desc_type, NULL, desc_ptype);
      num_vars++;
   }
#line 1455 "compilador.tab.c"
    break;

  case 31: /* lista_idents_param_formal: lista_idents_param_formal VIRGULA IDENT  */
#line 172 "compilador.y"
   {
      //Nao se sabe o offset ainda. DESCONHECIDO só para colocar algo
      tabela_simbolos_push(&ts, token, param_formal, nv_lex, DESCONHECIDO, desc_type, NULL, desc_ptype);
   }
#line 1464 "compilador.tab.c"
    break;

  case 32: /* lista_idents_param_formal: IDENT  */
#line 177 "compilador.y"
   {
      //Nao se sabe o offset ainda. -1000 só para colocar algo
      tabela_simbolos_push(&ts, token, param_formal, nv_lex, DESCONHECIDO, desc_type, NULL, desc_ptype);
   }
#line 1473 "compilador.tab.c"
    break;

  case 33: /* lista_idents_read: lista_idents_read VIRGULA IDENT  */
#line 186 "compilador.y"
   {
      int indx_simb = tabela_simbolos_busca_simbolo(&ts, token);
      geraCodigo (NULL, "LEIT");
      geraCodigo2ParamsNum(NULL, "ARMZ ", ts.pilha[indx_simb].nv_lex, ts.pilha[indx_simb].off_set);
   }
#line 1483 "compilador.tab.c"
    break;

  case 34: /* lista_idents_read: IDENT  */
#line 192 "compilador.y"
   {
      int indx_simb = tabela_simbolos_busca_simbolo(&ts, token);
      geraCodigo (NULL, "LEIT");
      geraCodigo2ParamsNum(NULL, "ARMZ ", ts.pilha[indx_simb].nv_lex, ts.pilha[indx_simb].off_set);
   }
#line 1493 "compilador.tab.c"
    break;

  case 40: /* $@3: %empty  */
#line 216 "compilador.y"
   {
      gera2Rotulos(&p_rotulos, &n_rotulos);
      geraCodigoParams(NULL, "DSVS ", p_rotulos.pilha[p_rotulos.topo-1]);     //Final do Procedimento
      nv_lex++;
      geraCodigo1ParamNum(p_rotulos.pilha[p_rotulos.topo], "ENPR ", nv_lex);  //ENPR 1
   }
#line 1504 "compilador.tab.c"
    break;

  case 41: /* $@4: %empty  */
#line 222 "compilador.y"
         {
      tabela_simbolos_push(&ts, token, proc_cs, nv_lex, -1, desc_type, p_rotulos.pilha[p_rotulos.topo], desc_ptype);
   }
#line 1512 "compilador.tab.c"
    break;

  case 42: /* $@5: %empty  */
#line 226 "compilador.y"
   {
      int num_param = tabela_simbolos_atualiza_offset__ultimos_pfs(&ts, nv_lex);
      tabela_simbolos_atualiza_procedimento(&ts, nv_lex, num_param);
   }
#line 1521 "compilador.tab.c"
    break;

  case 43: /* $@6: %empty  */
#line 231 "compilador.y"
   {
      tabela_simbolos_remove_sub_rotinas_internas_do_nv_lex(&ts, nv_lex);
      geraCodigo1ParamNum(NULL, "DMEM ", tabela_simbolos_remove_vs_ultimo_nv_lex(&ts));
      //o parametros por enquanto
      geraCodigo2ParamsNum(NULL,"RTPR ", nv_lex, tabela_simbolos_remove_pfs_do_nv_lex(&ts, nv_lex));
      nv_lex --;
      geraCodigo(p_rotulos.pilha[p_rotulos.topo-1], "NADA");
      pilha_string_pop_n(&p_rotulos,2);
   }
#line 1535 "compilador.tab.c"
    break;

  case 47: /* $@7: %empty  */
#line 252 "compilador.y"
   {
      gera2Rotulos(&p_rotulos, &n_rotulos);
      geraCodigoParams(NULL, "DSVS ", p_rotulos.pilha[p_rotulos.topo-1]);     //Final do Procedimento/Funcao
      nv_lex++;
      geraCodigo1ParamNum(p_rotulos.pilha[p_rotulos.topo], "ENPR ", nv_lex);  //ENPR 1
   }
#line 1546 "compilador.tab.c"
    break;

  case 48: /* $@8: %empty  */
#line 258 "compilador.y"
         {
      tabela_simbolos_push(&ts, token, funcao_cs, nv_lex, DESCONHECIDO, desc_type, p_rotulos.pilha[p_rotulos.topo], desc_ptype);
   }
#line 1554 "compilador.tab.c"
    break;

  case 49: /* $@9: %empty  */
#line 263 "compilador.y"
   {
      int num_param = tabela_simbolos_atualiza_offset__ultimos_pfs(&ts, nv_lex);
      tabela_simbolos_atualiza_funcao(&ts, nv_lex, num_param, simbolo);
   }
#line 1563 "compilador.tab.c"
    break;

  case 50: /* $@10: %empty  */
#line 269 "compilador.y"
   {
      tabela_simbolos_remove_sub_rotinas_internas_do_nv_lex(&ts, nv_lex);
      geraCodigo1ParamNum(NULL, "DMEM ", tabela_simbolos_remove_vs_ultimo_nv_lex(&ts));
      //o parametros por enquanto
      geraCodigo2ParamsNum(NULL,"RTPR ", nv_lex, tabela_simbolos_remove_pfs_do_nv_lex(&ts, nv_lex));
      nv_lex --;
      geraCodigo(p_rotulos.pilha[p_rotulos.topo-1], "NADA");
      pilha_string_pop_n(&p_rotulos,2);
   }
#line 1577 "compilador.tab.c"
    break;

  case 59: /* secao_de_parametros_formais_vars: VAR lista_idents_param_formal DOIS_PONTOS tipo  */
#line 304 "compilador.y"
   {
      tabela_simbolos_atualiza_passagem__ultimos_pfs(&ts, nv_lex, ref_ptype);
   }
#line 1585 "compilador.tab.c"
    break;

  case 60: /* secao_de_parametros_formais_vars: lista_idents_param_formal DOIS_PONTOS tipo  */
#line 308 "compilador.y"
   {
      tabela_simbolos_atualiza_passagem__ultimos_pfs(&ts, nv_lex, valor_ptype);
   }
#line 1593 "compilador.tab.c"
    break;

  case 69: /* $@11: %empty  */
#line 344 "compilador.y"
         {
      l_elem = tabela_simbolos_busca_simbolo(&ts, token);
      printf(" Atribuicao ou Chamada de procedimento\n Left Elemen\n    ");
      print_simbolo(&ts.pilha[l_elem]);
      pilhas_vs_type_reset(&pilha_F, &pilha_T);
   }
#line 1604 "compilador.tab.c"
    break;

  case 76: /* $@12: %empty  */
#line 360 "compilador.y"
   {
      num_vars=0;
   }
#line 1612 "compilador.tab.c"
    break;

  case 77: /* atribuicao_ou_chamda_de_procedimento: $@12 chamada_de_procedimento  */
#line 364 "compilador.y"
   {
      chamada_de_procedimento(&ts, l_elem, num_vars, nv_lex, &pilha_T);
   }
#line 1620 "compilador.tab.c"
    break;

  case 78: /* $@13: %empty  */
#line 372 "compilador.y"
   {
      verifica_left_elem_categoria_vs(&ts, l_elem);
      pilha_inf_fun_reset(&p_Funcoes);     
   }
#line 1629 "compilador.tab.c"
    break;

  case 79: /* atribuicao: ATRIBUICAO $@13 expressao  */
#line 377 "compilador.y"
   {
      armazena_identidade_vlr_vlrInd(&ts, l_elem, &pilha_F, &pilha_T);
   }
#line 1637 "compilador.tab.c"
    break;

  case 81: /* $@14: %empty  */
#line 392 "compilador.y"
   {
      l_elem = L_READ;
   }
#line 1645 "compilador.tab.c"
    break;

  case 83: /* $@15: %empty  */
#line 397 "compilador.y"
   {
      l_elem = L_WRITE;
   }
#line 1653 "compilador.tab.c"
    break;

  case 87: /* comando_condicional: if_then cond_else  */
#line 412 "compilador.y"
   { 
      geraCodigo(p_rotulos.pilha[p_rotulos.topo], "NADA");  //R01: NADA // Fim do ELSE
      pilha_string_pop_n(&p_rotulos,2); 
   }
#line 1662 "compilador.tab.c"
    break;

  case 88: /* $@16: %empty  */
#line 421 "compilador.y"
   {
      pilhas_vs_type_reset(&pilha_F, &pilha_T);
   }
#line 1670 "compilador.tab.c"
    break;

  case 89: /* $@17: %empty  */
#line 425 "compilador.y"
   {
      //Por causa do erro dois do teste
      //Se termo não for booleano ERRO.
      verifica_ultimo_termo_booleano(&pilha_T);
      pilhas_vs_type_reset(&pilha_F, &pilha_T);
      gera2Rotulos(&p_rotulos, &n_rotulos);
      geraCodigoParams(NULL, "DSVF ", p_rotulos.pilha[p_rotulos.topo-1]);  //DSVF ROO
   }
#line 1683 "compilador.tab.c"
    break;

  case 90: /* if_then: IF $@16 expressao $@17 THEN comando_sem_rotulo  */
#line 434 "compilador.y"
   {
      geraCodigoParams(NULL, "DSVS ", p_rotulos.pilha[p_rotulos.topo]);    //DSVS R01 //Fim do Then desvio Fim ELSE
      geraCodigo(p_rotulos.pilha[p_rotulos.topo-1], "NADA");               //ROO: NADA // Começo do ELSE
   }
#line 1692 "compilador.tab.c"
    break;

  case 93: /* $@18: %empty  */
#line 449 "compilador.y"
   {
      gera2Rotulos(&p_rotulos, &n_rotulos);
      geraCodigo(p_rotulos.pilha[p_rotulos.topo-1], "NADA");
   }
#line 1701 "compilador.tab.c"
    break;

  case 94: /* $@19: %empty  */
#line 454 "compilador.y"
   {
      geraCodigoParams(NULL, "DSVF ", p_rotulos.pilha[p_rotulos.topo]); 
      pilhas_vs_type_reset(&pilha_F, &pilha_T); 
   }
#line 1710 "compilador.tab.c"
    break;

  case 95: /* comando_repetitivo: WHILE $@18 expressao $@19 DO comando_composto_while  */
#line 458 "compilador.y"
   {
      geraCodigoParams(NULL, "DSVS ", p_rotulos.pilha[p_rotulos.topo-1]); 
      geraCodigo(p_rotulos.pilha[p_rotulos.topo], "NADA");
      pilha_string_pop_n(&p_rotulos,2);
   }
#line 1720 "compilador.tab.c"
    break;

  case 96: /* lista_de_expressoes_sr: lista_de_expressoes_sr VIRGULA expressao  */
#line 468 "compilador.y"
   {
      if(p_Funcoes.topo > -1){
         p_Funcoes.pilha[p_Funcoes.topo].num_p ++;

      }
      else{
         num_vars++;
      }
      
   }
#line 1735 "compilador.tab.c"
    break;

  case 97: /* lista_de_expressoes_sr: expressao  */
#line 479 "compilador.y"
   { 
      if(p_Funcoes.topo > -1){
         p_Funcoes.pilha[p_Funcoes.topo].num_p ++;

      }
      else{
         num_vars++;
      }
   }
#line 1749 "compilador.tab.c"
    break;

  case 99: /* lista_de_expressoes_write: lista_de_expressoes_write VIRGULA expressao  */
#line 493 "compilador.y"
                                               {geraCodigo (NULL, "IMPR");}
#line 1755 "compilador.tab.c"
    break;

  case 100: /* lista_de_expressoes_write: expressao  */
#line 494 "compilador.y"
               {geraCodigo (NULL, "IMPR");}
#line 1761 "compilador.tab.c"
    break;

  case 101: /* expressao: expressao relacao  */
#line 500 "compilador.y"
   {
      resolveTipoTermoFatores(&pilha_T,&pilha_T);
      pilha_vs_type_pop(&pilha_T);
      //Resultado de uma relacao é sempre booleano
      pilha_vs_type_push(&pilha_T, bool_type);
   }
#line 1772 "compilador.tab.c"
    break;

  case 103: /* relacao: IGUAL expressao_simples  */
#line 511 "compilador.y"
                           { geraCodigo (NULL, "CMIG");  }
#line 1778 "compilador.tab.c"
    break;

  case 104: /* relacao: DIFERENTE expressao_simples  */
#line 512 "compilador.y"
                                 { geraCodigo (NULL, "CMDG");}
#line 1784 "compilador.tab.c"
    break;

  case 105: /* relacao: MENOR_IGUAL_QUE expressao_simples  */
#line 513 "compilador.y"
                                       { geraCodigo (NULL, "CMEG");}
#line 1790 "compilador.tab.c"
    break;

  case 106: /* relacao: MAIOR_IGUAL_QUE expressao_simples  */
#line 514 "compilador.y"
                                       { geraCodigo (NULL, "CMAG");}
#line 1796 "compilador.tab.c"
    break;

  case 107: /* relacao: MENOR_QUE expressao_simples  */
#line 515 "compilador.y"
                                 { geraCodigo (NULL, "CMME");}
#line 1802 "compilador.tab.c"
    break;

  case 108: /* relacao: MAIOR_QUE expressao_simples  */
#line 516 "compilador.y"
                                 { geraCodigo (NULL, "CMMA");}
#line 1808 "compilador.tab.c"
    break;

  case 109: /* expressao_simples: MAIS termo termos  */
#line 521 "compilador.y"
                     {resolveTipoTermoFatores(&pilha_T,&pilha_T);}
#line 1814 "compilador.tab.c"
    break;

  case 110: /* $@20: %empty  */
#line 524 "compilador.y"
   {
      /*A multiplicação pode ser aplicada no fim de uma divisão e multiplicação.*/
      /*Não poderia com o AND, mas o semântico deve dar erro nesse caso.*/
      geraCodigo1ParamNum(NULL, "CRCT ", -1); 
      geraCodigo (NULL, "MULT");
   }
#line 1825 "compilador.tab.c"
    break;

  case 111: /* expressao_simples: MENOS termo $@20 termos  */
#line 530 "compilador.y"
          {
      resolveTipoTermoFatores(&pilha_T,&pilha_T);
   }
#line 1833 "compilador.tab.c"
    break;

  case 112: /* expressao_simples: termo termos  */
#line 534 "compilador.y"
                {
      resolveTipoTermoFatores(&pilha_T,&pilha_T);
   }
#line 1841 "compilador.tab.c"
    break;

  case 114: /* expressao_simples: MENOS termo  */
#line 542 "compilador.y"
   {
      /*A multiplicação pode ser aplicada no fim de uma divisão e multiplicação.*/
      /*Não poderia com o AND, mas o semântico deve dar erro nesse caso.*/
      geraCodigo1ParamNum(NULL, "CRCT ", -1); 
      geraCodigo (NULL, "MULT");
   }
#line 1852 "compilador.tab.c"
    break;

  case 116: /* termos: termos MAIS termo  */
#line 553 "compilador.y"
                     { geraCodigo (NULL, "SOMA"); }
#line 1858 "compilador.tab.c"
    break;

  case 117: /* termos: termos MENOS termo  */
#line 554 "compilador.y"
                        { geraCodigo (NULL, "SUBT"); }
#line 1864 "compilador.tab.c"
    break;

  case 118: /* termos: termos OR termo  */
#line 555 "compilador.y"
                     { geraCodigo (NULL, "DISJ"); }
#line 1870 "compilador.tab.c"
    break;

  case 119: /* termos: MAIS termo  */
#line 556 "compilador.y"
                { geraCodigo (NULL, "SOMA"); }
#line 1876 "compilador.tab.c"
    break;

  case 120: /* termos: MENOS termo  */
#line 557 "compilador.y"
                 { geraCodigo (NULL, "SUBT"); }
#line 1882 "compilador.tab.c"
    break;

  case 121: /* termos: OR termo  */
#line 558 "compilador.y"
              { geraCodigo (NULL, "DISJ"); }
#line 1888 "compilador.tab.c"
    break;

  case 122: /* termo: termo MULTIPLICA fator  */
#line 564 "compilador.y"
   { 
      resolveTipoP1P2toP1(&pilha_T,&pilha_F);
      geraCodigo (NULL, "MULT");
   }
#line 1897 "compilador.tab.c"
    break;

  case 123: /* termo: termo DIVIDE fator  */
#line 569 "compilador.y"
   { 
     
      resolveTipoP1P2toP1(&pilha_T,&pilha_F);
      geraCodigo (NULL, "DIVI");
   }
#line 1907 "compilador.tab.c"
    break;

  case 124: /* termo: termo AND fator  */
#line 575 "compilador.y"
   {
      resolveTipoP1P2toP1(&pilha_T,&pilha_F);
      geraCodigo (NULL, "CONJ");
   }
#line 1916 "compilador.tab.c"
    break;

  case 125: /* termo: fator  */
#line 579 "compilador.y"
           {
      pilha_vs_type_push(&pilha_T, pilha_vs_type_pop(&pilha_F));
   }
#line 1924 "compilador.tab.c"
    break;

  case 127: /* fator: numero  */
#line 587 "compilador.y"
           { pilha_vs_type_push(&pilha_F, integer_type);}
#line 1930 "compilador.tab.c"
    break;

  case 128: /* fator: vlr_booleano  */
#line 588 "compilador.y"
                 { pilha_vs_type_push(&pilha_F, bool_type);}
#line 1936 "compilador.tab.c"
    break;

  case 129: /* fator: ABRE_PARENTESES expressao FECHA_PARENTESES  */
#line 591 "compilador.y"
   {
      // pilha_vs_type_push(&pilha_T, pilha_vs_type_pop(&pilha_F));
      pilha_vs_type_push(&pilha_F, pilha_vs_type_pop(&pilha_T));
   }
#line 1945 "compilador.tab.c"
    break;

  case 130: /* fator: NOT fator  */
#line 595 "compilador.y"
              { geraCodigo(NULL, "NEGA");}
#line 1951 "compilador.tab.c"
    break;

  case 131: /* $@21: %empty  */
#line 601 "compilador.y"
   {
      carrega_identidade_ou_aloca_mem_para_funcao(&ts, token, l_elem, num_vars, &pilha_F, &p_Funcoes);
   }
#line 1959 "compilador.tab.c"
    break;

  case 133: /* chamada_subrotina_func_args: ABRE_PARENTESES lista_de_expressoes_sr FECHA_PARENTESES  */
#line 612 "compilador.y"
   {
      //Se IDENT for função faz os procedimentos abaixo 
      // Vai dar ruin se funcao for sem argumentos, pois dou push, mas nunca pop - TODO só dar push se função tiver argumentos.
      // Se não tiver não importa o membro como left dela.
      // Como estourar o erro de too few arguments ? TODO - contar variaveis antes de Chamar  
      // Em atribuicao o tipo é visto depois de calcular a função
      chamada_desvio_funcao(&ts, &p_Funcoes, p_Funcoes.pilha[p_Funcoes.topo].num_p, nv_lex, &pilha_F, &pilha_T);
      pilha_vs_type_push(&pilha_F, ts.pilha[p_Funcoes.pilha[p_Funcoes.topo].indx_fun].tipo);
      pilha_inf_fun_pop(&p_Funcoes);
   }
#line 1974 "compilador.tab.c"
    break;

  case 135: /* numero: NUMERO  */
#line 634 "compilador.y"
   {
      geraCodigoParams(NULL, "CRCT ", token);
   }
#line 1982 "compilador.tab.c"
    break;

  case 136: /* vlr_booleano: T_TRUE  */
#line 641 "compilador.y"
          {geraCodigo1ParamNum(NULL, "CRCT ", 1);}
#line 1988 "compilador.tab.c"
    break;

  case 137: /* vlr_booleano: T_FALSE  */
#line 642 "compilador.y"
            {geraCodigo1ParamNum(NULL, "CRCT ", 0);}
#line 1994 "compilador.tab.c"
    break;


#line 1998 "compilador.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 645 "compilador.y"


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
   l_elem = DESCONHECIDO;
   // operacao = -1;
   // vs_tipo = desc_type;
   pilha_string_reset(&p_rotulos);

   pilha_vs_type_reset(&pilha_E);
   pilha_vs_type_reset(&pilha_T);
   pilha_vs_type_reset(&pilha_F);
   pilha_inf_fun_reset(&p_Funcoes);

   yyin = fp;

   if(yyparse()!=0){
      fprintf(stderr, "Nao consegui montar arvore de derivação.\n");
      fprintf(stderr, "Erro (%d,%d): Token \"%s\" não esperado.\n",nl, nc, token);
   }

   return 0;
}

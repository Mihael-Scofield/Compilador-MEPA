# Aula 3 - Analisador Sintático. 

1. Analisador Sintático (PARSING) - Verifica se uma sentença faz parte de uma gramática - Cria á árvore de derivação com os tokens. Ou seja, verifica a gramática está correta. Exemplo, " a := 10; " a instrução é composto por uma variável "a" recebe um valor "10". Ou ainda, uma instrução pode ser composto por um token identificador, "a", o token ":=" que significa recebe, e um valor númerico. Relação, se conseguir criar a árvore de derivação 2->3.
Analisador Sintático: Indentifica estruturas de regras como:
         <regra while> ::= <expressão> DO <comandos>

2. A gramática não deve ser ambigua só existe uma árvore de derivação possível.
3. Partes do arquivo bison, ".y".
   1. Definição. Novamente código que será copiado integramente o que inclui headers, mas também fecha o Hook do arquivo ".l". O que estiver como return no ".l" tem que ter um "%token" no BISON.
   2. Regras: Códifica a gramática.
   3. Subrotinas. Deve conter o Main e outras subrotinas.
     
4. Tarefa: Complementatar Posfixo, arquivo original Posfixo arquivo alterado PosfixoPlus.
TODO: Feito semestre passado. Não foi Revisado. Era para entender como funciona alizador léxico e passar de infixo para pós fixo usando uma pilha. 
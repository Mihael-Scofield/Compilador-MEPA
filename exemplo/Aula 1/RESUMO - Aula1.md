# Aula 1 - Apresentação da Disciplina. 

1. Resumo da Matéria. 
   1. O que é um compilador.
   2. De que partes é composto. 
   3. Ferramentas para reconhecimento de algumas classes de linguagens.
   
2. Que tipo de linguagens o Compilador Reconhece. 
   1. Problematização: Não é todos os tipos de linguagem que o compilador reconhece ?! R.: Não.
   2. Hierarquia de Chomsky.
      Do mais abrangente para o Menos : 
      1. (tipo 0) - Linguagens Recursivamente Enumeráveis.
      2. (tipo 1) - Linguagens Sensiveis ao Contexto.
      3. (tipo 2) - Linguagens Livres de Contexto. 
      4. Linguagens Livres de Contexto Determinísticas.
      5. (tipo 3) - Linguagens Regulares. 
   Explicação:
      tipo 2 - são autonomos a pilha.
      tipo 0 - praticamente todos os "programas" de computadores possíveis de serem criados.

   Importante para a disciplina são as Linguagens Livres de Contexto Determinísticas.
   São um subconjunto das Linguagens Livres de Contexto, onde não se existe ambiguidade.
   Portanto, são ditas Determinísticas.

3. Partes de um compilador:
   1. Arquivo de Entrada - fornece caracteres de entrada. (Relação 1->2)
   2. Analisador Léxico - Tokenizer. Transforma os caracteres de entrada em tokes. (No trabalho as regras do arquivo extensão .l) (Relação 2<->3)
   3. Analisador Sintático - Cria á árvore de derivação com os tokens. Ou seja, verifica a gramática está correta. Exemplo, " a := 10; " a instrução é composto por uma variável "a" recebe um valor "10". Ou ainda, uma instrução pode ser composto por um token identificador, "a", o token ":=" que significa recebe, e um valor númerico. Relação, se conseguir criar a árvore de derivação 2->3.
   4. Analisador Semântico - Verifica se faz sentido. Exemplo: "a:=a>10" isso está sintáticamente correto. Uma variável recebe uma operação lógica. No entanto, como "a" ou é inteiro ou é "booleano' a expressão está semânticamente errada. 
   5. Gerador de Código: Transforma os tokens e regras em código.
   6. Arquivo de Saída.
   
4. Detalhamento (Exemplificando)
   1. Analisador Léxico: Divide a entrada em pedaçõs significativos, chamados Tokens. Exemplo: "begin", "while", "," e etc.
   2. Analisador Sintático: Indentifica estruturas de regras como:
         <regra while> ::= <expressão> DO <comandos>
   3. Analisador Semântico: Identifica algumas coisas que não são identificadas pelo analisador sintático. Como, por exemplo, consistência de tipos.   

5. Organização da Disciplina
   1. (Primeira Parte) - Criar Compilador de um subconjunto Linguagem Pascal. Linguagem alvo (MEPA).
   2. (Segunda Parte) - Descendente (LL) e Ascendente (LR).
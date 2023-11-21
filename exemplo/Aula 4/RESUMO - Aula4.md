# Aula 4 - MEPA e program. 

1. MEPA vai ser a linguagem alvo e foi fornecido o interpretador/Simulador MEPA. O interpretador só serve para ver o que os comandos MEPA estão efetivamente fazendo. Sendo assim, ajuda a entender se o programa foi compilado corretamente.
   Quando estamos fazendo o compilador pensamos: 
   PASCAL -> O que o programa efetivamente fez -> Programa equivalente em MEPA.
   Com o interpretador temos:
   Programa MEPA -> O que o programa efetivamente faz.

   Teoricamente podiamos ter certeza só de Pascal para MEPA, mas pode ser útil. Exemplo se fizermos um programa que calcula fatorial de 5. Podemos fazer em pascal, compilar para MEPA e quando simular efetivamente ver o 120 (5!) em memória. 

2. Foi resaltado que o Tomaz tem notação Top-down. Porém, Bison é botton-up. Ou seja, quando o Tomaz apresentar algo do tipo "A::=B{a}" em Bison será "A::Aa|B". Usamos "OUs", ao invés, de "0 à n" ou "1 à n".
    
3. Trecho da Aula.
   1. Em Pascal:
         program exemplo1 (input, output);
         var m,n :  integer;
         begin    
         end.
   2. Gramática Tomaz:
         <program> ::= 
            program <indentificador> (<lista de indentificadores>);
               <bloco>.
         <bloco> ::=
            [<parte de declaração de rótulos>]
            [<parte de definição de tipos>]
            [<parte de declaração de variáveis>]
            [<parte de declaração de sub-rotinas>]
            <comando composto>
         <comando composto> ::=
            begin <comando>{;<comando>} end 
      * Para atividade inicialmente podemos inferir a possibilidade de <comando>::= {}.
   3. Significado:
      Inicia programa.
      Finaliza programa.
   4. Instruções MEPA:
      INPP
      PARA
   5. Ação:
      1. INPP
         s:=-1;
         D[0]:=0;
         i=i+1
      2. PARA
         {}

# Rodando os testes de erro com: 
   ./compilador Testes/testeX.pas >out 2>err.out

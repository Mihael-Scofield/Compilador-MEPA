# Aula 5 - Variáveis e MEPA. 

1. Antigamente as variáveis eram associados a um lugar da memória, ou seja, endereços fixos.
   No entanto, linguagens atuais suportam recurssão e esse método não funcionaria.

2. A Mepa utiliza escopo das variáveis. Ideia, colocar o nível léxico como parte do endereço da várivel.
   Além disso, aloca espaço na entrada e retira na saída dos procedimentos.

-
|a (0,0)
|-
||a(1,0)
||
||
||
||
|-
|
|-
||a(1,0)
||
||-
|||a(2,0)
|||b(2,1)
|||
|||
|||
||-
||
||
||
|-
|
|

3. Para identificar os identificadores temos que usar tabela de Simbolos. Sugerido Pilha. Contendo pelo menos 3 funções: Insere(indentificador, atributos), Busca(Indentificador), Retira(n);
4. Existem vários tipos de identificadores que ficaram na tabela de simbolos. Tomaz cap.10:
Variáveis Simples, Procedimento, Função, Parâmetro formal, Rótulo. 
5. Inicialmente um simbolo deve ser composto por 
   1. "Identificador",
   2. "Categoria",
   3. "Endereço(
      1. nível Léxico,
      2. Endereço Relativo - Tomaz chama de deslocamento
   1. "Tipo".

TODO - Tabela de Símbolo. - Talvez refatorar mais tarde.
   1. Inseririr - OK!
   2. Remover - Parcialmente VS. 
   3. Busca - TODO!
   
TODO - Tipo Simbolo. - OK! Talvez refatorar mais tarde.
   1. Tomaz Apresenta 3 Categorias de Simbolo Fig 10.3 pg 164:
      1. Variável Simples.
      2. Parâmetro Formal.
      3. Procedimento.
   2. Entre eles as propiredade: identificador, categoria e nível está sempre presente.


Questão ? Usar uma assinatura genérica para todas as categorias e fazer a pilha como lista, ou como ponteiros. Ou usar um tipo símbolo que cubra todos os tipos? Na hora que agente começa a preencher a tabela de simbolos no identificador já sabemos que categoria ele vai ser.


Adicionar:
TODO - AMEM - ok! - Na aula 6, vou melhorar para receber multiplos AMEMs em um só.
                     Multiplas listas de identidades.
TODO - DMEM - ok!
TODO - CRCT - ok!
TODO - CRVL - ok!
TODO - ARMZ - ok!
TODO - SOMA - ok! - As operações estão funcionando, mas não respeitam ordem de prescedência. 


Teste4 parou de funcionar quando coloquei comandos. O compilador não gosta de blocos vazios. No livro do Tomaz tá assim também. Perguntar ?


teste 5:
   program varsGlobais (input, output);
   var a,b: integer;
   begin
      a:=0;
      b:= a +10;    
   end.
Traduzindo para:
   INPP
   AMEM 2
   CRCT 0
   ARMZ 0,0
   CRVL 0,0
   CRCT 10
   SOMA 
   ARMZ 0,1
   DMEM 2
   PARA

teste 6:
   program varsGlobais (input, output);
   var a,b: integer;
   begin
      c:=0;
      b:= a +10;    
   end.
Dando o erro: 
   Erro léxico (4,2):Simbolos/Variável "c" não identificada no contexto.


# Aula 12 - Chamadas de Procedimento: Parâmetros passados por Referência

1. Para variavéis passados por referência precisa:
   1. CREN - Carrega endereço.             -ok!
   2. CRVI - Carrega valor indiretamente.  -ok!
   3. ARMI - Armazena valor indiretamente. -ok!

Nota: Testes exaustivos ainda não foram feitos. 
   Porém, o teste do professor aparentemente funciona bem.
   Estou usando o elemento da esquerda (left element - l_elem) para guardar elementos da esquerda em atribuição.
   Porém, também para guardar o identificador de um procedimento na lista de fatores.
   A principio isso poderia ser ruim se eu tivesse procedimentos do lado esquerdo de uma atribuição. Porém, 
   procedimentos não tem retorno. Logo, imagino que isso seja o desafio para a próxima aula, junto com o fato de poder colocar funções dentro de chamada de outras funções. Dessa maneira, provavelmente será necessário uma pilha de com identificadores das funções. 

Teste procedimento em uma atribuição teste 16 e 17; -ok!
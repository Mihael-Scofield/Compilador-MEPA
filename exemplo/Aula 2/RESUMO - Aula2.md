# Aula 2 - Analisador Léxico. 

1.  Analisador Léxico: Divide a entrada em pedaçõs significativos, chamados Tokens. Exemplo: "begin", "while", "," e etc. É programavel através de por meio de autonomo finito. Pode ser visto como a assinatura Analex(**token, **simbolo). Ou seja, mapeia a sequência de caracteres, representação do token, no simbolo que efetivamente é usado, token. De maneira passiva, ou seja, sequêncial. 
2.  Usaremos o Flex. Que a partir de um arquivo ".l" com algumas regras ele gera o autonomo, ou seja, o analisador léxico efetivamente.
3.  Partes do arquivo flex, ".l".
    1.  Definições: O que estiver ente "%{" e "%}" será copiado integralmente no arquivo ".yy.c", ou seja, para adicionar regras e cabeçalhos. Aleḿ disso, cria regras de identificador, ou seja, regras mais gerais sobre sequencias de caracteres ou combinações de números como Ex: "numero [0-9]+", ou seja, numero é um sequencia de caracteres com pelo menos um caractere de 0 a 9 em sequência. Essa definição não contempla float. 
    2.  Regras: Faz o mapeamento de definições "gerais" e sequencias mais explicitas com os simbolos, tokens. Além disso, faz o hook para as os estados/execussões (Análisador Sintárico). Importante identifica as expressões na ordem, ou seja, escolhe o primeiro match. A ordem das expressões importa. 
    3.  Subrotinas: Trecho de código que pode ser usado em várias regras.(Sem exemplos)
   
4. Tarefa: Consultar Apêndice 1 e acrescentar tokens válidos (em negrito) PASCAL.
   1. Coloquei o arquivo compilador.l e compilador.h nessa pasta.
   2. A atividade era sobre o léxico. Logo, somente MAP entre token e simbolo é importante.
   3. Provavelmente serão acrescentados mais durante o desenvolvimento do compilador.

# Tokens dados:
program
var     
begin 
end 
:= 
; 
: 
, 
.
( 
) 

# Tokens Adicionados:
label - ok!
type - ok!
array - ok! 
of - ok!
procedure - ok!
function - ok!
if - ok!
then - ok!
else - ok!
goto - ok!
while - ok!
\+ \- or - ok!
\* div and ok!
número - estamos fazendo diferente. Thomas usa digito.
integer - Não está em negrito, mas acredito que possa ser um token; Junto com outros tipos.  
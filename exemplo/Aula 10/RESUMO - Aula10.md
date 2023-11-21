# Aula 10 - Chamadas de Procedimento Sem Parâmetros, Com Variáveis Locais.

1. Fazer chamada de procedimentos. (ALL ok!)
   1. ENPR - Configura registro de ativação
   2. RTPR - Retorna o Fluxo
   3. CHPR - Chama procedimento
   4. Regra sintática de chamada de procedimento. 
   5. Manipulação da tabela de simbolos.
   6. inclusão de rótulos para procedimentos. 
   


PERGUNTA RETÓRICA: Nem todos os procedures tem que terminar com Rótulo R00: NADA. Só o último procedure, ou seja, o begin do bloco principal. Ou seja, o begin da main que deve começar com rótulo R00: NADA. Certo ? Dá mesma maneira só o primeiro procedure/função deve começar com desvia sempre R00 (DSVS R00), certo? Ou utilizamos vários rótulos e vamos sempre para o fim do procedure e enquanto for procedure vai redirecionar para o fim do mesmo ?

Utilizar vários rótulos é mais fácil e professor não tem preferência. 
 

Bloco tem muitos ous ao invés de vazer todas as combinações possemos fazer cada um daqueles procedimentos ser vazios ? 

Esqueci de perguntar. 


Último comando de um bloco pode ser sem ponto_e_virgula ?
Pode aceitar os dois, mas na realidade o último comando é sem ponto e vírgula. 


O professor pontua o cuidado de que comando sem rótulo com: atributo| chamada de procedimento pode dar errado. 

E, propoe refatorar colocando. Comando sem rótulo: IDENT atributo_ou_chamada_de_procedimento. 
Tava no video, mas ansioso para programar não vi e ele me indicou o mesmo. 


Último commit foi lembrado de tirar o procedimentos internos do nível léxico. 
 
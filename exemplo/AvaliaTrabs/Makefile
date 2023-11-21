 # -------------------------------------------------------------------
 #            Arquivo: Makefile
 # -------------------------------------------------------------------
 #              Autor: Bruno Müller Junior
 #               Data: 08/2007
 #      Atualizado em: [09/08/2020, 19h:01m]
 #		Modificado: Vinícius G. Garcia.
 # -------------------------------------------------------------------

$DEPURA=1

all: compilador clean

compilador: lex.yy.c compilador.tab.c compilador.o compilador.h ts.o io.o
	@echo "Iniciando"
	@igcc lex.yy.c compilador.tab.c compilador.o ts.o io.o -o compilador -ll -ly -lc

lex.yy.c: compilador.l compilador.h ts.h io.h
	@flex compilador.l

compilador.tab.c: compilador.y compilador.h ts.h io.h
	@bison compilador.y -d -v

compilador.o : compilador.h compiladorF.c ts.h io.h
	@gcc -c compiladorF.c -o compilador.o

ts.o: ts.c ts.h
	@gcc -c ts.c

io.o: io.c io.h ts.h
	@gcc -c io.c

clean :
	@rm -f compilador.tab.* lex.yy.c compilador.output *.o
	@echo "Finalizando"

posfixo: posfixo.tab.c lex.yy.c posfixo.o posfixo.h
	gcc lex.yy.c posfixo.tab.c -o posfixo -ll -ly -lc

posfixo.tab.c: posfixo.y posfixo.h
	bison posfixo.y -d -v

lex.yy.c: posfixo.l posfixo.h
	flex posfixo.l


clean : 
	rm -f posfixo.tab.* lex.yy.c  *.o

all: testearvore testearvore2 testearvore3

testearvore: testearvore.o arvores.o misc.o
	gcc -o testearvore testearvore.o arvores.o misc.o

testearvore2: testearvore2.o arvores.o misc.o
	gcc -o testearvore2 testearvore2.o arvores.o misc.o

testearvore3: testearvore3.o arvores.o misc.o
	gcc -o testearvore3 testearvore3.o arvores.o misc.o

arvores.o: arvores.c arvores.h
	gcc -c arvores.c
	
misc.o: misc.c misc.h
	gcc -c arvores.c

testearvore.o: testearvore.c
	gcc -c testearvore.c
	
testearvore2.o: testearvore2.c
	gcc -c testearvore2.c
	
testearvore3.o: testearvore3.c
	gcc -c testearvore3.c

clean:
	@echo Limpando arquivos
	-@rm -f *.o *.gch *~

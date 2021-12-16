

prog1: functionsLab1.o main.o
	gcc functionsLab1.o main.o -o prog1

functionsLab1.o: functionsLab1.c functionsLab1.h
	gcc -g -c functionsLab1.c

main.o: main.c functionsLab1.h
	gcc -g -c main.c

clean:
	rm -f *.o prog1
CC=gcc
OBJS=arrays.o functionsLab2.o exe.o  prog.o
EXEC=lab2
DEBUG = -g
CFLAGS = -std=c99  -Wall -Werror $(DEBUG)

$(EXEC) : $(OBJS)
	$(CC) $(OBJS) -o $@


arrays.o: arrays.c arrays.h
exe.o: exe.c exe.h arrays.h functionsLab2.h
functionsLab2.o: functionsLab2.c functionsLab2.h arrays.h
prog.o: prog.c exe.h


clean: 
	rm -f $(EXEC) $(OBJS)
	

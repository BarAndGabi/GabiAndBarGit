CC=gcc
OBJS=arrays.o functions3.o exe.o  main.o
EXEC=lab3
DEBUG = -g
CFLAGS = -std=c99  -Wall -Werror $(DEBUG)

$(EXEC) : $(OBJS)
	$(CC) $(OBJS) -o $@


arrays.o: arrays.c arrays.h
functions3.o: functions3.c functions3.h
exe.o: exe.c arrays.h functions3.h exe.h
main.o: main.c exe.h

clean: 
	rm -f $(EXEC) $(OBJS)
	

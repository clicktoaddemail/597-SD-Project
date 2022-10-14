CC=gcc
CFLAGS=-g -Wall
LIBS=-lpthread

default: progRAM

progRAM: main.o modulate.o
	$(CC) $(CFLAGS) -o progRAM main.o modulate.o $(LIBS)

modulate.o: modulate.c modulate.h
	$(CC) $(CFLAGS) -c modulate.c

main.o: main.c modulate.h
	$(CC) $(CFLAGS) -c main.c

clean:
	rm progRAM *.o

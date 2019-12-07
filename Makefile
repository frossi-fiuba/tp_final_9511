PROGRAM=main
CC=gcc
CDFLAGS=-Wall -std=c99 -pedantic -g
LDFLAGS=-lm

all:$(PROGRAM)

$(PROGRAM): main.o status.o diccionario.o operaciones.o micro.o direccionamiento.o
	$(CC) $(CDFLAGS) $(LDFLAGS) main.o status.o diccionario.o operaciones.o micro.o direccionamiento.o -o $(PROGRAM)

main.o: main.c micro.h
	$(CC) $(CFLAGS) -c main.c
status.o: status.c status.h
	$(CC) $(CFLAGS) -c status.c
diccionario.o: diccionario.c diccionario.h operaciones.h direccionamiento.h micro.h
	$(CC) $(CFLAGS) -c diccionario.c
operaciones.o: operaciones.c operaciones.h micro.h status.h
	$(CC) $(CFLAGS) -c operaciones.c
micro.o: micro.c micro.h operaciones.h direccionamiento.h
	$(CC) $(CFLAGS) -c micro.c
clean:
	rm -vf *.o $(PROGRAM)
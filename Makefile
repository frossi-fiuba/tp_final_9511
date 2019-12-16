PROGRAM=main
CC=gcc
CDFLAGS=-Wall -std=c99 -pedantic -g
LDFLAGS=-lm

all:$(PROGRAM)

$(PROGRAM): main.o status.o diccionario.o operaciones.o micro.o direccionamiento.o
	$(CC) $(CDFLAGS) $(LDFLAGS) main.o status.o diccionario.o operaciones.o micro.o direccionamiento.o -o $(PROGRAM)

main.o: main.c micro.h
	$(CC) $(CDFLAGS) -c main.c
status.o: status.c status.h
	$(CC) $(CDFLAGS) -c status.c
diccionario.o: diccionario.c diccionario.h operaciones.h direccionamiento.h micro.h
	$(CC) $(CDFLAGS) -c diccionario.c
direccionamiento.o: direccionamiento.c direccionamiento.h micro.h
	$(CC) $(CDFLAGS) -c direccionamiento.c
operaciones.o: operaciones.c operaciones.h micro.h status.h
	$(CC) $(CDFLAGS) -c operaciones.c
micro.o: micro.c micro.h operaciones.h direccionamiento.h
	$(CC) $(CDFLAGS) -c micro.c
clean:
	rm -vf *.o $(PROGRAM)
	
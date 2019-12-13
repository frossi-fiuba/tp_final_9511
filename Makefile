PROGRAM=main_2
CC=gcc
CDFLAGS=-Wall -std=c99 -pedantic -g
LDFLAGS=-lm

all:$(PROGRAM)

$(PROGRAM): main_2.o status.o diccionario_2.o operaciones.o micro.o direccionamiento.o
	$(CC) $(CDFLAGS) $(LDFLAGS) main_2.o status.o diccionario_2.o operaciones.o micro.o direccionamiento.o -o $(PROGRAM)

main_2.o: main_2.c micro.h
	$(CC) $(CDFLAGS) -c main_2.c
status.o: status.c status.h
	$(CC) $(CDFLAGS) -c status.c
diccionario_2.o: diccionario_2.c diccionario_2.h operaciones.h direccionamiento.h micro.h
	$(CC) $(CDFLAGS) -c diccionario_2.c
direccionamiento.o: direccionamiento.c direccionamiento.h micro.h
	$(CC) $(CDFLAGS) -c direccionamiento.c
operaciones.o: operaciones.c operaciones.h micro.h status.h
	$(CC) $(CDFLAGS) -c operaciones.c
micro.o: micro.c micro.h operaciones.h direccionamiento.h
	$(CC) $(CDFLAGS) -c micro.c
clean:
	rm -vf *.o $(PROGRAM)
	
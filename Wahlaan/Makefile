# Make - Compila todo
# Make clean - Borra los archivos que se generaron
#La variable BINARY es el nombre del ejecutable

OBJS = \
  Bipartito.o\
	DimacsRead.o\
	GrafoConstruccion.o\
	GrafoInformacion.o\
	Greedy.o\
	main.o\
  Ordenes.o\

BINARY = main
CFLAGS = -g -Wall -O3 -std=c99

prgm: $(OBJS)
	$(CC) -o $(BINARY) $(OBJS)

%.o: %.c Rii.h
	$(CC) $(CFLAGS) -c $?

clean:
	@rm -f *.o $(BINARY) *.gch

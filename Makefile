CFLAGS = -Wall -Wextra -O2
CC = gcc

rastros: main.o dados.o interface.o logica.o
	$(CC) $(CFLAGS) -o rastros main.o dados.o interface.o logica.o

clean:
	@rm *.o
	@rm rastros


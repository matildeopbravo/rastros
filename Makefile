CFLAGS = -Wall -Wextra -pedantic-errors -O
CC = gcc

ex: src/main.o src/dados.o src/interface.o src/logica.o src/listas.o
	$(CC) $(CFLAGS) -o src/rastros $^ 

run: ex
	src/rastros

clean:
	@rm -f src/*.o
	@rm -f src/rastros


CFLAGS = -std=gnu11 -Wall -Wextra -pedantic-errors -O
CC = gcc

ex: projeto/main.o projeto/dados.o projeto/interface.o projeto/logica.o projeto/listas.o
	$(CC) $(CFLAGS) -o projeto/rastros $^ 

run: ex
	projeto/rastros

clean:
	@rm -rf projeto/*.o projeto/rastros bot/bot bot/*.o 


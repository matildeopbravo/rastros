CFLAGS = -Wall -Wextra -pedantic-errors -O
CC = gcc

ex: src/main.o src/dados.o src/interface.o src/logica.o src/listas.o
	$(CC) $(CFLAGS) -o src/rastros $^ 

run: ex
	src/rastros
all : ex src/bot-main.o src/bot.o 
	$(CC) $(CFLAGS) -o src/bot src/bot-main.o src/bot.o src/logica.o src/interface.o src/dados.o src/listas.o
   

clean:
	@rm -f src/*.o
	@rm -f src/rastros


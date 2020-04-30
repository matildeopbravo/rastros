CFLAGS = -Wall -Wextra -pedantic-errors -O
CC = gcc

ex: src/main.o src/dados.o src/interface.o src/logica.o src/listas.o
	$(CC) $(CFLAGS) -o src/rastros $^ 

run: ex
	src/rastros
all : ex src/bot/bot-main.o src/bot/bot.o 
	$(CC) $(CFLAGS) -o src/bot/bot src/bot/bot-main.o src/bot/bot.o src/logica.o src/interface.o src/dados.o src/listas.o
   

clean:
	@rm -rf src/bot/*.o src/*.o src/rastros src/bot/bot


CFLAGS = -Wall -Wextra -pedantic-errors -O
CC = gcc

ex: projeto/main.o projeto/dados.o projeto/interface.o projeto/logica.o projeto/listas.o
	$(CC) $(CFLAGS) -o projeto/rastros $^ 

run: ex
	projeto/rastros

all: ex bot/bot-main.o bot/bot.o 
	$(CC) $(CFLAGS) -o bot/bot bot/bot-main.o bot/bot.o projeto/logica.o projeto/interface.o projeto/dados.o projeto/listas.o
   

clean:
	@rm -rf projeto/*.o projeto/rastros bot/bot bot/*.o 


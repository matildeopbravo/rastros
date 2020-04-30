CFLAGS = -Wall -Wextra -pedantic-errors -O
CC = gcc

ex: bot-main.o bot.o logica.o interface.o dados.o
	$(CC) $(CFLAGS) -o bot bot-main.o bot.o logica.o interface.o dados.o listas.o

run: ex
	bot

clean:
	@rm -f *.o
	@rm -f bot

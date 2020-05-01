CFLAGS = -Wall -Wextra -pedantic-errors -O
CC = gcc

bot: bot.o bot-main.o logica.o interface.o dados.o listas.o
	$(CC) $(CFLAGS) -o bot $^
   

clean:
	@rm -rf *.o bot 


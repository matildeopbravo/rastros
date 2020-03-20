CFLAGS = -Wall -Wextra -O2
CC = gcc

run: ex
	 src/rastros

ex: src/main.o src/dados.o src/interface.o src/logica.o
	$(CC) $(CFLAGS) -o src/rastros src/main.o src/dados.o src/interface.o src/logica.o

clean:
	@rm -f src/*.o
	@rm -f src/rastros

       	#o -f faz com que a instrucao nunca dê erro e por isso execute sempre a primeira. o @ não dá print da instrucao executada

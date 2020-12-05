CC=gcc
INCLUDES=./includes
SOURCES=./sources
BINARY=./main
PROG=./main.c
FLAGS=-Wall -Werror -g
OBJFILES = list.o site.o utils.o

all: list.o site.o utils.o
	@$(CC) $(PROG) $(OBJFILES) -I $(INCLUDES) -o $(BINARY) $(FLAGS)

list.o:
	@$(CC) -c $(SOURCES)/list.c -I $(INCLUDES)

site.o:
	@$(CC) -c $(SOURCES)/site.c -I $(INCLUDES)

utils.o:
	@$(CC) -c $(SOURCES)/utils.c -I $(INCLUDES)

valgrind:
	@valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all $(BINARY)

run:
	@$(BINARY)

clean: 
	@rm -r *.o 

zip:
	zip -r Project_1.zip Makefile ./includes/ ./sources/ ./main.c ./googlebot.txt
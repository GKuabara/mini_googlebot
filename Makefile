CC=gcc
INCLUDES=./includes
SOURCES=./sources
BINARY=./main
PROG=./main.c
FLAGS=-Wall -Werror -g
OBJFILES = AVLtree.o site.o utils.o trie.o

all: AVLtree.o site.o utils.o trie.o
	@$(CC) $(PROG) $(OBJFILES) -I $(INCLUDES) -o $(BINARY) $(FLAGS)

AVLtree.o:
	@$(CC) -c $(SOURCES)/AVLtree.c -I $(INCLUDES)

site.o:
	@$(CC) -c $(SOURCES)/site.c -I $(INCLUDES)

utils.o:
	@$(CC) -c $(SOURCES)/utils.c -I $(INCLUDES)

trie.o:
	@$(CC) -c $(SOURCES)/trie.c -I $(INCLUDES)

valgrind:
	@valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all $(BINARY)

run:
	@$(BINARY)

clean: 
	@rm -r *.o 

zip:
	zip -r MiniGooglebot2.zip Makefile ./includes/ ./sources/ ./main.c ./googlebot.txt ./README.md
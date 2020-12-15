CC = gcc
INCLUDES = ./includes
SOURCES = ./sources
BINARY = main
PROG = main.c
FLAGS = -Wall -Werror -g -o

all:
	@$(CC) $(PROG) $(SOURCES)/* $(FLAGS) $(BINARY) -I $(INCLUDES)

valgrind:
	@valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all $(BINARY)

run:
	@./$(BINARY)

clean: 
	@rm -r $(BINARY)

zip:
	zip -r MiniGooglebot2.zip Makefile ./includes/ ./sources/ ./main.c ./googlebot.txt ./README.md
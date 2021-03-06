#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utils.h"
#include "trie.h"

struct letter_{
	LETTER *sub[alphabetSize];
	boolean end;
};

struct trie_{
	LETTER *root;
};

TRIE *trie_create(){
	TRIE *db = malloc(sizeof(TRIE));
	db->root = trie_node_create();

	return db;
}

LETTER *trie_node_create(){
	LETTER *node = malloc(sizeof(LETTER));
	for(int i = 0; i < alphabetSize; i++) node->sub[i] = NULL;
	node->end = 0;
	return node;
}

void trie_free_nodes(LETTER *node){
	
	// verifies if the node exists, then call it recursively until reaches a leaf
	for(int i = 0; i < alphabetSize; i++){
		if(node->sub[i]) trie_free_nodes(node->sub[i]);
		else continue;
	}
	free(node);
}

void trie_destroy(TRIE *db){
	if(!db || !db->root) return;
	trie_free_nodes(db->root);
	free(db);
}

boolean trie_insert_word(TRIE *db, char *str){
	if(!db || !str) return FALSE;

	LETTER *actual = db->root;

	// get each letter of the string going through the tree
	for(int i = 0; str[i] != '\0'; i++){
		int index = char_to_int(tolower(str[i]));

		// if the letter doesn't exists, then create it
		if(!actual->sub[index]){
			actual->sub[index] = trie_node_create();
		}
		actual = actual->sub[index];
	}

	actual->end = TRUE;
	return TRUE;
}

boolean trie_search_word(TRIE *db, char *str){
	if(!db || !str) return FALSE;

	LETTER *actual = db->root;

	for(int i = 0; str[i] != '\0'; i++){
		// gets the position of the letter in the array
		int index = char_to_int(tolower(str[i]));

		// if the letter exist in the array of nodes, then keep going
		if(actual->sub[index]) actual = actual->sub[index];
		else return FALSE; 
	}

	if(actual->end == FALSE) return FALSE;
	return TRUE;
}
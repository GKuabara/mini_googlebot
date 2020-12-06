#ifndef TRIE_H
#define TRIE_H

#define TRUE 1
#define FALSE 0    
#define boolean int
#define alphabetSize 26

typedef struct node_ NODE;
typedef struct trie_ TRIE;

struct node_{
	NODE *sub[alphabetSize];
	char key;
	boolean end;
};

struct trie_{
	NODE *root;
};

TRIE *trie_create();
NODE *trie_node_create();

void trie_free_nodes(NODE *node);
void trie_destroy(TRIE *db);

boolean trie_insert_word(TRIE *db, char *str);
boolean trie_search_word(TRIE *db, char *str);

#endif
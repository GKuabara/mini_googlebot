#ifndef TRIE_H
#define TRIE_H

#define TRUE 1
#define FALSE 0    
#define boolean int
#define alphabetSize 26

typedef struct letter_ LETTER;
typedef struct trie_ TRIE;

TRIE *trie_create();
LETTER *trie_node_create();

void trie_free_nodes(LETTER *node);
void trie_destroy(TRIE *db);

boolean trie_insert_word(TRIE *db, char *str);
boolean trie_search_word(TRIE *db, char *str);

#endif
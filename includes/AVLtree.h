#ifndef BINTREE_H
#define BINTREE_H

#include "trie.h"
#include "site.h"

#define boolean int
#define TRUE 1
#define FALSE 0

typedef struct node_ NODE;	
typedef struct bintree_ TREE;	

// creation and deletion	
TREE *tree_create();
NODE *node_create(SITE *site);
void free_nodes(NODE **node);
void tree_delete(TREE **tree);

boolean tree_empty(TREE *tree);

// height and number of nodes funcions
int search_tree_height(NODE *node);
int tree_height(TREE *tree);
int count_nodes(NODE *node);
int tree_totalnodes(TREE *tree);

// print funcions
void print(NODE *node);
void print_tree(TREE *tree);
void print2DUtil(NODE *root, int space);
void print2D(TREE* tree);

// balance funcions
int node_height(NODE *node);
int balance_factor(NODE *node);
int large(int x, int y);
NODE *smallest_node_key(NODE *node);

// rotations funcions
NODE *rotation_Left(NODE *node);
NODE *rotation_Right(NODE *node);
NODE *rotation_Left_Right(NODE *node);
NODE *rotation_Right_Left(NODE *node);

// insertion functions
NODE *search_node(NODE *node, int key);
NODE *insert(NODE *node, SITE *site);
void insert_node(TREE *tree, SITE *site);
NODE *insert_by_relevance(NODE *node, SITE *new_site);
void insert_node_by_relevance(TREE *tree, SITE *new_site);

// deletion node funtions
NODE *delete(NODE **node, int num);
void delete_node(TREE *tree, int key);


// update keywords and relevance
boolean tree_insert_keyword(TREE *tree, int key, char *keyword);
boolean tree_update_relevance(TREE *tree, int key, int relevance);

// search sites with a specific keyword
void build_sites_list(SITE ***sites, NODE *actual, char *str, int *count);
void search_and_sort_sites_with_keyword(TREE *tree, char *str);

// sites suggestions functions
TRIE *get_all_keywords_from_sites(SITE **sites, int count);
void search_sites_keywords_in_trie(SITE ***all_sites, NODE *actual, TRIE *all_keywords, int *nsites);
void sites_suggestions(TREE *tree, char *str);

#endif
#ifndef BINTREE_H
#define BINTREE_H

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

// node's insertion and deletion functions
NODE *search_node(NODE *node, int key);
NODE *insert(NODE *node, SITE *site);
void insert_node(TREE *tree, SITE *site);
NODE *delete(NODE **node, int num);
void delete_node(TREE *tree, int key);

// update keywords and relevance
boolean tree_insert_keyword(TREE *tree, int key, char *keyword);
boolean tree_update_relevance(TREE *tree, int key, int relevance);

SITE *list_get_site(TREE *tree, int key);

// sites from search by keyword
SITE **search_by_keyword(TREE *tree, char *str, int *count);
void search_and_sort_sites_with_keyword(TREE *tree, char *str);

// sites suggestions functions
char **search_and_collect_keyword_from_sites(TREE *tree, char *str, int *total_kw);
SITE **sites_with_suggested_keywords(TREE *tree, char **kw, int total_kw, int *n_sites);
SITE **search_for_largest_relevance(SITE **sites, int n_sites);
void sites_suggestions(TREE *tree, char *str);

#endif
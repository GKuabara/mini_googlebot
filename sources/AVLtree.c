#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AVLtree.h"
#include "site.h"
#include "utils.h"

struct node_{
	SITE *site;
	int height;
	NODE *left;
	NODE *right;
};

struct bintree_{
	NODE *root;
};

TREE *tree_create(){
	TREE *tree = malloc(sizeof(TREE));
	if(tree) tree->root = NULL;
	return tree;
}

NODE *node_create(SITE *site){
	NODE *node = malloc(sizeof(NODE));
	node->site = site;
	node->height = 1;
	node->left = NULL;
	node->right = NULL;

	return node;
}

void free_nodes(NODE **node){
	if(!(*node)) return;
	free_nodes(&(*node)->left);
	free_nodes(&(*node)->right);
	site_delete(&(*node)->site);
	free(*node);
	*node = NULL;
}

void tree_delete(TREE **tree){
	if(!(*tree)) return;
	free_nodes(&(*tree)->root);
	free(*tree);
	*tree = NULL;
}

boolean tree_empty(TREE *tree){
	if(!tree || !tree->root) return TRUE;
	return FALSE;
}

int search_tree_height(NODE *node){
	if(!node) return 0;

	int left_height = search_tree_height(node->left);
	int right_height = search_tree_height(node->right);

	return (left_height > right_height) ? left_height+1 : right_height+1;
}

int tree_height(TREE *tree){
	if(!tree) return FALSE;
	return search_tree_height(tree->root);
}

int count_nodes(NODE *node){
	if(!node) return 0;

	int left = count_nodes(node->left);
	int right = count_nodes(node->right);
	return left + right + 1;
}

int tree_totalnodes(TREE *tree){
	return count_nodes(tree->root);
}

void print(NODE *node){
	if(!node) return;
	// in-ordem
	print(node->left);
	site_print(node->site);
	print(node->right);
}
void print_tree(TREE *tree){
	print(tree->root);
}

void print2DUtil(NODE *node, int space) { 
    if (node == NULL) return; 
    // Increase distance between levels 
    space += 5; 
    // Process right child first 
    print2DUtil(node->right, space); 
  
    // Print current node after space count 
    printf("\n"); 
    for (int i = 5; i < space; i++) printf(" "); 
    printf("%d\n", site_get_key(node->site)); 
  
    // Process left child 
    print2DUtil(node->left, space); 
}

void print2D(TREE *tree) { 
   // Pass initial space count as 0 
   print2DUtil(tree->root, 0); 
}

int node_height(NODE *node){
	if(!node) return 0;
	return node->height;
}

int balance_factor(NODE *node){
	return node_height(node->left) - node_height(node->right);
}

int large(int x, int y){
	return (x > y) ? x : y;
}

NODE *smallest_node_key(NODE *node){
	NODE *actual = node;
	// finds the most left node, in other words, the minimiun key value
	while(actual->left) actual = actual->left;
	return actual;
}

NODE *rotation_Left(NODE *node){
	NODE *aux = node->right;
	node->right = aux->left;
	aux->left = node;

	node->height = large(node_height(node->left), node_height(node->right)) + 1;
	aux->height = large(node_height(aux->left), node_height(aux->right)) + 1;
	return aux;
}

NODE *rotation_Right(NODE *node){
	NODE *aux = node->left;
	node->left = aux->right;
	aux->right = node;

	node->height = 1 + large(node_height(node->left), node_height(node->right));
	aux->height = 1 + large(node_height(aux->left), node_height(aux->right));
	return aux;
}

NODE *rotation_Left_Right(NODE *node){
	node->left = rotation_Left(node->left);
	return rotation_Right(node);
}

NODE *rotation_Right_Left(NODE *node){
	node->right = rotation_Right(node->right);
	return rotation_Left(node);
}

NODE *search_node(NODE *node, int key){
	if(!node) return NULL;
	int temp = site_get_key(node->site);

	if(temp == key) return node;
	else if(temp < key) return search_node(node->left, key);
	else return search_node(node->right, key);
}

NODE *insert(NODE *node, SITE *new_site){
	// insert node
	if(!node) return node_create(new_site);

	// search for insertion
	int num = site_get_key(new_site);
	int key = site_get_key(node->site);
	if(num < key) node->left = insert(node->left, new_site);
	else if(num > key) node->right = insert(node->right, new_site);

	// returnin through the recursive calls, updating height, balance, and rotating if necessary
	node->height = 1 + large(node_height(node->left), node_height(node->right));

	int balance = balance_factor(node);
	if(balance > 1){
		int key = site_get_key(node->left->site);
		if(num < key) node = rotation_Right(node);
		else node = rotation_Left_Right(node);
	}
	if(balance < -1){
		int key = site_get_key(node->right->site);
		if(num > key) node = rotation_Left(node);
		else node = rotation_Right_Left(node);
	}

	return node;
}

void insert_node(TREE *tree, SITE *new_site){
	if(!tree){
		printf("No tree, sorry...\n");
		return;
	}
	tree->root = insert(tree->root, new_site);
}

NODE *delete(NODE **node, int num){
	if(*node == NULL) return *node;

	// pass through the tree recursively looking for the *node to delete
	int key = site_get_key((*node)->site);
	if(num < key) delete(&(*node)->left, num);
	else if(num > key) delete(&(*node)->right, num);
		
	// *node to delete found
	else{
		// *node has 2 subtrees case
		if((*node)->left && (*node)->right){

			// get smallest (*node) in the right subtree
			NODE *temp = smallest_node_key((*node)->right);

			// free (*node)->site, and copy temp->site to (*node)->site
			site_delete(&(*node)->site); 
			memcpy((*node)->site, temp->site, sizeof(SITE));
			//(*node)->site = site_copy(temp->site);

			// delete 'temp' (*node) that was copied
			(*node)->right = delete(&(*node)->right, site_get_key(temp->site));
		}
		// any or one subtree cases
		else{
			NODE *temp = *node;
			*node = ((*node)->left) ? (*node)->left : (*node)->right;
			site_delete(&temp->site);
			free(temp);
			temp = NULL;
		}

		// if there is any *node
		if(*node == NULL) return *node;

		// returning through the recursive calls, updating height, balance, and rotating if necessary
		(*node)->height = 1 + large(node_height((*node)->left), node_height((*node)->right));

		int balance = balance_factor(*node);
		if(balance > 1){
			if(balance_factor((*node)->left) > 0) *node = rotation_Right(*node);
			else *node = rotation_Left_Right(*node);
		}
		else if(balance < -1){
			if(balance_factor((*node)->right) < 0) *node = rotation_Left(*node);
			else *node = rotation_Right_Left(*node);
		}
	}
	return *node;
}

void delete_node(TREE *tree, int key){
	if(!tree){
		printf("No tree, sorry...\n");
		return;
	}
	tree->root = delete(&tree->root, key);
}

boolean tree_insert_keyword(TREE *tree, int key, char *keyword){
	if(tree_empty(tree)) return FALSE;

	// gets the first site with key equal or larger than the input key
	NODE *actual = search_node(tree->root, key);

	// if 'actual' key is equal as the input key, so insert keyword
	if(actual && site_get_key(actual->site) == key){
		//function to add a keyword in the site
		site_add_keyword(actual->site, keyword);
		printf("New keyword added\n");
		return TRUE;
	}

	// all nodes after 'actual' has key larger than the input key, so return FALSE
	printf("Sorry, but there is no site with this code\n");
	return FALSE;
}

boolean tree_update_relevance(TREE *tree, int key, int relevance){
	if(tree_empty(tree)) return FALSE;

	// gets the first site with key equal or larger than the input key
	NODE *actual = search_node(tree->root, key);

	// if 'actual' key is equal as the input key, so update relevance
	if(actual && site_get_key(actual->site) == key){
		//function to access site relevance content
		site_set_relevance(actual->site, relevance);
		printf("Revelance updated with success\n");
		return TRUE;
	}

	// all nodes after 'actual' has key larger than the input key, so return FALSE
	printf("Sorry, but there is no site with this code\n");
	return FALSE;
}

SITE **search_by_keyword(TREE *tree, char *str, int *count){
	// matrix to get all the sites with 'str'
	SITE **sites = NULL;

	NODE *actual = tree->root;
	while(actual){
		
		// verifies through all the sites of the tree has the keyword 'str' and add to to matrix
		if(compare_string_with_keywords(actual->site, str)){
			sites = (SITE **) realloc(sites, sizeof(SITE *) * (*count + 1));
			sites[(*count)++] = actual->site;
		}
		actual = actual->next;
	}

	return sites;
}

void search_and_sort_sites_with_keyword(TREE *tree, char *str){
	if(tree_empty(tree)) return;

	// funtion to look for sites with keyword 'str'
	int count = 0;
	SITE **sites = search_by_keyword(tree, str, &count);
	if(!sites){
		printf("Sorry, there are no sites with your keyword...\n");
		return;
	}

	// sort matrix 'sites'
	quick_sort(sites, 0, count - 1);

	printf("\nSo, these are the sites with keyword '%s':\n", str);
	for (int i = count - 1; i >= 0; i--)
		printf("%s - %s\n", site_get_name(sites[i]), site_get_URL(sites[i]));

	free(sites); sites = NULL;
}
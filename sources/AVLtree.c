#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AVLtree.h"
#include "site.h"
#include "utils.h"
#include "trie.h"

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

//__________________________________________________________________________________________________

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

//__________________________________________________________________________________________________

void print(NODE *node){
	if(!node) return;
	// in-ordem
	print(node->left);
	site_print(node->site);
	print(node->right);
}
void print_tree(TREE *tree){
	print(tree->root);
	printf("\n");
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

//__________________________________________________________________________________________________

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

//__________________________________________________________________________________________________

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

//__________________________________________________________________________________________________

NODE *search_node(NODE *node, int key){
	if(!node) return NULL;
	int temp = site_get_key(node->site);

	if(temp == key) return node;
	else if(temp > key) return search_node(node->left, key);
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

NODE *insert_by_relevance(NODE *node, SITE *new_site){
	// insert node
	if(!node) return node_create(new_site);

	// search for insertion
	int num = site_get_relevance(new_site);
	int key = site_get_relevance(node->site);
	if(num < key) node->left = insert_by_relevance(node->left, new_site);
	else if(num > key) node->right = insert_by_relevance(node->right, new_site);

	// returnin through the recursive calls, updating height, balance, and rotating if necessary
	node->height = 1 + large(node_height(node->left), node_height(node->right));

	int balance = balance_factor(node);
	if(balance > 1){
		int key = site_get_relevance(node->left->site);
		if(num < key) node = rotation_Right(node);
		else node = rotation_Left_Right(node);
	}
	if(balance < -1){
		int key = site_get_relevance(node->right->site);
		if(num > key) node = rotation_Left(node);
		else node = rotation_Right_Left(node);
	}

	return node;
}

void insert_node_by_relevance(TREE *tree, SITE *new_site){
	if(!tree){
		printf("No tree, sorry...\n");
		return;
	}
	tree->root = insert_by_relevance(tree->root, new_site);
}

//__________________________________________________________________________________________________

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
			(*node)->site = site_copy(temp->site);

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

//__________________________________________________________________________________________________

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

//__________________________________________________________________________________________________

void build_sites_list(SITE ***sites, NODE *actual, char *str, int *count){
	if(!actual) return;

	if(compare_string_with_keywords(actual->site, str)){
		*sites = realloc(*sites, sizeof(SITE *) * (*count + 1));
		(*sites)[(*count)++] = actual->site;
	}

	build_sites_list(sites, actual->left, str, count);
	build_sites_list(sites, actual->right, str, count);
}

void search_and_sort_sites_with_keyword(TREE *tree, char *str){
	if(tree_empty(tree)) return;

	// funtion to look for sites with keyword 'str'
	int count = 0;
	SITE **sites = NULL;
	build_sites_list(&sites, tree->root, str, &count);
	if(!sites){
		printf("Sorry, there are no sites with your keyword...\n");
		return;
	}

	// sort matrix 'sites'
	heap_sort(sites, count);

	printf("\nSo, these are the sites with keyword '%s':\n", str);
	for (int i = count - 1; i >= 0; i--)
		printf("%s - %s\n", site_get_name(sites[i]), site_get_URL(sites[i]));
	printf("\n");
	free(sites); sites = NULL;
}

//__________________________________________________________________________________________________

// gets all keywords from a sites' array into a TRIE tree
TRIE *get_all_keywords_from_sites(SITE **sites, int count){
	TRIE *all_keywords = trie_create();

	for(int i = 0; i < count; i++){
		int temp = site_get_nkeywords(sites[i]);

		for(int j = 0; j < temp; j++){
			char *aux = site_get_keywords(sites[i], j);
			trie_insert_word(all_keywords, aux);
		}
	}
	return all_keywords;
}

// search for sites in the data base that has at least one keyword in the TRIE
void search_sites_keywords_in_trie(SITE ***all_sites, NODE *actual, TRIE *all_keywords, int *nsites){
	if(!actual) return;

	int n_kw = site_get_nkeywords(actual->site); // how many keywords a site has
	
	// loop that pass through each site's keywords verifying if it exists in the TRIE
	// if exists, allocate more space in the SITE array
	for(int i = 0; i < n_kw; i++){
		char *temp = site_get_keywords(actual->site, i);
		
		if(trie_search_word(all_keywords, temp)){
			*all_sites = realloc(*all_sites, sizeof(SITE *) * (*nsites + 1));
			(*all_sites)[(*nsites)++] = actual->site;
			break;
		}
	}
	// recursive call to pass through all nodes of the AVL tree
	search_sites_keywords_in_trie(all_sites, actual->left, all_keywords, nsites);
	search_sites_keywords_in_trie(all_sites, actual->right, all_keywords, nsites);
}

void sites_suggestions(TREE *tree, char *str){
	if(tree_empty(tree)) return;

	// funtion to look for sites with keyword 'str'
	int count = 0;
	SITE **sites = NULL;
	build_sites_list(&sites, tree->root, str, &count);
	if(!sites){
		printf("Sorry, there are no sites with your keyword...\n");
		return;
	}

	// gets all keywords from our sites' array into a TRIE TREE
	TRIE *all_keywords = get_all_keywords_from_sites(sites, count);

	// search for sites that has at least one keyword in the TRIE, build another sites' array
	int nsites = 0;
	SITE **all_sites = NULL;
	search_sites_keywords_in_trie(&all_sites, tree->root, all_keywords, &nsites);

	// bubble sort for just 5 positions of the sites' array
	bubble_sort(all_sites, nsites);

	printf("\nSuggested sites for you, baby:\n");
	for(int i = 1; i <= 5; i++)
		printf("%s - %s\n", site_get_name(all_sites[nsites - i]), site_get_URL(all_sites[nsites - i]));

	free(sites);
	trie_destroy(all_keywords);
	free(all_sites);
}
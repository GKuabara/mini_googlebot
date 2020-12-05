#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "site.h"
#include "utils.h"

struct node_{
	SITE *site;
	NODE *next;
};

struct list_{
	NODE *start;
	int size;
};

LIST *list_create(){
	LIST *list = malloc(sizeof(LIST));
	if(!list) return FALSE;

	list->start = NULL;
	list->size = 0;
	return list;
}

NODE *search_site_through_key(LIST *list, int key){
	NODE *actual = list->start;

	// loop that get the first site with key equal or larger than the input key
	while(actual && site_get_key(actual->site) < key)
		actual = actual->next;

	// can return 3 cases: list->start, anynode, or NULL(no site with this key)
	return actual;
}

// ordered insertion using the key
boolean list_insert_site(LIST *list, SITE *newsite){
	//in case there is no list
	if(!list) return FALSE;

	NODE *elem = malloc(sizeof(NODE));
	//if the list is empty, put the site in the start
	if(list_empty(list)){
		elem->site = newsite;
		elem->next = NULL;
		list->start = elem;
		list->size = 1;
		return TRUE;
	}

	//if the list already has content, it needs to be added by order
	elem->site = newsite;
	NODE *prior = NULL, *actual = list->start;

	//gets the position to be alocated
	// while key is smaller than actual, keep going...
	while(actual && site_get_key(actual->site) < site_get_key(newsite)){
		prior = actual;
		actual = actual->next;	
	}

	// verifies if already has a site with this key
	if(actual && site_get_key(actual->site) == site_get_key(newsite)){
		site_delete(&newsite);
		printf("Sorry, but this site already exists\n");
		return FALSE;
	}
	
	// if is the first element
	if(actual == list->start){
		elem->next = list->start;
		list->start = elem;
	}
	// if is the last element
	else if(!actual){
		prior->next = elem;
		elem->next = NULL;
	}
	// inserts in the "middle" of the list
	else{
		elem->next = actual;
		prior->next = elem;
	}
	list->size++;
	return TRUE;
}

boolean list_remove_site(LIST *list, int key){
	if(list == NULL) return FALSE;

	// gets the first site with key equal or larger than the input key
	NODE *actual = search_site_through_key(list, key);

	// if 'actual' key is equal as the input key, so delete this site
	if(actual && site_get_key(actual->site) == key){
		site_delete(&actual->site);
		return TRUE;
	}

	// all nodes after 'actual' has key larger than the input key, so return FALSE
	printf("Sorry, but there is no site with this code\n");
	return FALSE;	
}

boolean list_insert_keyword(LIST *list, int key, char *keyword){
	if(list == NULL) return FALSE;

	// gets the first site with key equal or larger than the input key
	NODE *actual = search_site_through_key(list, key);

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

boolean list_update_relevance(LIST *list, int key, int relevance){
	if(list == NULL) return FALSE;

	// gets the first site with key equal or larger than the input key
	NODE *actual = search_site_through_key(list, key);

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

//erase the list and all its content
void list_erase(LIST **list){
	if(!list) return;

	NODE *actual = (*list)->start, *next = NULL;

	while(actual){
		next = actual->next;
		site_delete(&actual->site);
		free(actual);
		actual = next;
	}
	actual = NULL;
	free(*list);
	*list = NULL;
}


SITE *list_getsite(LIST *list, int key){
	if(!list) return FALSE;

	// gets the first site with key equal or larger than the input key
	NODE *actual = search_site_through_key(list, key);

	// if 'actual' key is equal as the input key, so return this site
	if(actual && site_get_key(actual->site) == key) return actual->site;

	// all nodes after 'actual' has key larger than the input key, so return FALSE
	printf("Sorry, no site with this key\n");
	return NULL;
}

int list_size(LIST *list){
	if(!list) return FALSE;
	return list->size;
}

boolean list_empty(LIST *list){
	if(!list || !list->size) return TRUE;
	return FALSE;
}

void list_print(LIST *list){
	if(list == NULL) return;
	
	NODE *aux = malloc(sizeof(NODE));
	aux = list->start;

	while(aux){
		site_print(aux->site);
		aux = aux->next;
	}
}

SITE **search_by_keyword(LIST *list, char *str, int *count){
	// matrix to get all the sites with 'str'
	SITE **sites = NULL;

	NODE *actual = list->start;
	while(actual){
		
		// verifies through all the sites of the list has the keyword 'str' and add to to matrix
		if(compare_string_with_keywords(actual->site, str)){
			sites = (SITE **) realloc(sites, sizeof(SITE *) * (*count + 1));
			sites[(*count)++] = actual->site;
		}
		actual = actual->next;
	}

	return sites;
}

void search_and_sort_sites_with_keyword(LIST *list, char *str){
	if(!list) return;

	// funtion to look for sites with keyword 'str'
	int count = 0;
	SITE **sites = search_by_keyword(list, str, &count);
	if(!sites){
		printf("Sorry, there are no sites with your keyword...\n");
		return;
	}

	// sort matrix 'sites'
	quick_sort(sites, 0, count - 1);

	printf("\nSo, these are the sites with keyword '%s':\n", str);
	for (int i = count - 1; i >= 0; i--)
		printf("%s - %s\n", site_getname(sites[i]), site_getURL(sites[i]));

	free(sites); sites = NULL;
}

char **search_and_collect_keyword_from_sites(LIST *list, char *str, int *total_kw){
	if(list_empty(list)) return NULL;

	// matrix with sites' keywords
	char **kw = NULL;
	int count = 0;

	NODE *actual = list->start;
	while(actual){
		// looks if 'actual' site has the input string, if TRUE, we already get
		// all the keywords from this site into our matrix
		if(compare_string_with_keywords(actual->site, str)){
			
			// realloc espace for 'actual->site' keywords
			int num_keywords = site_get_nkeywords(actual->site);
			*total_kw = *total_kw + num_keywords;
			kw = realloc(kw, sizeof(char *) * (*total_kw));
			
			// get all keywords' pointers from a site
			for(int i = 0; i < num_keywords; i++)
				kw[count++] = site_getkeywords(actual->site, i); 
		}
		actual = actual->next;
	}

	return kw;
}

SITE **sites_with_suggested_keywords(LIST *list, char **kw, int total_kw, int *n_sites){
	// matrix with all the sites that has at least one keyword in 'kw'
	SITE **sites = NULL;

	NODE *actual = list->start;
	while(actual){

		// verifies if the actual site has at least one of the keywords in 'kw'
		// if it has at least one, then add this site to the matrix 'sites'
		// and go to the next site, this way we optimize the search
		printf("erro1\n");	
		for(int i = 0; i < total_kw; i++){

			if(compare_string_with_keywords(actual->site, kw[i])){
				sites = realloc(sites, sizeof(SITE *) * (*n_sites + 1));
				sites[(*n_sites)++] = actual->site;
				break;
			}
		}
		printf("erro2\n");
		actual = actual->next;
	}

	return sites;
}

SITE **search_for_largest_relevance(SITE **sites, int n_sites){
	SITE **top5 = malloc(sizeof(SITE *) * 5);

	// bubble sort for 5 iteration, so the last five will have largest relevance
	for(int i = 0; i < 5; i++){          
       	for(int j = 0; j < n_sites - i -1; j++){  
          	if(site_get_relevance(sites[j]) > site_get_relevance(sites[j+1])){
              	SITE *temp = sites[j+1]; 
    			sites[j+1] = sites[j]; 
    			sites[j] = temp;
    		}
    	}
    }

    // get the last five to another matrix
    for(int i = 0, j = n_sites - 1; i < 5; i++, j--)
    	top5[i] = sites[j];

    return top5;
}

void sites_suggestions(LIST *list, char *str){

	// function that collects all keywords of sites with 'str' in its keywords
	int total_kw = 0;
	
	char **kw = search_and_collect_keyword_from_sites(list, str, &total_kw);
	for(int i = 0; i < total_kw; ++i) printf("%s\n", kw[i]);

 	// get sites with the keywords from 'kw'
 	int n_sites = 0;
	SITE **sites = sites_with_suggested_keywords(list, kw, total_kw, &n_sites);

	// looks for the 5 sites with larger relevance
	SITE **top5 = search_for_largest_relevance(sites, n_sites);

	printf("\nThanks for waiting, these are our suggestions for you:\n");
	for(int i = 0; i < 5; i++)
		printf("%d: %s - %s\n", i+1, site_getname(sites[i]), site_getURL(sites[i]));

	free(kw); kw = NULL;
	free(sites); sites = NULL;
	free(top5); top5 = NULL;
}
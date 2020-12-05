#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "site.h"
#include "utils.h"

struct site_{
    int key;            // primary key
    char *name;
    int relevance;
    char *URL;
    char **keywords;
    int num_kw;
};

SITE *site_create(int key, char *name, int relevance, char *URL, char **keywords, int nKeywords) {
    SITE *site = malloc(sizeof(SITE));

    if (site){
        site->key = key;
        site->name = malloc((strlen(name)+1)*sizeof(char));
        strcpy(site->name, name);
        site->relevance = relevance;
        site->URL = malloc((strlen(URL)+1)*sizeof(char));
        strcpy(site->URL, URL);
        site->keywords = NULL;
        site->keywords = malloc(nKeywords*sizeof(char*));
        site->num_kw = nKeywords;
        for(int i = 0; i < nKeywords; i++){
            site->keywords[i] = malloc((strlen(keywords[i])+1)*sizeof(char));
            strcpy(site->keywords[i], keywords[i]);
        }
    }
    return site;
}

//deletes the site and all content inside it
boolean site_delete(SITE **site) {
    if (!site)
        return FALSE;

    free((*site)->name); (*site)->name = NULL;
    free((*site)->URL); (*site)->URL = NULL;
    for(int i = 0; i < (*site)->num_kw; i++){
        free((*site)->keywords[i]);
        (*site)->keywords[i] = NULL;
    }
    free((*site)->keywords);
    free(*site); *site = NULL;
    return TRUE;
}

void site_print(SITE *site) {
    if (site){
        printf("%d,%s,%d,%s,%d", site->key, site->name, site->relevance, site->URL,site->num_kw);
        for(int i = 0; i < site->num_kw; i++) printf(",%s", site->keywords[i]);
        printf("\n");
    }
    else
        printf("Sorry bro, no data here\n");
}

int site_get_key(SITE *site) {
    if (site) return site->key;
    return -1;
}

char *site_getname(SITE *site){
    if(site) return site->name;
    return NULL;
}

char *site_getURL(SITE *site){
    if(site) return site->URL;
    return NULL;
}

int site_get_relevance(SITE *site){
    if(site) return site->relevance;
    return 0;
}

boolean site_set_relevance(SITE *site, int relevance){
    if(site == NULL) return FALSE;
    site->relevance = relevance;
    return TRUE;
}

boolean site_add_keyword(SITE *site, char *word){
    if(!site) return FALSE;
    site->keywords = realloc(site->keywords, sizeof(char *) * (site->num_kw + 1));
    site->keywords[site->num_kw] = strPart(word, NULL, NULL);
    site->num_kw++;
    return TRUE;
}

boolean site_remove_keyword(SITE *site, char *word){
    if(!site) return FALSE;
    for(int i = 0; i < site->num_kw; i++){
        if(site->keywords[i] == word){
            site->keywords[i] = NULL;
            site->keywords = realloc(site->keywords, sizeof(char *) * (site->num_kw - 1));
            return TRUE;
        }
    }
    printf("There is any '%s' here", word);
    return FALSE;
}

char *site_getkeywords(SITE *site, int index){
    if(site) return site->keywords[index];
    return NULL;
}

int site_get_nkeywords(SITE *site){
    if(site) return site->num_kw;
    return 0;
}

char *site_struct_to_string(SITE *site){
    char *line = malloc(sizeof(char) * 0);

    char *aux1;
    sprintf(aux1, "%d", site->key);
    strcat(line, aux1);
    strcat(line, ",");

    strcat(line, site->name);
    strcat(line, ",");
    
    char *aux2;
    sprintf(aux2, "%d", site->relevance);
    strcat(line, aux2);
    strcat(line, ",");

    strcat(line, site->URL);
    strcat(line, ",");

    for(int i = 0; i < site->num_kw; i++){
        strcat(line, site->keywords[i]);
        if(i != site->num_kw - 1) strcat(line, ",");
    }
    return line;
}

boolean compare_string_with_keywords(SITE *site, char *str){
    // go through site's keywords verifying if some matches 'str'
    for(int i = 0; i < site->num_kw; i++){
        printf("%s\n", site->keywords[i]);
        if(strcmp(site->keywords[i], str) == 0)
            return TRUE;
    }
    return FALSE;
}
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
        printf("%d,%s,%d,%s", site->key, site->name, site->relevance, site->URL);
        for(int i = 0; i < site->num_kw; i++) printf(",%s", site->keywords[i]);
        printf("\n");
    }
    else
        printf("Sorry bro, no data here\n");
}

SITE *site_copy(SITE *site){
    SITE *new = malloc(sizeof(SITE));
    new->key = site->key;
    new->name = strPart(site->name, NULL, NULL);
    new->relevance = site->relevance;
    new->URL = strPart(site->URL, NULL, NULL);
    new->num_kw = site->num_kw;
    for(int i = 0; i < site->num_kw; i++)
        new->keywords[i] = strPart(site->keywords[i], NULL, NULL);

    return new;
}

int site_get_key(SITE *site) {
    if (site) return site->key;
    return -1;
}

char *site_get_name(SITE *site){
    if(site) return site->name;
    return NULL;
}

char *site_get_URL(SITE *site){
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
    if (site->num_kw == 10){
        printf("There are already ten keywords in this site. You cannot add any further\n");
        return FALSE;
    }
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

char *site_get_keywords(SITE *site, int index){
    if(site) return site->keywords[index];
    return NULL;
}

int site_get_nkeywords(SITE *site){
    if(site) return site->num_kw;
    return 0;
}

SITE* create_site_from_googlebot(FILE* fp){
    char* line = readLine(fp);
    int nKeywords = 0;
    nKeywords = count_char(line, ',') - 3;
    if (nKeywords > 10){
        free(line);
        printf("Maximum keywords alowed are 10\n");
        return NULL;
    }
    char* codeChar = strsep(&line, ",");
    int code = atoi(codeChar);
    char* name = strsep(&line, ",");
    int relevance = atoi(strsep(&line, ","));
    char* url = strsep(&line, ",");
    char** keywords = malloc(nKeywords * sizeof(char*));
    for (int i = 0; i < nKeywords; i++){
        keywords[i] = strsep(&line, ",");
    }

    SITE* site = site_create(code, name, relevance, url, keywords, nKeywords);

    free(codeChar);
    free(keywords);
    return site;
}

boolean compare_string_with_keywords(SITE *site, char *str){
    // go through site's keywords verifying if some matches 'str'
    for(int i = 0; i < site->num_kw; i++){
        //printf("%s\n", site->keywords[i]);
        if(strcmp(site->keywords[i], str) == 0)
            return TRUE;
    }
    return FALSE;
}
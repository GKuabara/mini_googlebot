#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "site.h"
#include "AVLtree.h"
#include "utils.h"

char* readLine(FILE* stream) {
    //Fazendo uma alocação inicial
    char *word = (char*) malloc (32 * sizeof(char));

    int i = 0, tamanho = 32;
    do  {
        //Realocando a memória heap caso a palavra exceda o espaço máximo
        if (i == tamanho)  { 
            word = realloc (word, 2 * tamanho);
            tamanho *= 2;
        }
        //Recebendo os caracteres
        word[i] = (char) fgetc(stream); 
        //faço com que exclua o '\r' caso tenha
        if (word[i] == '\r') i--;
        i++;
    } while (word[i-1] != '\n' && !feof(stream));

    //Tirando epaço adicional
    word[i - 1] = '\0'; 
    word = realloc(word, i); 

    return word;
}

//função tanto copia quanto particiona strings
char* strPart(char* str, const void* init, const void* end) {
    int size = strlen(str);
    char* copy = (char*) malloc((size + 1) * sizeof(char));
    
    int i = 0;

    //faço contagem do número de bytes até chegar ao valor init
    if (init != NULL) {
        while (str[i] != *(char*)init && i <= size - 1) {
            i++;
        }
        i++;
    }
    if (i == size + 1) i--;

    if (end == NULL) end = "\0";
    int j = 0;

    //faço a copia da posição onde tem o valor init até o valor end
    while (str[i] != *(char*)end && i <= size - 1) {
        copy[j] = str[i];
        j++;
        i++;
    }
    copy[j++] = '\0';

    //faço o ajuste do tamanho da string copiada ou particionada
    if (j < size) {
        copy = (char*) realloc(copy, j);
    }

    return copy;
}

//faço junção de duas strings
char* strAppend(char* str, char* add) {
    int sizeStr = strlen(str);
    int sizeAdd = strlen(add);
    char *new = (char*) malloc((sizeStr + sizeAdd + 1) * sizeof(char));

    //faço a cópia das string umas sobre a outra
    for (int i = 0; i <= sizeStr; i++) 
        new[i] = str[i];
    for (int i = sizeStr, j = 0; j <= sizeAdd; i++, j++) 
        new[i] = add[j];
    
    return new;
}

void heapify(SITE **array, int n, int head){
    int big = head;
    int left =  big * 2 + 1;
    int right = big * 2 + 2;

    // if the left is larger than its root
    if(left < n && site_get_relevance(array[left]) > site_get_relevance(array[big])) big = left;
    // if the right is larger than its root
    if(right < n && site_get_relevance(array[right]) > site_get_relevance(array[big])) big = right;

    if(big != head){
        // swap root and bigger
        SITE *aux = array[head];
        array[head] = array[big];
        array[big] = aux;

        // calls the sub-tree
        heapify(array, n, big);
    }
}

void heap_sort(SITE **array, int n){
    // build max heap
    for(int i = n/2 - 1; i >= 0; i--)
        heapify(array, n, i);

    for(int i = n - 1; i > 0; i--){
        // moves current root (larger) to the end of the array
        SITE *aux = array[0];
        array[0] = array[i];
        array[i] = aux;

        // call max heap on the reduced array
        heapify(array, i, 0);
    }
}

int count_char (char *string, char searched){
    int count = 0;
    for (int i = 0; i < strlen(string); i++)
        if (string[i] == searched) count++;
    return count;
}

void bubble_sort(SITE **array, int len){
    for(int i = 0; i < 5; i++){          
        for(int j = 0; j < len - i -1; j++){  
            if(site_get_relevance(array[j]) > site_get_relevance(array[j+1])){
                SITE *temp = array[j+1]; 
                array[j+1] = array[j]; 
                array[j] = temp;
            }
        }
    }
}

int char_to_int(char c){
    int index = ((int)c - (int)'a');
    return index;
}
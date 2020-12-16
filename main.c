/*
 _________________________________________________ 
/        _________________________________        \
| == .  |      Gabriel Alves KUabara      |       |
|   _   |   Gabriel Freitas Vasconcelos   |    B  |
|  / \  |                                 | A   O |
| | O | |         N° USP 11275043         |  O    |
|  \_/  |         N° USP 11819084         |       |
|       |                                 |       |
|       |    gabrielalveskuabara@usp.br   | . . . |
|  :::  |    gabriel.vasconcelos@usp.br   | . . . |
|  :::  |_________________________________| . . . |
|                      G A K                      |
\_________________________________________________/
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AVLtree.h"
#include "site.h"
#include "utils.h"

void start_messages(){
	printf("These are the possible commands for this program:\n\n");
	printf("\t1 - Insert site\n");
	printf("\t2 - Remove site\n");
	printf("\t3 - Insert new keyword\n");
	printf("\t4 - Update site relevance\n");
	printf("\t5 - Search for sites with keyword\n");
	printf("\t6 - Sites sugestions\n");
	printf("\t7 - Exit Program\n\n");
}

void operations(TREE *tree){

	while(TRUE){
		printf("\nPlease, type a command: ");
		char* op = readLine(stdin);

		//insert new site
		if(!strcmp(op, "1")){
			printf("\nPlease, write all the site information as CSV: ");
			SITE *site = create_site_from_googlebot(stdin);
			insert_node(tree, site);
		}

		//remove site
		else if(!strcmp(op, "2")){
			printf("\nType the site code you want to delete: ");
			char* code2 = readLine(stdin);
			char* code2Aux = code2;

			int code2Int = atoi(code2Aux);

			if (code2Int == 0 && strcmp(code2, "0") != 0)
				printf("You typed an invalid site code.\n");
			else
				delete_node(tree, code2Int);

			free(code2);
		}

		//new key word
		else if(!strcmp(op, "3")){
			printf("\nType the site code you want to add a keyword: ");
			char* code3 = readLine(stdin);
			char* code3Aux = code3;

			printf("\nType the new keyword: ");
			char *keyword = readLine(stdin);

			int code3Int = atoi(code3Aux);

			if (code3Int == 0 && strcmp(code3, "0") != 0)
				printf("You typed an invalid site code.\n");
			else
				tree_insert_keyword(tree, code3Int, keyword);

			free(keyword); keyword = NULL;
			free(code3);
		}

		//update relevance
		else if(!strcmp(op, "4")){
			printf("\nType the site code you want to update relevance: ");
			char* code4 = readLine(stdin);
			char* code4Aux = code4;
			int code4Int = atoi(code4Aux);

			if (code4Int == 0 && strcmp(code4, "0") != 0)
				printf("You typed an invalid site code.\n");
			else{

				printf("\nType the new relevance: ");
				char* relevance = readLine(stdin);
				char* relevanceAux = relevance;
				int relevanceInt = atoi(relevanceAux);

				if (relevanceInt == 0 && strcmp(relevance, "0") != 0)
					printf("You typed an invalid relevance.\n");
				else
					tree_update_relevance(tree, code4Int, relevanceInt);

				free(relevance);
			}
			free(code4);
		}

		else if(!strcmp(op, "5")){
			printf("\nType your keyword and we search sites for you ٩(^‿^)۶ : ");
			getchar();
			char *str5 = readLine(stdin);
			search_and_sort_sites_with_keyword(tree, str5);
			free(str5); str5 = NULL;
		}

		else if(!strcmp(op, "6")){
			printf("\nType your keyword and just wait for some suggestions ~(‾▿‾)~ : ");
			getchar();
			char *str6 = readLine(stdin);
			sites_suggestions(tree, str6);
			free(str6); str6 = NULL;
		}

		//get out:
		else if(!strcmp(op, "7")){
			printf("\nOh no, this is a Good bye? (╥﹏╥)\n"
			"Take care of yourself! See you again!!!\n");
			free(op);				
			return;
		}

		else
			printf("\nPlease, can you type a valid operation number? ლ(ಠ益ಠლ)╯\n");

		free(op);
	}
}

int main() {
	printf("Hello my friend, welcome to our program! Enjoy the trip! ༼ つ ◕_◕ ༽つ \n\n");

	int nSites = 0;
	TREE* tree = tree_create();
	
	//reading all data
	FILE *fp = fopen("googlebot.txt", "r");
	printf("Reading from googlebot.txt...\n");

	while (!feof(fp)){
		SITE* site = create_site_from_googlebot(fp);
		insert_node(tree, site);
		nSites++;
	}
	fclose(fp);
	printf("Success Reading Input Data! Now, you have a tree bro!!!\n\n");

	start_messages(); //messages that show the commands
	print_tree(tree);
	
	operations(tree); //function that does all the operations required

	tree_delete(&tree);

	return 0;	
}
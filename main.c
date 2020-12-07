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
		int op;
		scanf("%d", &op);

		switch(op){
			//insert new site
			case 1:
				printf("\nPlease, write all the site information as CSV: ");
				getchar();
				SITE *site = create_site_from_googlebot(stdin);
				insert_node(tree, site);
				break;

			//remove site
			case 2:
				printf("\nType the site code you want to delete: ");
				int code2;
				scanf("%d", &code2);
				delete_node(tree, code2);
				break;

			//new key word
			case 3:
				printf("\nType the site code you want to add a keyword: ");
				int code3;
				scanf("%d", &code3); getchar();

				printf("\nType the new keyword: ");
				char *keyword = readLine(stdin);
				
				tree_insert_keyword(tree, code3, keyword);
				free(keyword); keyword = NULL;
				break;

			//update relevance
			case 4:
				printf("\nType the site code you want to update relevance: ");
				int code4;
				scanf("%d", &code4);

				printf("\nType the new relevance: ");
				int relevance;
				scanf("%d", &relevance);
				tree_update_relevance(tree, code4, relevance);
				break;

			case 5:
				printf("\nType your keyword and we search sites for you ٩(^‿^)۶ : ");
				getchar();
				char *str5 = readLine(stdin);
				search_and_sort_sites_with_keyword(tree, str5);
				free(str5); str5 = NULL;
				break;

			case 6:
				printf("\nType your keyword and just wait for some suggestions ~(‾▿‾)~ : ");
				getchar();
				char *str6 = readLine(stdin);
				sites_suggestions(tree, str6);
				free(str6); str6 = NULL;
				break;

			//get out:
			case 7:
				printf("\nOh no, this is a Good bye? (╥﹏╥)\n"
				"Take care of yourself! See you again!!!\n");				
				return;

			default:
				printf("\nPlease, can you type a valid operation number? ლ(ಠ益ಠლ)╯\n");
				break;
		}
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
# Mini_Googlebot
University project regarding data structures and algorithms

This project is just a simple googlebot. We read a csv file and build a AVL tree to store the sites' information. Respectively, the parameters of a website are: the key of the website, its name, relevance, URL, and keywords related to the site.

## Participants
Gabriel Alves Kuabara - N° USP 11275043 - gabrielalveskuabara@usp.br
Gabriel...

## Platform and Compilator
We used Sublime Text, VS code, WSL2, and all code was compiled using 'gcc'.

## Instructions for Use
When running the program, it will first read a csv file named "googlebot.txt", so that can be changed inside the main.c, then some initial messages will be displayed for the user, showing what commands are possible in this program. For example: insertion and deletion of a site, add a keyword to a site, update the relevance of a site, search for sites with a requested keyword, and sites suggestions.

## Explanation of the Data Structures used, Sorting Algorithms, and Some Functions

### Reasons to use a AVL:
Considering the available structures to build our project, a AVL tree allow us to make a search for a site's key with complexity O(log_2 n), being faster than a sequential data structures, like a linked list. Also, when we think about the functions to search for a keyword in every site (main function of the program), to use a tree or a list there is any big different because we need to access everysite in both cases. Therefore, we prefered to use the AVL tree with ordered keys to make easy the search for sites' keys.

### Search for keyword (main funcion of our googlebot):
When thinking about complexity, to find the sites with the requested keyword, we need to pass through all the sites independently of the data structure used. So, in the AVL tree, we pass through all sites looking for this keyword using a recursive function. Then, if we find it, we stop the loop through the keywords, and continue to the next site. After getting all sites containing the requested keyword, we sort the sites' array by relevance using a quick sort ($$n \cdot log n$$, and don't allocate more memory). Then we just print in descending order.

### Sites' Suggestions:
First of all, we used the same function of "Search for Keyword" to build our sites' array. Then, the next step was to use a TRIE TREE to store all keywords from our sites. That was because in a TRIE we are not repeating keywords (allocating more space for an existing keyword) and the search for a keyword is faster due to its own tree nature. After that, we need to look for all sites containing at least one of the keywords inside the TRIE. So, we recursively pass through our AVLtree verifying if its sites matches at least with one keyword. If a site matches, we add this site to our new sites array and skip this site's following keywords, going to the next node through the AVL. Now, we have a new sites' array that we need to sort by relevance. In this specific case, we need just the 5 sites with largest relevance, so we didn't need to sort all the array, when thinking about this we compared the sorting algorithms of complexity $$n \cdot log n$$ (like quick sort) and bubble sort. Bubble sort will have complexity of $$5n$$ while quick sort would keep with $$n \cdot log n$$. Considering that we would be sorting a huge amount of sites, this Bubble Sort looked to be the best option, while its complexity if linear and don't allocate more memory. Finally, we can just print the 5 last sites in the array.
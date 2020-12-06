# Mini_Googlebot
University project regarding data structures and algorithms

This project is just a simple googlebot. We read a csv file and build a AVL tree to store the sites' information. Respectively, the parameters of a website are: the key of the website, its name, relevance, URL, and keywords related to the site.

### Reasons to use a AVL:
Considering the available structures to build our project, a AVL tree allow us to make a search for a site's key with complexity O(log_2 n), being faster than a sequential data structures, like a linked list. Also, when we think about the functions to search for a keyword in every site (main function of the program), to use a tree or a list there is any big different because we need to access everysite in both cases. Therefore, we prefered to use the AVL tree with ordered keys to make easy the search for sites' keys.

### Search for keyword:
When thinking about complexity, to find the sites with the input keyword, we need to pass through all the sites independently of the data structure used. So, in the AVL tree, we pass through all sites looking for this keyword. Then, if we find it, we stop the loop through the keywords, and continue to the next site.
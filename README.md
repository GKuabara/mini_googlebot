# data-structures-and-algorithms-project
University project regarding data structures and algorithms

This project is just a simple googlebot. We use a csv text with a list of websites to start the linked list. Respectively, the parameters of a website are: the key of the website, its name, relevance, URL, and keywords related to the site.

### Reasons to use a linked list:
Considering the available structures to build our project, we may choose between a static or dinamic list. So, as we have to sort the sites according with its primary key, the use of a static list would be inneficient because all list's sites must be shifted everytime an insertion ou remotion occur, what costs lots of operations.

### Searching for keys:
Everytime we search for a specific site, we use an input key to find the site. So, to make an optimazed search, we use a loop to go through the list, comparing the input key with the sites' keys. Then, as the list is sorted, when the loop arrives at a site with key larger than the input key, this means that this input doesn't exists in the list. So, the loop breaks and it's returned that there is no site with the input.

### Search for keyword:
When thinking about complexity, to find the sites with the input keyword, we need to pass through all the sites independently of the data structure used. So, we kept the linked list due to the reasons already explained.
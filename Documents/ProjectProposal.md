# Project Proposal

## Leading Question 

We will essentially treat subreddit hyperlink data as a social network. Given the Stanford subreddit data graph, we perform a BFS traversal of the graph in order to find the shortest distance of hyperlinks between each subreddit. We then take the 10 closest subreddits based on hyperlink distance and print them out. The shorter the hyperlink distance, the more related two subreddits are. 

In addition, we want to gauge how positive the relationship is between each subreddit. We will do this by performing a BFS traversal on the graph of subreddits and gauging sentiment based on the link sentiment of each hyperlink. Our goal is to create a search tool that prints out the 10 closest subreddits to the subreddit in question as well as whether or not their relationship is positive or negative.

## Dataset Acquisition

Dataset link: http://snap.stanford.edu/data/soc-RedditHyperlinks.html 

## Data Format

We are using the Reddit Hyperlink Dataset found in the Stanford Network Dataset Collection. Our goal is to create a list of related subreddits based on the shortest distance between them in hyperlinks and the relation of each subreddit to the source subreddit. We will perform Dijkstra's Algorithm on the dataset to find the shortest distance of each subreddit from a chosen subreddit. We will then use a BFS traversal to find the sentiment of each subreddit to the source subreddit. We will use cycle detection in order to prevent hyperlinks from looping into each other. The dataset used is the “Social Network: Reddit Hyperlink Network” dataset located on the Stanford Network Database. We will be using the entire dataset. The data is provided as a tsv file. Each row has the source subreddit, target subreddit, timestamp, and properties of each message. It has about 56,000 subreddits with about 858,490 observations, or hyperlinks.

## Data Correction

The columns of interest are the ‘source subreddit’, ‘target subreddit’, and 'link sentiment'. The source and target subreddits indicate the direction of the relationship between them, and the link sentiment is an integer that takes the values of 1 or -1 depending on whether or not the relationship is positive or negative. We will clean the data with a Python script to get rid of inconsistent data, such as misspellings and blank cells, and then store it in another file.

## Data Storage

Our functions require a graph where nodes are obtained from the processed files. We’ll present this graph using an adjacency list. Therefore, the space complexity of this structure would be O(number of edges + number of nodes).

Each node will have a string value for the subreddit name and an integer indicating its relationship to the input subreddit.

## Algorithm 

Our input will be a subreddit name. We will then calculate the shortest distance for each subreddit from the submitted subreddit. Our output will be a vector of pairs. Each pair will have a node and an integer containing the distance of each subreddit to the input subreddit. Each node will contain a string for the name and an integer indicating the relationship the subreddit has with the source subreddit. The vector will contain the 10 closest subreddits.

Our graph that will store the data will be an adjacency list. We will read the file and only focus on the subreddit names and sentiment. We will then read and create a vector of strings containing every unique name mentioned in the file, which we will call the names vector. From there, we can build a directed graph of nodes that store two things: a string for the name, and an integer for the relationship of that node to the source node. More on that later.

Using the dataset, we will then read the file again to build out the list with each observation, inserting values into the adjacency list.

We will use cycle identification in order to go through the same nodes over and over again. When making our directed graph, we will create a disjoint set with indices that match the names vector. When we add values to our adjacency list, we make sure that the two subreddits are not located in the same union as each other. If that is the case, then we skip the hyperlink and move on to the next.

From there, we will traverse our graph using Dijkstra’s Algorithm to calculate distances. Dijkstra's algorithm will create a vector that stores the shortest distances to each node from the source node which we will call the distances vector. Once we have the distances, we simply find the 10 smallest in the distances vector and find the corresponding ones in the names vector. We then make pairs and return them.

For link sentiment, we will be doing a BFS traversal across the entire graph. Each edge, or adjacency, will have an additional value of -1 or 1 depending on the sentiment of the hyperlink. If it is -1, the relation is negative, and it is positive if it is 1. We will now use the integer values on each node.

We set the integer value on the source node to 1, and add it to a queue of nodes. The node we are traversing on will be referred to as the current node. Once we traverse to the current node, we will find the adjacent nodes based on direct hyperlinks with the current as the source. For each of the adjacent nodes, we will then find the hyperlink between them to find the sentiment of said hyperlink. Once we do, we change the int value attached to the adjacent node to be the product of the current node value and the hyperlink sentiment. We then add the node to the queue and pop the current node, going to the next.

Each node will then have a value that corresponds to its relation to the source node. If it has a value of -1, it has a negative relationship with the input subreddit. If it has a value of 1, it has a positive relationship. When we gather our pairs vector from the Dijkstra's algorithm, we will then locate each node in the pairs vector and then obtain their relation value. The final product will print out the 10 nodes, their distances, and their relation to the source node.

In summary, we will be using three main algorithms: BFS traversal, Dijkstra's Algorithm, and a disjoint set algorithm. The BFS traversal will be used to traverse through the graph and assign sentiment values to each node in relation to the source node based on the hyperlink sentiments and nodes before. Dijkstra's algorithm is used to output a vector of distances that will be used to find the shortest distances to the source node. The disjoint set algorithm is used primarily to combat cycles and will be used to identify when nodes create a hyperlink loop, and skip the hyperlink that would cause said loop.

The runtime of our algorithm for BFS traversal is O(V), where V represents the amount of nodes, which is 55,863 in this case. The runtime of our cycle will be O(n(log n)) as it relies on a disjoint set with union by size as it goes through every single observation. The runtime of creating the names vector should be O(n). The runtime of the Dijkstra's Algorithm is going to be O((E+V)log(V)), where E represents the amount of edges and V represents the amount of vertices.


## Timeline

Ideally, each algorithm should take at most a week to do. Our first week should be spent working on an algorithm to read the file and turn it into a names vector. Our second, and maybe third, week should be spent on creating the adjacency list and cycle detection. If this takes only one week, then we finish the BFS and Dijkstra's on week 3. If it takes more than two weeks to do the second part, then we finish this on week 4. Testing will be done as we go along.
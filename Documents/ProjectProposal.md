# Project Proposal

## Leading Question 

We will use the OpenFlights Airports Database, which contains thousands of airports, to convert it into graph structure and perform traversals of interest. Provided this graph, we will perform a BFS traversal of the graph in order to find the shortest distance between two destinations.

Furthermore, we will also present a more efficient way to tackle a more specific problem with the help of Dijkstra’s. Through Dijkstra’s, we plan to propose a way to find out the shortest distance between any two destinations. Then, to figure out the most popular airport, we will implement the PageRank algorithm. 

## Dataset Acquisition

Dataset link: https://openflights.org/data.html 

## Data Format

We are using the OpenFlights Airports Database. Our goal is to create a graph of airports connected as described in the dataset. The dataset used is the “Airports.dat” or ”Airports only, high quality” dataset. The file contains information on 14,110 distinct airports in 14 columns. We will preprocess the file to extract only the columns that are of interest to us and store them in a new CSV file.

## Data Correction

We have gotten rid of the irregularities in the route columns.

We will first check if the correct data types are used in each column/category. We will remove incorrect and NULL/NaN entries. This should not be a problem due to the large size of our dataset. In fact, keeping these faulty entries could mess up our analysis since our analysis heavily relies on individual data points (airport ID, etc). Lastly, we also plan to drop columns not relevant to our data analysis.

## Data Storage

Our functions require a graph where nodes are obtained from the processed files. We’ll present this graph using an adjacency list. Therefore, the space complexity of this structure would be O(number of edges + number of nodes).

## Algorithm 

### BFS
- After building the graph with the nodes represented as the airports and flights representing edge connections, we will establish our algorithms.
- Firstly, through the BFS traversal, we will input two airports and will check if those exist.
- Then, if they do, we will proceed to find the shortest path between them and display them.
- Theoretical time complexity: O(V + E)
- Target time complexity: O(V^2 + E)

### Dijkstra’s Algorithm
- In addition, we will use Dijkstra’s to show an efficient manner of carrying out the above process.
- We will input the airports and output the shortest path between them.
- Theoretical time complexity: O(|V|^2) (array implementation, which is the worst)

### PageRank
- We will implement a PageRank algorithm to output the most central airports in the given dataset.
- Here, we define centrality with the number of unique connections in mind.
- An airport’s graph will serve as the algorithm's input, and it will be utilized to identify the busiest airport. A dictionary containing an airport's popularity score will be the result
- Method: convergence of probabilities of Markov matrix
- Time complexity: O(K * N), K = number of iterations, N = space requirement, (K * space complexity).
- Space complexity is O(airlines*airports^2).

### Summary
In summary, we will be using three main algorithms: BFS traversal, Dijkstra's Algorithm, and PageRank. The BFS traversal will be used to traverse through the graph and output the path between two airports. Dijkstra's algorithm is used to output the distance between two airports of interest. Finally, PageRank helps us find out the most central airports.

## Timeline

We are currently done with data cleaning and parsing. Currently, we are working on the algorithms simultaneously and should be done with BFS and Dijkstra’s fairly soon. Implementing the PageRank should be done by the middle of next week. We will test the functions as we go and plan to start the presentation video ready immediately after completing the functions.
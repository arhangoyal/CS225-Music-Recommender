# Project Proposal

## Leading Question 

We will use the OpenFlights Airports Database, which contains thousands of airports, to convert it into graph structure and perform traversals of interest. Provided this graph, we will perform a DFS traversal of the graph in order to find the shortest distance between two destinations.

Furthermore, we will also present a more efficient way to tackle a more specific problem with the help of Dijkstra’s. Through Dijkstra’s, we plan to propose a way to find out the shortest distance between any two destinations. Then, to figure out the most central airport, we will implement the PageRank algorithm. 

## Dataset Acquisition

Dataset link: https://openflights.org/data.html 

## Data Format

We are using the OpenFlights Airports Database. Our goal is to create a graph of airports connected as described in the dataset. The dataset used is the “Airports.dat” or ”Airports only, high quality” dataset. The file contains information on 14,110 distinct airports in 14 columns. We will preprocess the file to extract only the columns that are of interest to us and store them in a new CSV file.

## Data Correction

We have gotten rid of the irregularities in the route columns.

We will first check if the correct data types are used in each column/category. We will remove incorrect and NULL/NaN entries. This should not be a problem due to the large size of our dataset. In fact, keeping these faulty entries could mess up our analysis since our analysis heavily relies on individual data points (airport ID, etc). Lastly, we also plan to drop columns not relevant to our data analysis.

Another important check we have put in is removing the rows with > 0 stops. The reason: imagine a flight from Chicago to Amsterdam and Amsterdam to Delhi. When finding the shortest route from Chicago to Delhi, we will anyway consider the route through Amsterdam because of our graph/web of airports. So > 0 stop rows are merely duplicates that we should discard to not mess up our data analysis like in finding the most central airport.

## Data Storage

Our functions require a graph where nodes are obtained from the processed files. We’ll present this graph using an adjacency list. Therefore, the space complexity of this structure would be O(number of edges + number of nodes).

## Algorithm 

After building the graph with the nodes represented as the airports and flights representing edge connections, we will establish our algorithms.

### DFS
- Inputs: startAirport and endAirport
- Output: path between startAirport and endAirport using depth-first search
- Theoretical time complexity: O(V + E)
- Target time complexity: O(V^2 + E) (worst case if we use array implementation)

### Dijkstra’s Algorithm
- Inputs: startAirport and endAirport
- Output: shortest path between startAirport and endAirport
- Target time complexity: O(|V|^2) (worst case if we use array implementation)
- Since Dijkstra’s Algorithm since essentially a weighted BFS traversal, we have the ability to include weights for our graph edges. We use the distance between airports for this.

### PageRank
- We will implement a PageRank algorithm to output the most central airports in the given dataset.
- Here, we define centrality with the number of unique connections in mind.
- An airport’s graph will serve as the algorithm's input, and it will be utilized to identify the busiest airport. A dictionary containing an airport's popularity score will be the result
- Method: convergence of probabilities of Markov matrix
- Time complexity: O(K * N), K = number of iterations, N = space requirement, (K * space complexity).
- Space complexity is O(airlines*airports^2).

### Summary
In summary, we will be using three main algorithms: DFS traversal, Dijkstra's Algorithm, and PageRank. The DFS traversal will be used to traverse through the graph and output the path between two airports. Dijkstra's algorithm is used to output the shortest path between two airports of interest with distance between two airports as edge weights while finding the shortest path. Finally, PageRank helps us find out the most central airports.

## Timeline

- Mid point check-in done on November 30, 2022 at 8 pm CST
- We are currently done with data cleaning and parsing. Currently, we are working on the algorithms simultaneously and should be done with them (DFS, Dijkstra’s and PageRank) fairly soon (Dec 7). We will test the functions as we go and start the presentation video and "Findings" document ready immediately after completing the functions.
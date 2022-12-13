# Video Presentation
- [https://youtu.be/H-d7jhaFIsA](https://youtu.be/H-d7jhaFIsA)

# Our Leading Questions & Results
- Q: How to find a viable path from one airport to another and what could be the shortest path possible, so that resources are utilized conservatively?
- A: For the first part of the question, we have devised the DFS algorithm to output us a possible route between two airports of our choice. Then, for the second problem, we have produced the Dijkstra’s algorithm to help find the shortest path between those two given airports, along with convenience of travel in mind.

- Q: How to find the airports which should receive appropriate resources for maintenance and other purposes, or which are the most central airports?
- A: We implemented the PageRank algorithm to essentially check which are the most central airports and hence should be allocated enough funding.

# Graph Algorithms

## Note about our Graph: It is Directed!
Our graph was directed. Example: There are multiple route (with layovers) from CMI to BSS but none from BSS to CMI, proving there must be edges which only go one way in our graph.

## DFS 
- Description: Performs a Depth-first search of the flight routes.
  - Inputs: StartNode EndNode
  - Output: vector of nodes in path (empty if path does not exist)
  - Time complexity: O(V<sup>2</sup> + E)
  - Example run description: For a complete operation, DFS will firstly initialize maps which will help us keep track of particular nodes which have been visited or not. This helps us in not including a node twice during path tracing. With the help of a stack, we maintain a list of edges which are visited and not, and then ultimately output the desired output. The final output of the BFS is a map containing all the edges.
- Tests implemented: 
  - Nonexistent path
  - Varied number of elements

## Dijkstra’s algorithm 
- Description: Performs a search but using a priority queue instead of a regular queue . Provides a route to maximize "ease" of travel.
  - Inputs: Starting Airport, Destination Airport
  - Output: Struct -> path: vector of nodes in path, Path Length: weighted length of path
  - Time complexity: O(V<sup>2</sup>)
- Example run description: Start by creating a weighted, directed adjacency matrix, where each entry reflects the inverse of the distance between the two locations in terms of flights. The next step is to update all linked airports, starting with the start airport, with the current airport's distance and weight of the connection, and to add the current airport's ID as the preceding airport. Create a priority queue for every connecting airport that hasn't been explored. Once the priority queue is empty, keep removing the first item from it and repeating the previous stages. After that, backtrack through each airport, adding each to a vector, starting at the final destination airport. The path is this vector's inverse.
- Tests implemented: 
  - Path of airport to itself
  - Varied Subsets Dataset test


## PageRank
- Description: The program calculates the likelihood of landing at a specific airport by taking a random flight, or the most central airports. It utilizes the convergence of Markov matrix's probabilities. Due to the fact that multiplying by the transition matrix has no effect on the output, this is also known as the steady state vector or the eigenvector of the transition matrix to the eigenvalue 1. The eigenvalues might be used to compute it normally, but given the size of our matrix, we chose to employ power iteration, which entails repeatedly multiplying an initial vector by the transition matrix. By locating the highest and minimum values in the matrix, we can then establish which airports are the most and least central.
  - Inputs: Adjacency matrix of airports
  - Output: getCenter() -> most central airport code, getLeastCenter() -> least central airport code
  - Time complexity: O(airports<sup>3</sup>)
- Example run description: The algorithm first starts by creating a weighted, directed adjacency matrix, where every another entry reflects the inverse of the distance between the two locations in terms of flights. The probability of traveling from the airport represented by each column to the airport represented by the row number is then represented by normalizing each column so that it amounts to one. Then, we find the greatest and minimum values of the resulting vector, which correspond to the most and least central airports, respectively.
- Tests implemented: 
  - Steady state vector properties
  - Most central airport
  - Least central airport


### General Tests (not directly related to one algorithm)
  - readInCSV base case
  - readInCSV small scale test (large scale is too difficult to test)
  - Weighted Adjacency Matrix construction small test
  - Weighted Adjacency Matrix construction medium test (large scale is too difficult to test)

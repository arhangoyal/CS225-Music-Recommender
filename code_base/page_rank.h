#pragma once

#include "airport.h"
#include "utils.h"

struct WeightedAdjacency {
    WeightedAdjacency(): n(0), matrix(vector<vector<unsigned int>>()), keys(map<string, unsigned int>()) {};
    size_t n;
    vector<vector<unsigned int>> matrix;
    map<string, unsigned int> keys;
};

class MainAlgos {
    public:
        // constructors and destructor
        MainAlgos();
        MainAlgos(const std::string& filename, bool from_csv=false);
        ~MainAlgos();

        // helper function: read flight data from csv file
        bool readInCSV(const std::string& filename);

        // helper function: read flight data from txt file
        void readInCompressed(const std::string& filename);

        // Write map data to compressed txt file
        void writeMapToFile(const string& filename);

        // getter for reference to airports map (for testing and Dijkstras)
        map<string, Airport*>& getAirports();

        // DFS main function
        // Input: none
        // Runs DFS in alphabetical order
        // Output: Map of edges in format "<start> <end>"
        map<string,short> DFS();

        // DFS recursive helper function
        // Note: Output is exclusively for DFS_to_path function
        map<string, string> DFS(string start, map<string, short>& edges, map<string, bool>& vertices);

        // Output: vector in order of airports taken to reach destination
        // Note: If no path exists, output is a vector with only the destination as its element
        vector<string> DFS_to_path(map<string, string> in, string end);

        // create weighted adjacency matrix (each position has value n, the number of flights from i to j)
        // needs to be manipulated for Dijkstra's and PageRank
        WeightedAdjacency getWeightedAdjacency();

        // calculates the steady state vector from PageRank
        std::vector<double> pageRankSSV();

        // calculates the steady state vector from PageRank (for testing)
        std::vector<double> pageRankSSVTest();

        // PageRank: Prints Top 5 Most Central Airports from the given dataset
        void getCenter();

        // PageRank: Prints Least Central Airport from the given dataset
        void getLeastCenter();

    
    private:
        map<string, Airport*> airport_lookup_; //lookup airports

};
    

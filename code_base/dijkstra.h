#pragma once
#include "page_rank.h"
#include "heap.h"
#include <float.h>

using namespace std;


struct DijkstraOutput {
    double pathLength_;
    vector<string> path_;
    DijkstraOutput() : pathLength_(0.0), path_(vector<string>()) {}
};

struct GraphVertex {
    double distance_;
    unsigned int prev_;
    string node_;
    GraphVertex() : distance_(DBL_MAX), prev_(INT_MAX), node_("") {}
    GraphVertex(double distance, unsigned int prev, string node) {
        distance_ = distance;
        prev_ = prev;
        node_ = node;
    }
};


class CompareVertex {
    public:
    bool operator()( const GraphVertex& lhs, const GraphVertex& rhs ) const {
        return lhs.distance_ < rhs.distance_;
    }
};

class Dijkstra {
    public:
    // default constructor, generatedAdjacency must be called after using default
    Dijkstra();
    
    // parameterized constructor, calls generateAdjacency
    Dijkstra(MainAlgos& dh);

    // generates special weighted adjacency matrix using function in data_handler
    void generateAdjacency(MainAlgos& dh);

    // finds path between two points
    DijkstraOutput findPath(string start, string dest);

    // helper for findpath
    void dijkstraSearch(vector<GraphVertex>& vertices, vector<bool>& visited, heap<GraphVertex, CompareVertex>& priorityQueue, unsigned int vert);

    private:
    // true if generateAdjacency has been run, prevents findPath from running if false
    bool generated;

    // weighted dijkstra's adjacency matrix (1/n where n is number of flights from i to j)
    vector<vector<double>> djWeightedAdj;

    // lookup dictionary from airport name tag to position in matrix (ex. STL -> 3)
    map<string, unsigned int> keys_;
    
    // lookup vector from position in matrix to airport name tag (ex. 3 -> STL)
    vector<string> values_;
};
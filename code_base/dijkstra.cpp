#include "dijkstra.h"

using namespace std;

// default constructor
Dijkstra::Dijkstra() : generated(false), djWeightedAdj(vector<vector<double>>()) {
    keys_ = map<string, unsigned int>();
    values_ = vector<string>();
}

// parameterized constructor, calls generateAdjacency
Dijkstra::Dijkstra(MainAlgos& dh) : generated(false), djWeightedAdj(vector<vector<double>>()) {
    keys_ = map<string, unsigned int>();
    values_ = vector<string>();
    generateAdjacency(dh);
}

// generates weighted adjacency matrix using function in data_handler
void Dijkstra::generateAdjacency(MainAlgos& dh) {
    generated = true;
    WeightedAdjacency w = dh.getWeightedAdjacency();
    djWeightedAdj.resize(w.n);
    for (size_t i = 0; i < w.n; i++) {
        djWeightedAdj[i].resize(w.n);
        for (size_t j = 0; j < w.n; j++) {
            djWeightedAdj[i][j] = w.matrix[i][j] == 0 ? 0 : 1 / static_cast<double>(w.matrix[i][j]);
        }
    }
    keys_ = w.keys;
    values_.resize(keys_.size());
    for (pair<string, unsigned int> p : keys_) {
        values_[p.second] = p.first;
    }
}

// finds path between two points
DijkstraOutput Dijkstra::findPath(string start, string dest) {
    if (!generated) throw runtime_error("adjacency matrix not generated");
    vector<GraphVertex> vertices;
    vertices.resize(djWeightedAdj.size());
    vector<bool> explored;
    explored.resize(djWeightedAdj.size());
    for (size_t i = 0; i < djWeightedAdj.size(); i++) {
        explored[i] = false;
    }

    heap<GraphVertex, CompareVertex> priorityQueue;

    if (keys_.find(start) == keys_.end() || keys_.find(dest) == keys_.end()) {
        cout << "no solution, missing start or dest" << endl;
        return DijkstraOutput();
    }

    vertices[keys_.at(start)].distance_ = 0;
    for (pair<string, unsigned int> p : keys_) {
        vertices[p.second].node_ = p.first;
    }

    priorityQueue.push(vertices[keys_.at(start)]);
    // cout << "add " << vertices[keys_[start]].node_ << " to queue" << endl;
    while (!priorityQueue.empty()) {
        // cout << "searching " << v.node_ << ", #" << keys_[v.node_] << endl;
        GraphVertex v = priorityQueue.pop();
        dijkstraSearch(vertices, explored, priorityQueue, keys_[v.node_]);
    }

    DijkstraOutput dr;
    dr.pathLength_ = vertices[keys_.at(dest)].distance_;
    unsigned int startPos = keys_.at(start);
    unsigned int currentPos = keys_.at(dest);
    while (currentPos != startPos) {
        if (currentPos > values_.size()) return DijkstraOutput();
        dr.path_.insert(dr.path_.begin(), values_.at(currentPos));
        currentPos = vertices[currentPos].prev_;
    }
    dr.path_.insert(dr.path_.begin(), start);
    return dr;
}

void Dijkstra::dijkstraSearch(vector<GraphVertex>& vertices, vector<bool>& visited, heap<GraphVertex, CompareVertex>& priorityQueue, unsigned int vert) {
    
    // ending case, needs to be fixed
    if (visited[vert]) {
        return;
    }

    for (size_t i = 0; i < djWeightedAdj.size(); i++) {
        if (visited[i]) {
            // cout << "visited already" << endl;
            continue; 
        }
        if (djWeightedAdj[vert][i] != 0) {
            // cout << "vert " << i << " distance = " << (vertices[i].distance == INT_MAX ? "Max" : to_string(vertices[i].distance)) << " vert " << vert << " distance = " << (vertices[vert].distance + djWeightedAdj[vert][i]) << endl;
            if (vertices[i].distance_ > (vertices[vert].distance_ + djWeightedAdj[vert][i])) {
                // cout << "found vert " << i << endl;
                vertices[i].distance_ = vertices[vert].distance_ + djWeightedAdj[vert][i];
                vertices[i].prev_ = vert;
                priorityQueue.push(vertices[i]);
            }
        }
    }
    visited[vert] = true;
}

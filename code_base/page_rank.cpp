#include "page_rank.h"
#include <stack>
#include "Eigen/Core"
#include "Eigen/Eigenvalues"


using namespace std;


// Constructors
MainAlgos::MainAlgos() {
    airport_lookup_ = map<string, Airport*>();
}

MainAlgos::MainAlgos(const string& filename, bool from_csv) {
    airport_lookup_ = map<string, Airport*>();
    // Read in CSV/compressed format
    if (from_csv) readInCSV(filename);
    else readInCompressed(filename);
}

// Destructor
MainAlgos::~MainAlgos() {
    // deletes dynamically allocated airport objects from the map
    for (pair<string, Airport*> p : airport_lookup_) {
        if (p.second != NULL) {
            delete p.second;
            p.second = NULL;
        }
    }
}


// helper function: read flight data from csv file
bool MainAlgos::readInCSV(const std::string& filename) {
    ifstream ifs(filename);
    if (!ifs.is_open()) return false;
    string line;
    // get rid of first entry (header)
    getline(ifs, line);

    // read in the rest of the entries
    while (ifs.good()) {

        getline(ifs, line);
        vector<string> delimited = utils::delimitLine(line, ',');
        if (delimited.size() <= 1) { return true; }


        string source = delimited.at(2);
        pair<string,string> destination = {delimited.at(0), delimited.at(4)};

        // id may not be a valid integer (bad data)
        int id;
        try { id = stoi(delimited.at(3)); }
        catch(std::invalid_argument& e) { id = -1; }

        // if airport does not exist, add new entry to map
        if (airport_lookup_.find(source) == airport_lookup_.end()) {
            airport_lookup_.insert(pair<string, Airport*>(source, new Airport(source, id, destination)));
            // prevent duplicate additions
            if (airport_lookup_.find(destination.second) == airport_lookup_.end()) {
                airport_lookup_[destination.second] = new Airport(destination.second);
            }
        }
        else {
            // if airport does exist, append destination
            airport_lookup_.at(source)->addDestination(destination);
            if (airport_lookup_.find(destination.second) == airport_lookup_.end()) {
                airport_lookup_[destination.second] = new Airport(destination.second);
            }
        }
    }
    return true;
}

// helper function: read flight data from txt file
void MainAlgos::readInCompressed(const std::string& filename) {
    ifstream ifs(filename);
    string line;

    // read in entries
    while (ifs.good()) {

        getline(ifs, line);
        vector<string> initial = utils::delimitLine(line, '>');
        // make sure line is of valid size
        if (initial.size() <= 1) { return; }

        // dynamically allocate new airport and insert into map
        string source = initial.at(0);
        Airport* ap = new Airport(source, -1);
        airport_lookup_.insert(pair<string, Airport*>(source, ap));

        // further separate line to obtain destinations and airlines
        vector<string> destinations = utils::delimitLine(initial.at(1), ',');
        for (string dest : destinations) {
            if (dest.size() == 0) continue;
            vector<string> sep = utils::delimitLine(dest, '|');
            if (sep.size() == 2) {
                const vector<char> rem = { '(', ')' };
                ap->addDestination(pair<string,string>(utils::removeChar(sep[0], rem), utils::removeChar(sep[1], rem)));
            }
            else {
                cout << "invalid format of compressed file, re-run generation"  << endl;
            }
        }
    }
}


// Write map data to compressed txt file
// Format: CDG>JFK, LHR, ORD, MIA, JFK, JFK
// This means: ORD has flights to JFK, LHR, OTZ, SHG, JFK, JFK
// Repeats (like JFK above) mean multiple flights or airlines
void MainAlgos::writeMapToFile(const string& filename) {
    ofstream ofs(filename);

    for (pair<string, Airport*> p : airport_lookup_) {
        ofs << p.first << ">";
        for (pair<string,string> dest : p.second->getDestinations()) {
            ofs << "("<< dest.first << "|" << dest.second << "),";
        }
        ofs << "\n";
    }
    ofs.close();
}

// DFS main function
// Input: none
// Runs DFS in alphabetical order
// Output: Map of edges in format "<start> <end>"
map<string,short> MainAlgos::DFS() {
    map<string, bool> vertex;
    map<string, short> edges;
    for (auto v : airport_lookup_) {
        if (!vertex[v.first]) {
            DFS(v.first, edges, vertex);
        }
    }
    return edges;
}

map<string, Airport*>& MainAlgos::getAirports() {
    return airport_lookup_;
}


// DFS recursive helper function
// Note: Output is exclusively for DFS_to_path function
map<string, string> MainAlgos::DFS(string start, map<string, short>& edges, map<string, bool>& vertices) {
    map<string, string> ret;
    vertices[start] = true;
    stack<string> s;
    s.push(start);
    while (!s.empty()) {
        string curr = s.top();
        s.pop();
        for (auto x : airport_lookup_[curr]->getDestinations()) {
            string dest = x.second;
            if (vertices[dest] == false) {
                vertices[dest] = true;
                string temp = curr;
                edges[temp.append(" ").append(dest)] = 1;
                s.push(dest);
                ret[dest] = curr;
            }
            else {
                string temp = curr;
                temp.append(" ").append(dest);
                if (edges[temp] != 1) edges[temp] = 2;
                if (ret[dest] == "") ret[dest] = curr;
            }
            
        }
    }
    ret[start] = "";
    // cout << "tada" << endl;
    return ret;
}


// Output: vector in order of airports taken to reach destination
// Note: If no path exists, output is a vector with only the destination as its element
vector<string> MainAlgos::DFS_to_path(map<string, string> in, string end) {
    stack<string> q;
    q.push(end);
    string next = in[end];
    while (next != "") {
        q.push(next);
        next = in[next];
    }
    vector<string> ret;
    while (!q.empty()) {
        ret.push_back(q.top());
        q.pop();
    }
    return ret;
}

// gets the weighted adjacency matrix (each position has value n, the number of flights from i to j)
// will be manipulated for Dijkstra's and PageRank
WeightedAdjacency MainAlgos::getWeightedAdjacency() {
    // initialize variables
    WeightedAdjacency w;
    w.n = airport_lookup_.size();
    w.matrix.resize(w.n);
    for (size_t i = 0; i < w.n; i++) {
        w.matrix[i].resize(w.n);
    }
    unsigned int count = 0;
    // initialize keys of airport lookup map
    for (pair<string, Airport*> airport : airport_lookup_) {
        w.keys.insert(pair<string, unsigned int>(airport.first, count++));
    }
    // for each source airport, add a flight for each destination
    for (pair<string, Airport*> airport : airport_lookup_) {
        if (airport.second == NULL) continue;
        vector<pair<string,string>>& destinations = airport.second->getDestinations();
        for (pair<string,string> dest : destinations) {
            if (w.keys.find(dest.second) == w.keys.end()) continue;
            w.matrix[w.keys.at(airport.first)][w.keys.at(dest.second)]++;
        }
    }
    return w;
}


// calculates the steady state vector from PageRank
std::vector<double> MainAlgos::pageRankSSV(){
    WeightedAdjacency w = getWeightedAdjacency();
    Eigen::MatrixXd m(w.n, w.n);
    // normalize weighted adjacency matrix by column
    for (int i = 0; i < (int)w.n; i++){
        // sum all entries in column
        double colSum = 0;
        for (int j = 0; j < (int)w.n; j++){
            colSum += w.matrix.at(j).at(i);
        }
        // divide all entries in column by column sum (or set to 1/n if column sum = 0)
        for (int j = 0; j < (int)w.n; j++){
            if (colSum != 0){
                m(j,i) = (double)w.matrix.at(j).at(i)/colSum;
            }
            else{
                m(j,i) = (1.00)/((double)(w.n));
            }
        }
    }

    Eigen::VectorXd start = Eigen::VectorXd::Zero(w.n);
    for (int i = 0; i < (int)w.n; i++){
        start(i) = (1.00)/((double)(w.n));
    }

    // run power iteration
    start = m * start;
    for (int i = 0; i < 100; i++){
        start = m * start;
    }

    // convert to vector<double> steady state vector
    vector<double> steady_state;

    for (int j = 0; j < (int)w.n; j++){
        steady_state.push_back(start(j));
    }
    return steady_state;
}

// calculates the steady state vector from PageRank (for testing)
std::vector<double> MainAlgos::pageRankSSVTest(){
    WeightedAdjacency w = getWeightedAdjacency();
    Eigen::MatrixXd m(w.n, w.n);
    // normalize by column
    for (int i = 0; i < (int)w.n; i++){
        // sum all entries in column
        double colSum = 0;
        for (int j = 0; j < (int)w.n; j++){
            colSum += w.matrix.at(j).at(i);
        }
        // divide all entries in column by column sum (or set to 1/n if column sum = 0)
        for (int j = 0; j < (int)w.n; j++){
            if (colSum != 0){
                m(j,i) = (double)w.matrix.at(j).at(i)/colSum;
            }
            else{
                m(j,i) = (1.00)/((double)(w.n));
            }
        }
    }

    Eigen::VectorXd start = Eigen::VectorXd::Zero(w.n);
    for (int i = 0; i < (int)w.n; i++){
        start(i) = (1.00)/((double)(w.n));
    }

    // run power iteration
    start = m * start;
    for (int i = 0; i < 150; i++){
        start = m * start;
    }

    // convert to vector<double> steady state vector
    std::vector<double> steady_state;

    for (int j = 0; j < (int)w.n; j++){
        steady_state.push_back(start(j)); 
    }
    return steady_state;
}


// PageRank: Prints Top 5 Most Central Airports from the given dataset
void MainAlgos::getCenter() {
    // get steady state vector
    pair<unsigned int, string> ret;
    vector<double> ssv = pageRankSSV();
    WeightedAdjacency w = getWeightedAdjacency();
    double max = 0; double maxIndex = 0;

    vector<double> ssv_desc = ssv;
    sort(ssv_desc.begin(), ssv_desc.end());
    reverse(ssv_desc.begin(), ssv_desc.end());
    for (int rank  = 1; rank <= 5; rank++) {
        max = ssv_desc[rank - 1];
        for (int i = 0; i < (int)ssv.size(); i++){
            if (ssv[i] == max) maxIndex = i;
        }

        map<string, unsigned int>::iterator it;
        for (it = w.keys.begin(); it != w.keys.end(); it++){
            if ( (int)(*it).second == maxIndex){
                ret.first = maxIndex;
                ret.second = (*it).first;
                cout << "Rank " << to_string(rank) << ": " << ret.second << endl;
            }
        }
    }
}


// PageRank: Prints Least Central Airport from the given dataset
void MainAlgos::getLeastCenter() {
    // get steady state vector
    vector<double> steady_state = pageRankSSV();
    double min = INT_MAX;
    double minIndex = 0; 
    WeightedAdjacency w = getWeightedAdjacency();

    // find position of min value in vector
    for (int i = 0; i < (int)steady_state.size(); i++){
        if (steady_state.at(i) < min){
            min = steady_state.at(i);
            minIndex = i;
        }
    }

    // find airport name of min value position
    map<string, unsigned int>::iterator it;
    for (it = w.keys.begin(); it != w.keys.end(); it++){
        if ( (int)(*it).second == minIndex){
            cout << "Least Central Airport: " << (*it).first << endl;
        }
    }
}

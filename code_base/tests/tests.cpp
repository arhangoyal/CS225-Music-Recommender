#include "../cs225/catch/catch.hpp"

// data_handler includes airport & utils
#include "../page_rank.h"
#include "../dijkstra.h"
#include <cmath>


using namespace std;

TEST_CASE("readInCSV basecase", "[valgrind][weight=1]") {
    cout << "readInCSV basecase" << endl;
    const string input = "tests/basecase.csv";

    // read data from csv file
    MainAlgos d(input, true);

    map<string, Airport*>& airports = d.getAirports();
    //vector<string> ans = { "JFK" };
    vector<string> ans = { "JFK" , "STL"};

    for (pair<string, Airport*> p : airports) {
        REQUIRE(find(ans.begin(), ans.end(), p.first) != ans.end());
    }
    for (string s : ans) {
        REQUIRE(airports[s]);
    }
}

TEST_CASE("readInCSV easy1", "[valgrind][weight=1]") {
    cout << "readInCSV easy1" << endl;
    const string input = "tests/easyroutes.csv";

    // read data from csv file
    MainAlgos d(input, true);

    map<string, Airport*>& airports = d.getAirports();
    //vector<string> ans = { "JFK", "STL", "LIL", "CMW" };
    vector<string> ans = { "JFK", "STL", "LIL", "CMW" , "DFW", "BRU", "FIA"};
    cout << airports.empty() << endl;
    for (pair<string, Airport*> p : airports) {
        //cout << "test3" << endl;
        REQUIRE(find(ans.begin(), ans.end(), p.first) != ans.end());
    }

    for (string s : ans) {
        REQUIRE(airports[s]);
    }
}

TEST_CASE("DFS", "[valgrind][weight=1]") {
    cout << "DFS" << endl;
    const string input = "tests/basecase.csv";

    // read data from csv file
    MainAlgos d(input, true);
    map<string,short> out = d.DFS();

    REQUIRE(out["JFK STL"] == 1);
}


TEST_CASE("Weighted Adjacency Matrix small", "[valgrind][weight=1]") {
    cout << "Weighted Adjacency Matrix small" << endl;
    const string input = "tests/basecase.csv";

    // read data from csv file
    MainAlgos d(input, true);

    vector<vector<int>> ans = { {0, 1},
                                {0, 0} };
    vector<string> ans_keys = {"JFK", "STL" };
    WeightedAdjacency w = d.getWeightedAdjacency();
    for (size_t i = 0; i < w.n; i++) {
        for (size_t j = 0; j < w.n; j++) {
            REQUIRE(w.matrix[i][j] == ans[i][j]);
        }
    }

    for (pair<string, unsigned int> key : w.keys) {
        bool found_key = false;
        for (string s : ans_keys) {
            if (key.first == s) {
                found_key = true;
                break;
            }
        }
        REQUIRE(found_key);
    }
}

TEST_CASE("Weighted Adjacency Matrix medium", "[valgrind][weight=1]") {
    cout << "Weighted Adjacency Matrix medium" << endl;
    const string input = "tests/easyroutes.csv";

    // read data from csv file
    MainAlgos d(input, true);

    vector<vector<int>> ans = { {0, 0, 0, 0, 0, 0, 0,},
                                {0, 0, 0, 0, 0, 0, 1,},
                                {0, 0, 0, 0, 0, 0, 0,},
                                {0, 0, 0, 0, 0, 0, 0,},
                                {0, 0, 0, 0, 0, 0, 1,},
                                {1, 0, 0, 0, 0, 0, 0,},
                                {0, 0, 1, 1, 0, 0, 0 } };
    vector<string> ans_keys = {"BRU","CMW","DFW","FIA","JFK","LIL","STL"};
    WeightedAdjacency w = d.getWeightedAdjacency();
    for (size_t i = 0; i < w.n; i++) {
        for (size_t j = 0; j < w.n; j++) {
            REQUIRE(w.matrix[i][j] == ans[i][j]);
        }
    }

    for (pair<string, unsigned int> key : w.keys) {
        bool found_key = false;
        for (string s : ans_keys) {
            if (key.first == s) {
                found_key = true;
                break;
            }
        }
        REQUIRE(found_key);
    }

}



TEST_CASE("Dijkstra self travel", "[valgrind][weight=1]") {
    cout << "Dijkstra self travel" << endl;
    const string input = "tests/easyroutes.csv";

    // read data from csv file
    MainAlgos d(input, true);

    Dijkstra dk = Dijkstra(d);
    DijkstraOutput result = dk.findPath("STL", "STL");
    vector<string> pathAns = { "STL" };
    for (size_t i = 0; i <= result.pathLength_; i++) {
        REQUIRE(result.path_[i] == pathAns[i]);
        cout << result.path_[i] << (i != result.pathLength_ ? " -> " : "");
    }
    cout << endl;

    cout << result.pathLength_ << endl;
    REQUIRE((result.pathLength_ == 0));
    REQUIRE(result.path_.size() == pathAns.size());

}

TEST_CASE("Dijkstra invalid travel", "[valgrind][weight=1]") {
    cout << "Dijkstra invalid travel" << endl;
    const string input = "tests/easyroutes.csv";

    // read data from csv file
    MainAlgos d(input, true);


    Dijkstra dk = Dijkstra(d);
    DijkstraOutput result = dk.findPath("STL", "LIL");
    REQUIRE(result.path_.size() == 0);
    REQUIRE(result.pathLength_ == 0);
}


TEST_CASE("Dijkstra easy", "[valgrind][weight=1]") {
    cout << "Dijkstra easy" << endl;
    const string input = "tests/easyroutes.csv";

    // read data from csv file
    MainAlgos d(input, true);


    Dijkstra dk = Dijkstra(d);
    DijkstraOutput result = dk.findPath("CMW", "DFW");
    vector<string> pathAns = { "CMW", "STL", "DFW" };
    cout << "route: ";
    for (size_t i = 0; i <= result.pathLength_; i++) {
        REQUIRE(result.path_[i] == pathAns[i]);
        cout << result.path_[i] << (i != result.pathLength_ ? " -> " : "");
    }
    cout << endl;

    cout << "path length: " << result.pathLength_ << endl;
    REQUIRE((result.pathLength_ == 2));
    REQUIRE(result.path_.size() == pathAns.size());

}


TEST_CASE("Dijkstra hard", "[valgrind][weight=1]") {
    cout << "Dijkstra hard" << endl;
    const string input = "data/routes.csv";

    // read data from csv file
    MainAlgos d(input, true);


    Dijkstra dk = Dijkstra(d);
    DijkstraOutput result = dk.findPath("STL", "BNB");
    vector<string> pathAns = { "STL", "ATL", "JFK", "BRU", "DLA", "FIH", "BNB" };
    cout << "route: ";
    for (size_t i = 0; i < result.path_.size(); i++) {
        REQUIRE(result.path_[i] == pathAns[i]);
        cout << result.path_[i] << (i != result.path_.size() - 1 ? " -> " : "");
    }
    cout << endl;

    cout << "path length: " << result.pathLength_ << endl;
    // relaxed pathLength_ test to avoid rounding errors
    REQUIRE((result.pathLength_ >= 1.83 && result.pathLength_ <= 1.85));
    REQUIRE(result.path_.size() == pathAns.size());
}

TEST_CASE("PageRank Steady State Vector Properties", "[valgrind][weight=1]") {
    cout << "PageRank Steady State Vector Properties" << endl;
    const string input = "data/routes.csv";

    // read data from csv file
    MainAlgos d(input, true);
    // cout << "successfully read from " << input << endl;
    std::vector<double> v = d.pageRankSSV();

    double sum = 0; 

    for (int i = 0; i < (int)v.size(); i++){
        sum+= v.at(i);
    }

    // 1.0001 used due to sum rounding errors
    REQUIRE( sum <= 1.0001 );

}

TEST_CASE("PageRank Convergence of Steady State Vector", "[valgrind][weight=1]") {
    cout << "PageRank Convergence of Steady State Vector" << endl;
    const string input = "data/routes.csv";

    // read data from csv file
    MainAlgos d(input, true);
    vector<double> v = d.pageRankSSV();
    vector<double> v2 = d.pageRankSSVTest();
    cout << abs(v.at(165) - v2.at(165)) << endl;

    REQUIRE( abs(v.at(165) - v2.at(165)) <= 0.001 );

}

/*TEST_CASE("Most Central Airport", "[valgrind][weight=1]") {
    cout << "Most Central Airport" << endl;
    const string input = "data/routes.csv";

    // read data from csv file
    MainAlgos d;

    REQUIRE(d.getCenter() == "Least Central Airport: ATL");

}

TEST_CASE("Least Central Airport", "[valgrind][weight=1]") {
    cout << "Least Central Airport" << endl;
    const string input = "data/routes.csv";

    // read data from csv file
    MainAlgos d;
    REQUIRE( d.getLeastCenter() == "Least Central Airport: BSS");
}*/
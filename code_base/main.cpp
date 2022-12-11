#include "page_rank.h"
#include "airport.h"
#include "dijkstra.h"

using namespace std;


// Currently coding with the idea that this will only be ran on this data set with this formatting
int main(int argc, char** argv) {

    cout << "\nData Processing..." << endl;
    MainAlgos d;


    // Case 1: read in data from routes.csv and save to compressed.txt
    if ((argc == 2 || argc == 3) && argv[1][0] == '-' && argv[1][1] == 'c' && argv[1][2] == 's' && argv[1][3] == 'v') {

        string input;
        string output = "./data/compressed.txt";

        // no specified input file
        if (argc == 2) {
            input = "./data/routes.csv";
        }
        else {
            input = argv[2];
        }

        // read data from csv file
        if (d.readInCSV(input)) {
            cout << "Successfully read flight data from " << input << endl;
            // write data to compressed file
            d.writeMapToFile(output);
            cout << "Successfully wrote flight data in to " << output << endl;
        }
        else {
            cout << "Faulty input file" << endl;
        }
    }


    // Case 2: read in data from compressed.txt and save to compressed_twice.txt
    else {
        cout << "Reading from compressed flight data..." << endl;
        const string input = "./data/compressed.txt";
        const string output = "./data/compressed_twice.txt";

        // read data from compressed file
        d.readInCompressed(input);
        cout << "Successfully read flight data from " << input << endl;

        // write data to another compressed file
        // to test if this works, run "diff ./data/compressed.txt ./data/compressed_twice.txt"
        // if there is no output, the files match (and they should)
        d.writeMapToFile(output);

        // Dijkstra
        if (argc == 4 && argv[1][0] == '-' && argv[1][1] == 'd' && argv[1][2] == 'k') {
            cout << "\n\n-------Dijkstra's Algorithm-------" << endl;
            string start = argv[2];
            string dest = argv[3];
            cout << "Look for shortest path from " << start << " to " << dest << endl;
            Dijkstra dk = Dijkstra(d);
            DijkstraOutput result = dk.findPath(start, dest);
            if (result.path_.size() == 0) {
                cout << "No paths were found :(";
            }
            else {
                cout << "Path: ";
                for (size_t i = 0; i < result.path_.size(); i++) {cout << result.path_[i] << (i != result.path_.size() - 1 ? " -> " : "");}
                cout << "\n" << "Path Length (weighted): " << result.pathLength_ << endl;
            }
            cout << endl;
        }

        // DFS
        else if (argc == 4 && argv[1][0] == '-' && argv[1][1] == 'd' && argv[1][2] == 'f' && argv[1][3] == 's') {
            cout << "\n\n-----Depth First Search (DFS)-----" << endl;
            map<string, short> out = d.DFS();
            string source = argv[2];
            string dest = argv[3];
            string query = source + " " + dest;

            map<string, short> edges;
            map<string, bool> vertices;
            vector<string> path = d.DFS_to_path(d.DFS(source, edges, vertices), dest);
            if (path.size() == 1 && source != dest) cout << "No paths were found :(";
            else {
                cout << "Path: ";
                for (size_t i = 0; i < path.size(); i++) cout << path[i] << (i != path.size() - 1 ? " -> " : "");
                cout << "\n" << "Path Length: " << path.size() - 1 << endl;
            }
            cout << endl;
        }

        // PageRank
        else if (argc == 3 && argv[1][0] == '-' && argv[1][1] == 'p' && argv[1][2] == 'r') {
            cout << "\n\n-------------PageRank-------------" << endl;
            if (argv[2][0] != 'T' && argv[2][0] != 'F') goto invalid;
            pair<unsigned int, string> res;
            if (argv[2][0] == 'T') d.getCenter();
            if (argv[2][0] == 'F') d.getLeastCenter();
        }

        // Errors
        else {
            invalid:
            cout << "\n\nInvalid Command Line Argument. Here's how to use it: " << endl << endl;
            cout << "---------------------STEP 1: Generate Routes---------------------" << endl << endl;
            cout << "-> Generate Compressed Routes: " << argv[0] << " -csv <file=default>" << endl;
            cout << "   - Converts provided csv into compressed.txt. Default = ./data/routes.csv" << endl;
            cout << "   - Example: " << argv[0] << " -csv" << endl << endl;

            cout << "---------------------STEP 2: Use Algorithms---------------------" << endl << endl;

            cout << "-> DFS: " << argv[0] << " -DFS <source airport> <destination airport>" << endl;
            cout << "   - Desc: Returns unweighted path between source and destination and path length." << endl;
            cout << "   - Example: " << argv[0] << " -dfs STL LIL" << endl << endl;

            cout << "-> Dijkstra's Algorithm: " << argv[0] << " -dk <source airport> <destination airport>" << endl;
            cout << "   - Returns shortest weighted path between source and destination and weighted path length." << endl;
            cout << "   - Example: " << argv[0] << " -dk STL LIL" << endl << endl;

            cout << "-> PageRank: " << argv[0] << " -pr  <T/F>" << endl;
            cout << "   - Returns most centralized or decentralized airport. T = centralized. F = decentralized." << endl;
            cout << "   - Example: " << argv[0] << " -pr T" << endl << endl;
        }
    }
    cout << "\n";
    
    return 0;
}
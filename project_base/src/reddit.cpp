#include "Reddit.h"

#include <fstream>
#include <string>
#include <sstream>
#include <iterator>
#include <algorithm>

// check entry file for main() function


Flights::Flights() {
    // do nothing
}


// the columns are as follows:
//
// airline, airline ID, source, source ID, dest, dest ID, codeshare, stops, equipment
//
// if source or dest is empty, then we have a problem. if stops is empty, we (may) have a problem
//
// We only care about columns (zero indexed) 2, 3, 4, 5, and maybe 7
//
// it is important to filter out faulty observations. if any of these are empty/missing, we have an issue

Flights::Flights(std::string filename) {
    std::string check = "\\N";
    // filename reading 
    std::ifstream stream(filename);
    std::string temp;
    // read until every line read
    while(std::getline(stream, temp)) {
        std::stringstream ss(temp);
        std::vector<std::string> vect;
        std::string linePart;
        // put every value in each column into a vector corresponding to said row
        while(std::getline(ss, linePart, ' ')) {
            vect.push_back(linePart);
        }
        // check if this line has enough data to be used
        lines_.push_back(vect);
    }
    // dataset has a row of labels, will have to look at that
    // lines_.erase(lines_.begin());
}

std::vector<std::string> Flights::getFirstLine() {
    if (lines_.empty()) {
        std::vector<std::string> temp;
        return temp;
    }
    return lines_[0];
}
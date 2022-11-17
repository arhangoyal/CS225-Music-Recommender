#include "reddit.h"

#include <fstream>
#include <string>
#include <sstream>
#include <iterator>
#include <algorithm>

Reddit::Reddit() {
    // do nothing
}

Reddit::Reddit(std::string filename) {
    // filename reading 
    std::ifstream stream(filename);
    std::string temp;
    while(std::getline(stream, temp)) {
        std::stringstream ss(temp);
        std::vector<std::string> vect;
        std::string linePart;
        while(std::getline(ss, linePart, '	')) {
            vect.push_back(linePart);
        }
        lines_.push_back(vect);
    }
    lines_.erase(lines_.begin());
}

std::vector<std::string> Reddit::getFirstLine() {
    if (lines_.empty()) {
        std::vector<std::string> temp;
        return temp;
    }
    return lines_[0];
}
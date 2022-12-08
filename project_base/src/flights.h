#pragma once
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>

// note: name has to be changed, we swapped over today so I didn't bother changing names yet

// in the future, we will have to change these names


// degree to radians
double toRadians(double deg);

// distance calculator
double distance(double lat1, double lat2, double long1, double long2);

class Flights {
    public:
        // default constructor, never used
        Flights();
        // reads file
        Flights(std::string filename, std::string airports);
        std::vector<std::string> getFirstLine();
        std::vector<std::string> getFirstPort();
    private:
        std::vector<std::vector<std::string>> lines_;
        std::vector<std::vector<std::string>> airports_;
};
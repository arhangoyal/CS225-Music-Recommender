#pragma once
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>

// note: name has to be changed, we swapped over today so I didn't bother changing names yet

// in the future, we will have to change these names


class Flights {
    public:
        // default constructor, never used
        Flights();
        // reads file
        Flights(std::string filename);
        std::vector<std::string> getFirstLine();
    private:
        std::vector<std::vector<std::string>> lines_;
};
#pragma once
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>


class Reddit {
    public:
        Reddit();
        Reddit(std::string filename);
    private:
        std::vector<std::vector<std::string>> lines_;
};
#pragma once
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>


class Reddit {
    public:
        Reddit();
        Reddit(std::string filename);
        std::vector<std::string> getFirstLine();
    private:
        std::vector<std::vector<std::string>> lines_;
};
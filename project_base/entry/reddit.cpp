#include "reddit.h"

#include <iostream>

int main() {
    Flights temp("/workspaces/CS225/project/newdata.csv");
    std::vector<std::string> check = temp.getFirstLine();
    for (size_t i = 0; i < check.size(); i++) {
        std::cout << check[i] << std::endl;
        std::cout << "next value" << std::endl;
    }
    return 0;
}
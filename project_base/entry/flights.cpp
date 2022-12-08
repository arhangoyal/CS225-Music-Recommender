#include "flights.h"

#include <iostream>

int main() {
    Flights temp("/workspaces/CS225/project/newdata.csv", "/workspaces/CS225/project/new_airports.csv");
    std::vector<std::string> check = temp.getFirstLine();
    std::cout << check[0] << std::endl;
    for (size_t i = 0; i < check.size(); i++) {
        std::cout << check[i] << ", next is ";
    }
    std::cout << std::endl;
    std::cout << "Now checking airports" << std::endl;
    std::vector<std::string> check2 = temp.getFirstPort();
    std::cout << check2[0] << std::endl;
    for (size_t i = 0; i < check2.size(); i++) {
        std::cout << check2[i] << ", next is ";
    }
    std::cout << std::endl;

    // test distance
    double lat1 = 53.32055555555556;
    double long1 = -1.7297222222222221;
    double lat2 = 53.31861111111111;
    double long2 = -1.6997222222222223;

    double dist = distance(lat1, lat2, long1, long2);
    std::cout << std::to_string(dist) << std::endl;



    return 0;
}
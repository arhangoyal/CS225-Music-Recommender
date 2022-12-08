#include "flights.h"
#include <bits/stdc++.h>

#include <fstream>
#include <string>
#include <sstream>
#include <iterator>
#include <algorithm>

// degree to radians
double toRadians(double deg) {
    double pi = M_PI;
    double one_d = (pi) / 180;
    return (deg * one_d);
}



double distance(double lat1, double lat2, double long1, double long2) {
    lat1 = toRadians(lat1);
    lat2 = toRadians(lat2);
    long1 = toRadians(long1);
    long2 = toRadians(long2);

    double dlong = long2 - long1;
    double dlat = lat2 - lat1;

    double ans = pow(sin(dlat / 2), 2) + cos(lat1) * cos(lat2) * pow(sin(dlong/2) , 2);
    ans = 2 * asin(sqrt(ans));

    // convert to kilometers
    ans = ans * 6371;
    return ans;
}


Flights::Flights() {
    // do nothing
}



// Data now only includes source, sourceID, dest, destID

// it is important to filter out faulty observations. if any of these are empty/missing, we have an issue

// weird thing is that when i print the contents of a vector, the [0]th index prints on its own but fails when done in for loop

Flights::Flights(std::string filename, std::string airports) {
    // filename reading 
    std::ifstream stream(filename);
    std::string temp;
    bool check = true;
    // read until every line read
    while(std::getline(stream, temp)) {
        std::stringstream ss(temp);
        std::vector<std::string> vect;
        std::string linePart;
        // put every value in each column into a vector corresponding to said row
        while(std::getline(ss, linePart, ' ')) {
            if (check) {
                check = false;
                std::cout << linePart << std::endl;
            }
            vect.push_back(linePart);
        }
        // check if this line has enough data to be used
        lines_.push_back(vect);
    }
    // dataset has a row of labels, will have to look at that
    // lines_.erase(lines_.begin());


    // adds airport data
    std::ifstream stream2(airports);
    std::string port;
    while (std::getline(stream2, port)) {
        std::stringstream ss2(port);
        std::vector<std::string> vect;
        std::string portData;
        while(std::getline(ss2, portData, ' ')) {
            vect.push_back(portData);
        }
        airports_.push_back(vect);
    }
    
}

std::vector<std::string> Flights::getFirstLine() {
    if (lines_.empty()) {
        std::vector<std::string> temp;
        return temp;
    }
    return lines_[0];
}

std::vector<std::string> Flights::getFirstPort() {
    if (airports_.empty()) {
        std::vector<std::string> temp;
        return temp;
    }
    return airports_[0];
}
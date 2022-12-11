#pragma once
#include "utils.h"

using namespace std;
class Airport {
    public:
        Airport(string iata_code);
        Airport(int airport_id);
        Airport(string iata_code, int airport_id);
        Airport(string iata_code, int airport_id, pair<string,string> destination);
        Airport(string iata_code, vector<pair<string,string>> destinations);
        string getIATACode();
        int getAirportID();
        vector<pair<string,string>>& getDestinations();
        vector<pair<string,string>> getArrivals(map<string, Airport*> m);
        void addDestination(pair<string,string> dest);
    private:
        string iata_code_;
        int airport_id_;
        vector<pair<string,string>> destinations_;
};
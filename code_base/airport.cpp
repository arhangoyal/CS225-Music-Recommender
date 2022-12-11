#include "airport.h"

using namespace std;


Airport::Airport(string iata_code) : iata_code_(iata_code), airport_id_(-1), destinations_(vector<pair<string,string>>()) {}

Airport::Airport(int airport_id) : iata_code_("unknown"), airport_id_(airport_id), destinations_(vector<pair<string,string>>()) {}

Airport::Airport(string iata_code, int airport_id) : iata_code_(iata_code), airport_id_(airport_id), destinations_(vector<pair<string,string>>()) {}

Airport::Airport(string iata_code, int airport_id, pair<string,string> destination) : iata_code_(iata_code), airport_id_(airport_id), destinations_(vector<pair<string,string>>()) {
    addDestination(destination);
}

string Airport::getIATACode() {
    return iata_code_;
}

int Airport::getAirportID() {
    return airport_id_;
}

vector<pair<string,string>>& Airport::getDestinations() {
    return destinations_;
}

vector<pair<string,string>> Airport::getArrivals(map<string, Airport*> m){
    std::vector<std::pair<string,string>> ret; map<string, Airport*> :: iterator it;
    // for (it = m.begin(); it != m.end(); it++){
    //     std::vector<std::pair<string,string>>& destinations = it->second->getDestinations();
    //     for (size_t x = 0; x < destinations.size(); x++ ){
    //         int id;
    //         try {
    //             id = stoi(destinations.at(x).second);
    //         }
    //         catch (std::invalid_argument& e) {
    //             id = -1;
    //         }

    //         if (destinations.at(x).first == getIATACode() && id == getAirportID()) ret.push_back(pair<string,string>(destinations.at(x).first, to_string(id)));
    //     }
    // }
    for (size_t x = 0; x < destinations_.size(); x++ ){
        std::vector<std::pair<string,string>>& destinations_ = it->second->getDestinations();
        for (it = m.begin(); it != m.end(); it++){
            int id;
            try { id = stoi(destinations_.at(x).second); }
            catch(std::invalid_argument& e) { id = -1; }
            if (destinations_.at(x).first == getIATACode() && id == getAirportID()){
                ret.push_back(pair<string,string>(destinations_.at(x).first, to_string(id)));
            }  
        }
    }
    return ret;
}

void Airport::addDestination(pair<string,string> dest) {
    destinations_.push_back(dest);
}


#ifndef CAMPW_STATE
#define CAMPW_STATE

#include <map>
#include <string>

typedef std::map<std::string,std::map<std::string,std::string>> json_data; 

extern json_data loaded_data; 


struct serviceUser {
    std::string service;
    std::string user;
    std::string pass;
};


#endif

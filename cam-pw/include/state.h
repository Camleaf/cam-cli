
#ifndef CAMPW_STATE
#define CAMPW_STATE

#include <map>
#include <string>



typedef std::map<std::string,std::string> service_group;
typedef std::map<std::string,service_group> json_data; 

extern json_data loaded_data; 


struct serviceUser {
    double queryScore;
    std::string service;
    std::string user;
    std::string pass;
};


#endif

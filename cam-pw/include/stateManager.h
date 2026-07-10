#ifndef CAMPW_STATEMANAGER
#define CAMPW_STATEMANAGER

#include <string>

int add_password(std::string service, std::string username, std::string enc_pass);
int query_password(std::string service, std::string username, std::string &enc_pass);
int prompt_for_master(std::string &master_key);
#endif

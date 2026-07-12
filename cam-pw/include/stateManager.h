#ifndef CAMPW_STATEMANAGER
#define CAMPW_STATEMANAGER

#include <string>
#include <state.h>
#include <vector>

int add_password(std::string service, std::string username, std::string enc_pass);
int query_password(std::string service, std::string username, std::string &enc_pass);
int prompt_for_master(std::string &master_key);
int delete_password(std::string service, std::string username);


int query_by_service(std::vector<serviceUser> &ordered_query_result, std::string service);
int query_all(std::vector<serviceUser> &ordered_query_result);
int query_by_username(std::vector<serviceUser> &ordered_query_result, std::string username);

#endif

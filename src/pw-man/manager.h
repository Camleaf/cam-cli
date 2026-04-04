#ifndef CAMCLI_PW_MANAGER
#define CAMCLI_PW_MANAGER

#include <nlohmann/json.hpp>
using json = nlohmann::json;
using namespace std;


// filecommands
json readFileAsJSON(string fileLocation);
void writeFileAsJSON(string fileLocation, json &data);
void wipeFile(string fileLocation);

// encrypt/decrypt stuff
string encryptValue(string value, string password);
string decryptValue(string value, string password);
bool checkMasterPW(json& data, string password);
bool checkMasterExistence(json& data);

//manager specifics
void setMasterPassword(string fileLocation);


#endif

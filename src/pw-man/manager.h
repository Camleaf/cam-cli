#ifndef CAMCLI_PW_MANAGER
#define CAMCLI_PW_MANAGER

#include "../util/constants.h"
#include <nlohmann/json.hpp>
using json = nlohmann::json;
using namespace std;

//         service   username password
typedef map<string,map<string,string>> passwordStructure;

// filecommands
json readFileAsJSON();
void writeFileAsJSON(json &data);
void wipeFile();
passwordStructure mapFromJSON(json& rawData);
json mapToJSON(passwordStructure& mapData);

// encrypt/decrypt stuff

string encryptValue(string value, string password);
string decryptValue(string value, string password);
bool checkMasterPW(passwordStructure& data, string password);
bool checkMasterPW(string value);
bool checkMasterExistence(passwordStructure& data);

//manager specifics
void setMasterPassword(bool flagSet);


#endif

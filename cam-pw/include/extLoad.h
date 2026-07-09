#ifndef CAMPW_EXTLOAD
#define CAMPW_EXTLOAD

#include <string>
#include <array>
#include <map>

using namespace std;

const string kDiskLoc = std::string(local_directory)+"pw-man/pw.json";
typedef map<string,map<string,string>> json_data; 


int load_disk(json_data &enc_json);
int write_disk(json_data enc_json);

#endif

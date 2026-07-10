#ifndef CAMPW_EXTLOAD
#define CAMPW_EXTLOAD

#include <string>
#include <state.h>

const std::string kHashLoc = std::string(local_directory)+"pw-man/hash";
const std::string kSaltLoc = std::string(local_directory)+"pw-man/salt";
const std::string kDiskLoc = std::string(local_directory)+"pw-man/pw.json";
const std::string kParentLoc = std::string(local_directory) + "pw-man/";


int load_disk(json_data &enc_json);
int write_disk(json_data enc_json);
int write_master_key_disk(std::string key);
bool is_key_master(std::string key);
#endif

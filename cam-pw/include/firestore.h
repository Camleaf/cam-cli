#ifndef CAMPW_FIRESTORE_SYNC
#define CAMPW_FIRESTORE_SYNC

#include <string>
#include <state.h>


const std::string kParentLoc = std::string(local_directory) + "pw-man/";


int load_disk(json_data &enc_json);
int write_disk(json_data enc_json);
int write_master_key_disk(std::string key);
bool is_key_master(std::string key);
#endif

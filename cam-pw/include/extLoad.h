#ifndef CAMPW_EXTLOAD
#define CAMPW_EXTLOAD

#include <string>
#include <state.h>

const std::string kHashLoc = std::string(local_directory)+"pw-man/hash";
const std::string kSaltLoc = std::string(local_directory)+"pw-man/salt";
const std::string kDiskLoc = std::string(local_directory)+"pw-man/pw.json";
const std::string kParentLoc = std::string(local_directory) + "pw-man/";
const std::string kBackendKeyLoc = std::string(local_directory) + "pw-man/backend_enc";

int load_disk(json_data &enc_json);
int write_disk(json_data enc_json);
int write_master_key_disk(std::string key);
bool is_key_master(std::string key);

int load_backend_key_disk(std::string &enc_backend_key);
int write_backend_key_disk(std::string enc_backend_key);

#endif

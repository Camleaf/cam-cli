#ifndef CAMPW_FIRESTORE_SYNC
#define CAMPW_FIRESTORE_SYNC

#include <string>
#include <state.h>


const std::string kWebAddress = "https://cam-cli.vercel.app";


int load_backend(json_data &enc_json, std::string pw);
int store_backend(json_data enc_json, std::string pw, bool prune=false);
#endif

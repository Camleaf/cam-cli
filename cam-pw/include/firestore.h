#ifndef CAMPW_FIRESTORE_SYNC
#define CAMPW_FIRESTORE_SYNC

#include <string>
#include <state.h>


const std::string kWebAddress = "https://cam-cli.vercel.app";


int load_firebase(json_data &enc_json);
int write_firebase(json_data enc_json, bool prune=false);
#endif

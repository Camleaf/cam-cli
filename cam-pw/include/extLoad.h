#ifndef CAMPW_EXTLOAD
#define CAMPW_EXTLOAD

#include <string>
#include <array>

using namespace std;

int file_exists_disk(std::string filename);
int pass_exists_disk(std::string name);
int load_pass_disk(std::string name, std::string &encrypted_pass);
int create_pass_disk(std::string name, std::string encrypted_pass);

#endif

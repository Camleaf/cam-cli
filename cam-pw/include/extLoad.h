#ifndef EXTLOAD
#define EXTLOAD

#include <string>
#include <array>

using namespace std;

int file_exists_disk(std::string filename);
int pass_exists_disk(std::string user);
int load_pass_disk(std::string user, std::string &encrypted_pat);
int create_pass_disk(std::string user, std::string encrypted_pat);

#endif

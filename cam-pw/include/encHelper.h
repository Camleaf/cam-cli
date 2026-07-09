#ifndef CAMPW_ENCHELPER 
#define CAMPW_ENCHELPER
#include <string>

int gpg_decrypt(std::string key, std::string encrypted_pass, std::string &pass);
int gpg_encrypt(std::string key, std::string pass, std::string &encrypted_pass);
int generateHash(std::string unhashed, std::string &hashed);
bool is_key_master(std::string key);

#endif

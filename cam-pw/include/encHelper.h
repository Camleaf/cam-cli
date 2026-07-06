#ifndef CAMPW_ENCHELPER 
#define CAMPW_ENCHELPER
#include <string>

int gpg_decrypt(std::string key, std::string encrypted_pass, std::string &pass);
int gpg_encrypt(std::string key, std::string pass, std::string &encrypted_pass);


#endif

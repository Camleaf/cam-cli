#ifndef SGIT_PATHELPER
#define SGIT_PATHELPER

#include <string>

int gpg_decrypt(std::string password, std::string encrypted_pat, std::string &pat);
int gpg_encrypt(std::string password, std::string pat, std::string &encrypted_pat);


#endif

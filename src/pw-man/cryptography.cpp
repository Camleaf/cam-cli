#include "./manager.h"
#include <iostream>



string encryptValue(string value, string password){
    // todo implement
    return value;
}


string decryptValue(string value, string password){
    //todo implement
    return value;
}

// Checks if the master password is correct by decoding the stored master password, and seeing if the two passwords are equal.
bool checkMasterPW(json& data, string password){
    string encryptedKey = data.find("master").value()[0];
    return decryptValue(encryptedKey, password) == password;
}

bool checkMasterExistence(json& data){
    return data.find("master") == data.end();
}

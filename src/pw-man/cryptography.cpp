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


bool checkMasterPW(string value){
    json rawData = readFileAsJSON();
    passwordStructure data = mapFromJSON(rawData);
    return checkMasterPW(data, value);
}

// Checks if the master password is correct by decoding the stored master password, and seeing if the two passwords are equal.
bool checkMasterPW(passwordStructure& data, string password){
    string encryptedKey = data["master"]["user"];
    return decryptValue(encryptedKey, password) == password;
}



bool checkMasterExistence(passwordStructure& data){
    if (data.find("master") == data.end()) return false;
    if (data["master"].find("user") == data["master"].end()) return false;
    return true;
}

#include <iostream>
#include <ranges>
#include "./manager.h"
#include "../util/iohelper.h"
// Start by making it without encryption, but add encryption later
// Is also possible that I can encrypt the JSON string before writing and decrypt when reading
// maybe later can add password caching for length of terminal session

// I want the format to look like this
// Will store in JSON

/*
printed to user on printall:
Website email/username   password
        email3/username2 password

stored as:

{
    [string Website]: {
        [string email/username]: password
    }
}

*/


void setMasterPassword(bool flagSet){

    json rawData = readFileAsJSON();
    passwordStructure data = mapFromJSON(rawData);
    
    // check if there is no master key already. If there isn't then we can assume that the passwords list is empty 
    if (!checkMasterExistence(data)){
        cout << "Could not find existing master password. Creating one will invalidate any existing data in the password document." << endl<<endl;
        string pw = getValidInput("Enter password (a-zA-Z0-9,symbols, nospace)");
        if (pw == "") return;
        data["master"]["user"] = encryptValue(pw,pw);
        json createdData = mapToJSON(data); 
        writeFileAsJSON(createdData);
        return;
    }
    
    string pw = getValidInput("Enter password (a-zA-Z0-9, symbols, nospace)");
    if (pw == "") return;

    // Case where password is the same as the one already there
    if (checkMasterPW(data,pw)) {
        cout << "Password is already the master password. Exiting." << endl;
        return;
    }


    // Case where password isn't the one already there
    //cout << "Wipe all stored passwords or transfer to new password? (wipe,transfer)" << endl;
    string answer = getInputOption(vector<string> {"wipe", "transfer"}, "Wipe all stored passwords or transfer to new password? (wipe,transfer)");
    if (answer == "") return;

    passwordStructure newData;
    if (answer == "wipe"){
        wipeFile();
        newData["master"]["user"] = encryptValue(pw,pw);
        json createdData = mapToJSON(newData);
        writeFileAsJSON(createdData);
        return;
    }
    
    string oldpw = getValidInput("Enter old password (a-zA-Z0-9, symbols, nospace)", checkMasterPW);
    if (pw == "" || !checkMasterPW(data,oldpw)) return;
    
    for (auto it = data.begin(); it != data.end(); ++it) {
        string service = it->first;
        map<string,string> value = it->second;
         
        map<string,string> temp;
        for (auto it2 = value.begin(); it2 != value.end(); ++it2) {
            temp[it2->first] = encryptValue(decryptValue(it2->second,oldpw),pw);
        }
        newData[service] = temp;
    }
    newData["master"]["user"] = encryptValue(pw,pw);

    json JSONData = mapToJSON(newData);
    writeFileAsJSON(JSONData);
 
    // If the password exists, this is a bit more involved, as we have to ask them if they want to wipe or transfer all passwords    
}


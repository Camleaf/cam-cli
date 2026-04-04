#include <iostream>
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



void setMasterPassword(string fileLocation){
    
    json data = readFileAsJSON(fileLocation);
    
    
    // check if there is no master key already. If there isn't then we can assume that the passwords list is empty 
    if (checkMasterExistence(data)){
        cout << "Could not find existing master password. Creating one will invalidate any existing data in the password document." << endl<<endl;
        string pw = getValidPasswordInput("Enter password (a-zA-Z0-9,symbols, nospace)");
        if (pw == "") return;
        data["master"] = {pw};
        writeFileAsJSON(fileLocation,data);
        return;
    }
    
    string pw = getValidPasswordInput("Enter password (a-zA-Z0-9,symbols, nospace)");
    if (pw == "") return;

    // Case where password is the same as the one already there
    if (checkMasterPW(data,pw)) {
        cout << "Password is already the master password. Exiting." << endl;
        return;
    }


    // Case where password isn't the one already there
    //cout << "Wipe all stored passwords or transfer to new password? (wipe,transfer)" << endl;
    string answer = getInputOption(vector<string> {"wipe", "transfer"}, "Wipe all stored passwords or transfer to new password? (wipe,transfer)");
    cout << answer << endl;

    
    // If the password exists, this is a bit more involved, as we have to ask them if they want to wipe or transfer all passwords
    
}



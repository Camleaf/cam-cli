#include <fstream>
#include <filesystem>
#include <iostream>
#include "./manager.h"
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
        string pw = "";
        int attempt = 0;
        while (
            pw.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_!@#$%^&*()/\\:;.,<>~?") != string::npos ||
            pw == ""
        ){
            if (attempt == 3) {
                cout << "Exiting" << endl;
                return;
            }

            attempt++;
            if (attempt != 1) {
                cout << "Invalid password" << endl << endl;
                cout << "(" << attempt << "/3) ";
            }


            cout << "Enter new password: " << endl << "> ";
            cin >> pw;
            
        }
        data["master"] = {pw};
        writeFileAsJSON(fileLocation,data);
        return;
    }

    
}



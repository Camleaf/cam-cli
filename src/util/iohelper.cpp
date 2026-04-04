#include "./iohelper.h"
#include <cstdio>
#include <vector>

/* Wipes n previous lines in the console, inclusive of current line.
 */ 
void wipeNLines(int n){
    for (int i = 0; i < n; i++){
        cout << "\033[A\033[2K";
    };
    cout << "\r";
}

bool checkIfRightPWChars(string value){
    return value.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_!@#$%^&*()/\\:;.,<>~?|+=-~`") == string::npos
            &&
            value != "";
}

string getValidInput(string message, validityCallback callback){
    string pw = "";

    for (int idx = 0; idx < 3; idx++){
        
        cout << message;
        cout << " (" << idx + 1 << "/3)" << endl;
        cout << "> ";
        getline(cin, pw);

        if (callback(pw)){
            return pw;
        }
        wipeNLines(2);

    };
    cout << "Exiting";
    return "";
}

string getInputOption(vector<string> options, string message){
    string choice = "";
    for (int idx = 0; idx < 3; idx++){
        cout << message;
        cout << " (" << idx + 1 << "/3)" << endl;

        cout << "> ";
        getline(cin, choice);
        
        for (string option : options) {
            if (choice == option) return choice;
        }

        wipeNLines(2);
    }
    cout << "Exiting";
    return "";
}

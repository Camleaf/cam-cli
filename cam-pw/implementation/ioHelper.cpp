#include <algorithm>
#include <ioHelper.h>
#include <cstdio>
#include <random>
#include <vector>
#include <iostream>

/* Wipes n previous lines in the console, inclusive of current line.
 */ 
void wipe_n_lines(int n){
    for (int i = 0; i < n; i++){
        cout << "\033[A\033[2K";
    };
    cout << "\r";
}

bool check_if_right_pw_chars(string value){
    return value.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_!@#$%^&*()/\\:;.,<>~?|+=-~`") == string::npos
            &&
            value != "";
}

bool empty_validity_callback(string value) { return true;}


int get_valid_input(string message, string &choice, validityCallback callback){

    for (int idx = 0; idx < 3; idx++){
        
        cout << message;
        cout << " (" << idx + 1 << "/3): ";
        getline(cin, choice);

        if (callback(choice)){
            return 1;
        }
        wipe_n_lines(1);

    };
    return 0;
}

int get_input_option(string message, string &choice, vector<string> options){
    for (int idx = 0; idx < 3; idx++){
        cout << message;
        cout << " (" << idx + 1 << "/3): ";
        getline(cin, choice);
        
        for (string option : options) {
            if (choice == option) return 1;
        }

        wipe_n_lines(1);
    }
    return 0;
}


// Random string gen found from some internet forum 10 yrs ago xd.
std::string random_string(size_t len) {
    std::string const allowed_chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_!@#$%^&*()/\\:;.,<>~?|+=-~`";
    std::mt19937_64 gen { std::random_device()() };

    std::uniform_int_distribution<size_t> dist { 0, allowed_chars.length()-1 };

    std::string ret;

    std::generate_n(std::back_inserter(ret), len, [&] { return allowed_chars[dist(gen)]; });
    return ret;
}


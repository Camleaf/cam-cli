#include <algorithm>
#include <ioHelper.h>
#include <cstdio>
#include <iomanip>
#include <random>
#include <vector>
#include <iostream>

/* Wipes n previous lines in the console, inclusive of current line.
 */ 
void wipe_n_lines(int n){
    for (int i = 0; i < n; i++){
        std::cout << "\033[A\033[2K";
    };
    std::cout << "\r";
}

bool check_if_right_pw_chars(std::string value){
    return value.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_!@#$%^&*()/\\:;.,<>~?|+=-~`") == std::string::npos
            &&
            value != "";
}

bool empty_validity_callback(std::string value) { return true;}


int get_valid_input(std::string message, std::string &choice, validityCallback callback){

    for (int idx = 0; idx < 3; idx++){
        
        std::cout << message;
        std::cout << " (" << idx + 1 << "/3): ";
        std::getline(std::cin, choice);

        if (callback(choice)){
            return 1;
        }
        wipe_n_lines(1);

    };
    return 0;
}

int get_input_option(std::string message, std::string &choice, std::vector<std::string> options){
    for (int idx = 0; idx < 3; idx++){
        std::cout << message;
        std::cout << " (" << idx + 1 << "/3): ";
        std::getline(std::cin, choice);
        
        for (std::string option : options) {
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





// Some conversion code from stackoverflow
std::string binary_to_hex(const std::string& binary_str) {
    std::stringstream ss;
    ss << std::hex << std::setfill('0');
    for (unsigned char c : binary_str) {
        ss << std::setw(2) << static_cast<int>(c);
    }
    return ss.str();
}

std::string hex_to_binary(const std::string& hex_str) {
    std::string binary_str;
    binary_str.reserve(hex_str.length() / 2);
    for (size_t i = 0; i < hex_str.length(); i += 2) {
        std::string byte_str = hex_str.substr(i, 2);
        char byte = static_cast<char>(strtol(byte_str.c_str(), nullptr, 16));
        binary_str.push_back(byte);
    }
    return binary_str;
}

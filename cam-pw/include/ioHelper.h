#ifndef CAMPW_IOHELPER
#define CAMPW_IOHELPER

#include <string>
#include <iostream>
#include <vector>

using namespace std;

bool check_if_right_pw_chars(string value);
typedef bool (*validityCallback)(string value);

bool empty_validity_callback(string value);

void wipe_n_lines(int n);
int get_valid_input(string message, string &choice, validityCallback callback=check_if_right_pw_chars);
int get_input_option(string message, string &choice, vector<string> options);
std::string random_string(size_t len = 15);
#endif

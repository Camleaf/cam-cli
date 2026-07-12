#ifndef CAMPW_IOHELPER
#define CAMPW_IOHELPER

#include <string>
#include <iostream>
#include <vector>
#include <state.h>

bool check_if_right_pw_chars(std::string value);
typedef bool (*validityCallback)(std::string value);

bool empty_validity_callback(std::string value);

void wipe_n_lines(int n);
int get_valid_input(std::string message, std::string &choice, validityCallback callback=check_if_right_pw_chars);
int get_input_option(std::string message, std::string &choice, std::vector<std::string> options);
std::string random_string(size_t len = 15);
int outputQuery(std::vector<serviceUser> &ordered_query_result, std::string master_key="", int result_count = 10);
int formatLine(std::string service, std::string username, std::string password, std::array<int, 3> cols);

std::string binary_to_hex(const std::string& binary_str);
std::string hex_to_binary(const std::string& hex_str);

#endif

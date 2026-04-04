#ifndef CAMCLI_IOHELPER
#define CAMCLI_IOHELPER

#include <string>
#include <iostream>
#include <vector>

using namespace std;

bool checkIfRightPWChars(string value);
typedef bool (*validityCallback)(string value);

string getValidInput(string message, validityCallback callback=checkIfRightPWChars);
string getInputOption(vector<string> options, string message);


#endif

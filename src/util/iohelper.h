#ifndef CAMCLI_IOHELPER
#define CAMCLI_IOHELPER

#include <string>
#include <iostream>
#include <vector>

using namespace std;

string getValidPasswordInput(string message);
string getInputOption(vector<string> options, string message);

#endif

#include "iostream"
#include <CLI11.hpp>
#include "pw-man/manager.h"
#include <filesystem>
#include <format>
#include <ostream>
// maybe use like CLI11 or some other cli tool for parseing input

using namespace std;

int main (int argc, char **argv) {
    CLI::App app;
    

    CLI11_PARSE(app,argc,argv);
    
    string fileLocation = std::format("{}/stored/passwords.txt", assets_dir); 
    
    setMasterPassword(fileLocation); 

    json data = readFileAsJSON(fileLocation);
    cout << data << std::endl; 


    return 0;
}

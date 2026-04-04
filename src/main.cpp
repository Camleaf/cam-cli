#include "iostream"
#include <CLI11.hpp>
#include "pw-man/manager.h"
#include <filesystem>
// maybe use like CLI11 or some other cli tool for parseing input

int main (int argc, char **argv) {
    CLI::App app;
    

    CLI11_PARSE(app,argc,argv);
    
    readFileAsJSON("word"); 

    return 0;
}

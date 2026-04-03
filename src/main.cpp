#include "iostream"
#include "pw-man/manager.h"
#include <CLI11.hpp>
#include <filesystem>
// maybe use like CLI11 or some other cli tool for parseing input

int main (int argc, char **argv) {
    CLI::App app;
    
    auto callback = [](int count){std::cout << "This was called " << count << " times";};
    app.add_flag_function("-c", callback, "Optional description");
   
    std::string option;
    app.add_option("posoption", option, "Optional description");

    CLI11_PARSE(app,argc,argv);
    
    std::cout << " " <<option << std::endl;        
    
    return 0;
}

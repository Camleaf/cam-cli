#include <CLI/App.hpp>
#include <ioHelper.h>
// maybe use like CLI11 or some other cli tool for parseing input

using namespace std;

int main (int argc, char **argv) {
    CLI::App app;
     
    auto configSeparator = app.add_option_group("configSeparator");
    
    string user;
    configSeparator->add_option("username", "the username of the desired password");
    
    CLI::App* subConfig = configSeparator ->add_subcommand("config", "configure settings");  
    
    configSeparator->require_option(1);
    
    bool deleteFlag, addFlag;
    app.add_flag("-d", deleteFlag,"");
    app.add_flag("-a", addFlag,"");
    
    bool masterPassFlag;
    auto flagGroup = subConfig->add_option_group("config_flag_group");
    flagGroup->add_flag("--master", masterPassFlag,"The flag to determine if the master password should be modified");
    flagGroup->require_option(1);

    CLI11_PARSE(app,argc,argv);
    
    // Check for config commands first
    
    if (app.got_subcommand(subConfig)){
        if (masterPassFlag){

        }

        return 0;
    }  

    // Do regular command next

    return 0;
}

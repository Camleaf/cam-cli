#include <CLI11.hpp>
#include "pw-man/manager.h"
#include "util/constants.h"
// maybe use like CLI11 or some other cli tool for parseing input

using namespace std;

int main (int argc, char **argv) {
    CLI::App app;
    
    CLI::App* subGet = app.add_subcommand("get", "gets passwords from the manager");
    CLI::App* subModify = app.add_subcommand("modify", "add and update, or delete passwords");
    CLI::App* subConfig = app.add_subcommand("config", "configure password caching, master password");
    
    subGet->add_option("username","the username of the desired password");

    bool modify_deleteFlag;
    subModify->add_flag("-d", modify_deleteFlag, "a flag to determine if a password should be deleted");
    subModify->add_option("username", "the username of a stored password");
    
    auto flagGroup = subConfig->add_option_group("config_flag_group");
    flagGroup->add_flag("--master", setMasterPassword, "The flag to determine if the master password should be modified");
    flagGroup->add_flag("--cache");
    flagGroup->add_flag("--nocache");
    flagGroup->require_option(1);

    CLI11_PARSE(app,argc,argv);

    return 0;
}

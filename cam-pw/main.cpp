#include <CLI/App.hpp>

using namespace std;


int main (int argc, char **argv) {
    CLI::App app;
    
    
    CLI::App* subCreate = app.add_subcommand("create","creates an ssh key and stores it locally");
    //subModify->add_option("username", "the username of a stored password");
    CLI::App* subLoad = app.add_subcommand("load", "loads an ssh key from local disk");

    CLI11_PARSE(app,argc,argv);

    if (app.got_subcommand(subCreate)){
        // No options on that subcommand for now just do default behaviour
    } else if (app.got_subcommand(subLoad)){
    }

    return 0;    
}

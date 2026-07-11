#include <CLI/App.hpp>
#include <ioHelper.h>
#include <extLoad.h>
#include <stateManager.h>
#include <encHelper.h>
#include <gpgme++/global.h>
// maybe use like CLI11 or some other cli tool for parseing input

using namespace std;

int main (int argc, char **argv) {
    CLI::App app;
    GpgME::initializeLibrary(); 
    
    CLI11_PARSE(app,argc,argv);
    
    
    std::string vef;
    if (get_valid_input("enter pass", vef, is_key_master)){
        std::cout << "pass verified " << endl;
    } else {
        std::cout << "pass incorrect" << endl;
    }
    
    
    std::string service,user,pass;

    get_valid_input("enter service: ", service);
    get_valid_input("enter username: ", user);
    get_valid_input("enter pass: ",pass);

    std::string enc_pass;
    
    gpg_encrypt(vef,pass,enc_pass);
    
    load_disk(loaded_data);
    add_password(service,user,enc_pass);
    

    std::string inpt;

    get_valid_input("enter service to query: ",inpt);
    
    std::vector<serviceUser> x;
    query_by_service(x,inpt);
    outputQuery(vef,x);

    return 0;
}

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

    std::string master_key, enc_pass;
    prompt_for_master(master_key);

    gpg_encrypt(master_key,pass,enc_pass);
    add_password(service,user,enc_pass);
    
    std::string enc_pass2,dec_pass;
    query_password(service,user,enc_pass2);
    std::cout << enc_pass2 << std::endl;
    
    gpg_decrypt(master_key, enc_pass2, dec_pass);
    std::cout << dec_pass << std::endl;
    

    return 0;
}

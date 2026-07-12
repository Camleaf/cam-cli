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
   

    std::string service,username, query = "";
    CLI::App* subAdd = app.add_subcommand("add");
    subAdd->add_option("service",service)->required(true);
    subAdd->add_option("user",username)->required(true);

    CLI::App* subRemove = app.add_subcommand("remove");
    subRemove->add_option("service",service)->required(true);
    subRemove->add_option("user",username)->required(true);
    
    CLI::App* subGet = app.add_subcommand("get");
    subGet->add_option("service",service)->required(true);
    subGet->add_option("user",username)->required(true);

    CLI::App* subList = app.add_subcommand("list");

    auto userModeFlag = subList->add_flag("-u");
    auto decryptFlag = subList->add_flag("-x");
    subList->add_option("query",query);
    



    CLI11_PARSE(app,argc,argv);
    

    std::vector<serviceUser> x;
    std::string master_key, pass, enc_pass = "";
    load_disk(loaded_data);
    if (subAdd->parsed()){
        prompt_for_master(master_key);
        get_valid_input("Enter password: ", pass);
        gpg_encrypt(master_key,pass,enc_pass);
        add_password(service,username,enc_pass);
        wipe_n_lines(1);
        cout << "Added user`" << username << "`to service `" << service <<"`" << endl;
    } else if (subRemove->parsed()){
        prompt_for_master(master_key);
        delete_password(service,username);
        cout << "Removed user`" << username << "` from service `" << service <<"`" << endl;
    } else if (subGet->parsed()){
        prompt_for_master(master_key);
        query_password(service,username,enc_pass);
        gpg_decrypt(master_key,enc_pass,pass);
        formatLine(service,username,pass,{15,25,15});
    } else if (subList->parsed()){
         
        if (!query.empty()){
            if (userModeFlag->count()){
                query_by_username(x, query);
            } else {
                query_by_service(x, query);
            }
        } else {
            query_all(x);
        }        

        if (decryptFlag->count()){
            prompt_for_master(master_key);
        }

        outputQuery(x,master_key);
    } else {
        query_all(x);
        outputQuery(x);
    }

    return 0;
}

#include "backendInterface.h"
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
    
    // firebase_key_update, master_key_update under config
    bool backend_key_update, master_key_update;
    CLI::App* config = app.add_subcommand("config");
    auto configGroup = config->add_option_group("configGroup","group with various config flag options");
    configGroup->add_flag("backend",backend_key_update,"Flag to indicate that the backend key is to be updated");
    configGroup->add_flag("master",master_key_update,"Flag to indicate that the master key is to be updated NOT IMPLEMENTED");
    configGroup->require_option(1);

    bool backend_pull, backend_push;
    CLI::App* backend = app.add_subcommand("backend");
    auto backendGroup = config->add_option_group("configGroup","group with various config flag options");
    backendGroup->add_flag("pull",backend_pull,"Flag to indicate that password data is to be pulled from the backend");
    backendGroup->add_flag("push",backend_push,"Flag to indicate that password data is to be pushed to the backend");
    backendGroup->require_option(1);

    CLI11_PARSE(app,argc,argv);
    

    std::vector<serviceUser> x;
    std::string master_key, pass, enc_pass = "";
    load_disk(loaded_data);
    if (subAdd->parsed()){ // add key
        prompt_for_master(master_key);
        get_valid_input("Enter password: ", pass);
        gpg_encrypt(master_key,pass,enc_pass);
        add_password(service,username,enc_pass);
        wipe_n_lines(1);
        cout << "Added user`" << username << "`to service `" << service <<"`" << endl;


    } else if (subRemove->parsed()){ // remove key
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


    } else if (config->parsed()) {
        
        if (master_key_update){
            cout << "Master key update not implemented" << endl;
        } else if (backend_key_update){
            prompt_for_master(master_key);
            get_valid_input("Enter new backend key: ",pass);
            gpg_encrypt(master_key,pass,enc_pass);
            write_backend_key_disk(enc_pass); 
        }


    } else if (backend->parsed()){ // push and pull to backend
        if (backend_pull){ // pull and load on local disk
            prompt_for_master(master_key);
            load_backend_key_disk(enc_pass);
            gpg_decrypt(master_key,enc_pass,pass);
            if (load_backend(loaded_data, pass)){
                return 1; // We don't want to overwrite local if there is an issue grabbing the data.
            };
            write_disk(loaded_data);
    } else if (backend_push){ // push and store on backend
            prompt_for_master(master_key);
            load_backend_key_disk(enc_pass);
            gpg_decrypt(master_key,enc_pass,pass);
            std::string choice;
            get_input_option("Merge or overwrite data on backend? (merge/overwrite)",choice,{"m","o"});
            store_backend(loaded_data, pass,(choice=="m")?0:1);
        }

    
    } else {
        query_all(x);
        outputQuery(x);
    }

    return 0;
}

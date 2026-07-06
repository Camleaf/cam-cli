#include <nlohmann/json_fwd.hpp>
#include <extLoad.h>
#include <fstream>
#include <nlohmann/json.hpp>
#include <filesystem>
#include <iostream>

int pass_create_user_disk(string user, string encrypted_pat){
    const string filename = string(local_directory);
    

    // add filedata
    map<string,string> data_map;
    data_map["pat"] = encrypted_pat;
    nlohmann::json json_data = data_map;

    filesystem::create_directories(filesystem::path(string(local_directory) + "key/"));

    ofstream f(filename + "key/" + user);    
    f << json_data.dump();
    f.close();

    // add config 
    map<string,string> cfg_map;
    cfg_map["mode"] = "pat";
    nlohmann::json json_cfg = cfg_map;

    filesystem::create_directories(filesystem::path(string(local_directory) + "cfg/"));

    ofstream cfg_f(filename + "cfg/" + user);
    cfg_f << json_cfg.dump();
    cfg_f.close();

    return 0;
}


int pass_load_user_disk(string user, string &encrypted_pat){
    const string filename = string(local_directory) + "key/" + user;
    if (!pass_exists_disk(user)){
        cout << "User " << user << " not found" << endl;
        return 1;
    }
    
    ifstream f;
    f.open(filename);
    
    std::stringstream strStream;
    strStream << f.rdbuf();
    string fdata = strStream.str();

    f.close();

    map<string,string> data_map = nlohmann::json::parse(fdata);
    
    encrypted_pat = data_map["pat"];
    
    return 0;
}




int pass_exists_disk(string user){
    return file_exists_disk(string(local_directory)+"key/"+user) && 
        file_exists_disk(string(local_directory)+"cfg/"+user);
}

int file_exists_disk(string filename){
    return ifstream(filename).good();
}

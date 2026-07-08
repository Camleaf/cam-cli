#include <nlohmann/json_fwd.hpp>
#include <extLoad.h>
#include <fstream>
#include <nlohmann/json.hpp>
#include <filesystem>
#include <iostream>
#include <stateManager.h>

int pass_create_disk(string name, string encrypted_pass){

    return 0;
}


int pass_load_disk(string name, string &encrypted_pass){
    
    return 0;
}

int pass_destroy_disk(string name);


int pass_exists_disk(string name){
    return 0;
}

int file_exists_disk(string filename){
    return ifstream(filename).good();
}


int load_disk(json_data &enc_json){
    if (!file_exists_disk(kDiskLoc)){
        // create empty json file
        std::ofstream outfile (kDiskLoc);
        outfile << "{}";
        outfile.close();
    }

    std::ifstream inStream(kDiskLoc);
    nlohmann::json data;
    try {
        data = nlohmann::json::parse(inStream);
    } catch (nlohmann::json::parse_error e) {
        cout << e.what() << endl << endl;
        cout << "cam-cli: Your password document has been modified externally and the JSON structure has been corrupted, you can fix it manually at "
            << kDiskLoc << endl;
    }
    
    enc_json = data.get<json_data>();
    return 0;
}


int write_disk(json_data &enc_json){
    nlohmann::json data = enc_json;
    std::ofstream outfile (kDiskLoc);

    outfile << data.dump();
    return 0;
}

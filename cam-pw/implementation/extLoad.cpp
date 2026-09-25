#include "state.h"
#include <nlohmann/json_fwd.hpp>
#include <extLoad.h>
#include <fstream>
#include <nlohmann/json.hpp>
#include <iostream>
#include <stateManager.h>
#include <encHelper.h>
#include <ioHelper.h>


int file_exists_disk(std::string filename){
    return std::ifstream(filename).good();
}


int load_disk(json_data &enc_json){
    if (!file_exists_disk(kDiskLoc)){
        // create empty json file
        std::filesystem::create_directories(std::filesystem::path(kParentLoc));
        std::ofstream outfile (kDiskLoc);
        outfile << "{}";
        outfile.close();
    }

    std::ifstream inStream(kDiskLoc);
    nlohmann::json data;
    try {
        data = nlohmann::json::parse(inStream);
    } catch (nlohmann::json::parse_error e) {
        std::cout << e.what() << std::endl << std::endl;
        std::cout << "cam-cli: Your password document has been modified externally and the JSON structure has been corrupted, you can fix it manually at "
            << kDiskLoc << std::endl;
    }
    
    enc_json = data.get<json_data>();
    return 0;
}


int write_disk(json_data enc_json){
     if (!file_exists_disk(kDiskLoc)){
        std::filesystem::create_directories(std::filesystem::path(kParentLoc));
    }
    nlohmann::json data = enc_json;
    std::ofstream outfile (kDiskLoc);

    outfile << data.dump();
    return 0;
}


int write_master_key_disk(std::string key){
    load_disk(loaded_data);

    if (loaded_data.size() != 0){ // encrypted data is already populated
        // if existing salt doesn't exist, add prompt to overwrite.
        // if existing hash doesn;t exist, add password prompt for old password add warning saying that verification won't exist, and ask if willing to risk corrupt during password encryption transfer, or just do overwrite.
        // if both exist, then same process as above, but only show the risky options if password fails.
        // the transfer must manually decrypt every single password with old password then re-encrypt with new one
    
        //return 1; // remove once block implemented
    }
    
    std::string salt = random_string(4);
    std::string hash;

    generateHash(key+salt,hash);

    std::ofstream hashFile(kHashLoc, std::ios::out | std::ios::trunc); // clear files
    std::ofstream saltFile(kSaltLoc, std::ios::out | std::ios::trunc);

    hashFile << hash;
    saltFile << salt;

    hashFile.close();
    saltFile.close();
    
    load_disk(loaded_data);
    return 0;
}


bool is_key_master(std::string key){
    std::string salt, hash, challenge;

    std::ifstream saltIn(kSaltLoc);
    std::ifstream hashIn(kHashLoc);

    std::getline(saltIn,salt);
    std::getline(hashIn,hash);
    generateHash(key+salt,challenge);

    saltIn.close();
    hashIn.close();

    if (challenge == hash){
        return true;
    }

    return false;
}



int load_backend_key_disk(std::string &enc_backend_key){
    
    std::ifstream bkIn(kBackendKeyLoc);
    std::getline(bkIn,enc_backend_key);
    bkIn.close();
    
    return 0;

};

int write_backend_key_disk(std::string enc_backend_key){
    
    std::ofstream bkFile(kBackendKeyLoc, std::ios::out | std::ios::trunc); // clear file
    bkFile << enc_backend_key; 
    bkFile.close();
    
    return 0;   
};

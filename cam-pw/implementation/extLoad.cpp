#include <nlohmann/json_fwd.hpp>
#include <extLoad.h>
#include <fstream>
#include <nlohmann/json.hpp>
#include <iostream>
#include <stateManager.h>
#include <encHelper.h>
#include <ioHelper.h>


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


int write_disk(json_data enc_json){
    nlohmann::json data = enc_json;
    std::ofstream outfile (kDiskLoc);

    outfile << data.dump();
    return 0;
}


int write_master_key_disk(std::string key){
    json_data enc_json;
    load_disk(enc_json);

    if (enc_json.size() != 0){ // encrypted data is already populated
        // if existing salt doesn't exist, add prompt to overwrite.
        // if existing hash doesn;t exist, add password prompt for old password add warning saying that verification won't exist, and ask if willing to risk corrupt during password encryption transfer, or just do overwrite.
        // if both exist, then same process as above, but only show the risky options if password fails.
        // the transfer must manually decrypt every single password with old password then re-encrypt with new one
    
        return 1; // remove once block implemented
    }
    
    std::string salt = random_string(4);
    std::string hash;

    generateHash(key+salt,hash);

    std::ofstream hashFile(kHashLoc);
    std::ofstream saltFile(kSaltLoc);

    hashFile << hash;
    saltFile << salt;
    return 0;
}


bool is_key_master(std::string key){
    std::string salt, hash, challenge;

    std::ifstream saltIn(kSaltLoc);
    std::ifstream hashIn(kHashLoc);

    std::getline(saltIn,salt);
    std::getline(hashIn,hash);
    generateHash(hash+salt,challenge);

    if (challenge == hash){
        return true;
    }

    return false;
}

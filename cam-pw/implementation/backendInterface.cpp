#include <backendInterface.h>
#include <cpr/cpr.h>
#include <iostream>
#include <nlohmann/json.hpp>


using json = nlohmann::json;





int load_backend(json_data &enc_json, std::string pw){
    
    json content = {
        {"password", pw},
    };

    cpr::Response r = cpr::Post(
        cpr::Url{kWebAddress+"/retrieve"},
        cpr::Body{content.dump()},
        cpr::Header{{"Content-Type","application/json"}}        
    );

    if (!r.status_code == 200){
        return 1;
    }

    nlohmann::json data;
    try {
        data = nlohmann::json::parse(r.text);
    } catch (nlohmann::json::parse_error e) {
        std::cout << e.what() << std::endl << std::endl;
        std::cout << "cam-cli: Your password document has been modified externally and the JSON structure has been corrupted, this is an issue on the backend" << std::endl;
    }
    
    enc_json = data.get<json_data>();
    return 0;
};


int store_backend(json_data enc_json, std::string pw, bool prune){

    json content;
    content["passwordSubmission"]["password"] = pw;
    content["data"]["content"] = enc_json;
    content["data"]["mode"] = prune;

    cpr::Response r = cpr::Post(
        cpr::Url{kWebAddress+"/update"},
        cpr::Body{content.dump()},
        cpr::Header{{"Content-Type","application/json"}}        
    );

    if (r.status_code != 200){
        std::cout << r.text << std::endl;
        std::cout << r.status_line << std::endl;
        return 1;
    }
    return 0;
};

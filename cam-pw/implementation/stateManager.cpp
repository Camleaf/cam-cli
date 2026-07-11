#include "encHelper.h"
#include "ioHelper.h"
#include <iostream>
#include <queue>
#include <stateManager.h>
#include <extLoad.h>
#include <vector>
#include <rapidfuzz/fuzz.hpp>
#include <state.h>

 
bool compareScore(const serviceUser r1, const serviceUser r2) { return r1.queryScore > r2.queryScore; }





// If search
int query_by_service(std::vector<serviceUser> &ordered_query_result, std::string service){
    load_disk(loaded_data);
    
    // Use fuzzy finder to get best "matches".
    // Will have a match cutoff
    ordered_query_result.clear();
    

    for (json_data::iterator it = loaded_data.begin(); it != loaded_data.end(); ++it) {
        double score = rapidfuzz::fuzz::token_sort_ratio(service,it->first);
        
        if (score < 40) continue;
        
        service_group x = it->second;
        
        for (service_group::iterator it2 = x.begin(); it2 != x.end(); ++it2){
            ordered_query_result.push_back({
                score,
                it->first,
                it2->first,
                it2->second
            });
        }    
        
    }
   
    std::sort(ordered_query_result.begin(),ordered_query_result.end(),compareScore);

    return 0;
}



// Get-All version
int query_all(std::vector<serviceUser> &ordered_query_result){
    
    load_disk(loaded_data);
    ordered_query_result.clear();

    for (json_data::iterator it = loaded_data.begin(); it != loaded_data.end(); ++it) {
        for (std::map<std::string,std::string>::iterator it2 = loaded_data[it->first].begin(); it2 != loaded_data[it->first].end(); ++it2){
                ordered_query_result.push_back({
                    100,
                    it->first,   // service
                    it2->first,          // name
                    it2->second         // password
                });
        }
    }

    return 0;
}

int query_by_username(std::vector<serviceUser> &ordered_query_result, std::string username){
    load_disk(loaded_data);
    
    // Use fuzzy finder to get best "matches".
    // Will have a match cutoff
    ordered_query_result.clear();
    

    for (json_data::iterator it = loaded_data.begin(); it != loaded_data.end(); ++it) {
        
        service_group x = it->second;
        
        for (service_group::iterator it2 = x.begin(); it2 != x.end(); ++it2){     
            double score = rapidfuzz::fuzz::token_sort_ratio(username,it2->first);
            
            if (score < 40) continue;

            ordered_query_result.push_back({
                score,
                it->first,
                it2->first,
                it2->second
            });
        }    
        
    }
   
    std::sort(ordered_query_result.begin(),ordered_query_result.end(),compareScore);

    return 0;

}



int query_password(std::string service, std::string username, std::string &enc_pass){
    load_disk(loaded_data);
     
    if (!loaded_data.contains(service)){
        std::cout << "Service `" << service << "` does not exist" << std::endl;
        return 1;
    } 

    if (!loaded_data[service].contains(username)){
        std::cout << "Username `" << username << "` does not exist in service `" << service  << "`" << std::endl;
        return 1;
    }
    
    enc_pass = loaded_data[service][username];
    
    return 0;
}


int prompt_for_master(std::string &master_key){
    std::string challenge;
    if (!get_valid_input("Enter master key: ", challenge, is_key_master)){
        std::cout << "Incorrect master key";
        return 1;
    }
    
    master_key = challenge;
    return 0;
}


int add_password(std::string service, std::string username, std::string enc_pass){
    
    if (!loaded_data.contains(service)){
        loaded_data.insert_or_assign(service,std::map<std::string,std::string>());
    } 

    if (loaded_data[service].contains(username)){
        // add overwrite code
        std::string opt;
        get_input_option("Overwrite existing password with service (y/n) `" + service + "` and user `" + username + "`", opt, {"y","n"});
        if (opt == "n"){
            return 1;
        }
    } 

    loaded_data[service].insert_or_assign(username,enc_pass);

    write_disk(loaded_data);        
    load_disk(loaded_data);
    return 0;
}



int delete_password(std::string service, std::string username){

    std::string temp;
    if (query_password(service,username, temp)){
        return 1;
    };

    // master pass not needed for delete operation however good for verification
    std::string master_key, enc_pass;
    prompt_for_master(master_key);



    if (loaded_data[service].size() == 1) {
        loaded_data.erase(service);
    } else {
        loaded_data[service].erase(username);
    }

    write_disk(loaded_data);
    load_disk(loaded_data);
    return 0;
}




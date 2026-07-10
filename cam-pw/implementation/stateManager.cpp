#include "encHelper.h"
#include "ioHelper.h"
#include <iostream>
#include <queue>
#include <stateManager.h>
#include <extLoad.h>
#include <vector>
#include <rapidfuzz/fuzz.hpp>


struct fuzzy_value_wrapper {
    std::string name;
    double score;
};



// If search
int query_data(std::vector<std::string> &ordered_query_result, std::string service){
    json_data enc_data;
    load_disk(enc_data);
    
    // Use fuzzy finder to get best "matches".
    // Will have a match cutoff
    struct fuzzScoreLessThan
    {
        bool operator()(const fuzzy_value_wrapper r1, const fuzzy_value_wrapper r2) const { return r1.score > r2.score; }
    };

    std::priority_queue<fuzzy_value_wrapper,std::vector<fuzzy_value_wrapper>, fuzzScoreLessThan> scorePQ;
    for (json_data::iterator it = enc_data.begin(); it != enc_data.end(); ++it) {
        double score = rapidfuzz::fuzz::token_sort_ratio(service,it->first);
        
        if (score < 70) continue;

        scorePQ.push(
            {
                it->first,
                score
            }
        );
    }

    ordered_query_result.clear();
    while (scorePQ.size()>0){
        ordered_query_result.push_back(scorePQ.top().name);
        scorePQ.pop();
    }

    return 0;
}



// Get-All version
int query_data(std::vector<std::string> &ordered_query_result){
    
    json_data enc_data;
    load_disk(enc_data);
    ordered_query_result.clear();

    for (json_data::iterator it = enc_data.begin(); it != enc_data.end(); ++it) {
        ordered_query_result.push_back(it->first);
    }

    return 0;
}



int query_password(std::string service, std::string username, std::string &enc_pass){
    json_data enc_data;
    load_disk(enc_data);
     
    if (!enc_data.contains(service)){
        std::cout << "Service `" << service << "` does not exist" << std::endl;
        return 1;
    } 

    if (!enc_data[service].contains(username)){
        std::cout << "Username `" << username << "` does not exist in service `" << service  << "`" << std::endl;
        return 1;
    }

    enc_pass = enc_data[service][username];
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
    json_data enc_data;
    load_disk(enc_data);
    
    if (!enc_data.contains(service)){
        enc_data.insert_or_assign(service,std::map<std::string,std::string>());
    } 

    if (enc_data[service].contains(username)){
        // add overwrite code
        std::string opt;
        get_input_option("Overwrite existing password with service (y/n) `" + service + "` and user `" + username + "`", opt, {"y","n"});
        if (opt == "n"){
            return 1;
        }
    } 

    enc_data[service].insert_or_assign(username,enc_pass);

    write_disk(enc_data);        
    return 0;
}



int delete_password(std::string service, std::string username){
    json_data enc_data;
    load_disk(enc_data);

    std::string temp;
    if (query_password(service,username, temp)){
        return 1;
    };

    // master pass not needed for delete operation however good for verification
    std::string master_key, enc_pass;
    prompt_for_master(master_key);



    if (enc_data[service].size() == 1) {
        enc_data.erase(service);
    } else {
        enc_data[service].erase(username);
    }

    write_disk(enc_data);
    return 0;
}

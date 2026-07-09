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


int query_service(string name){
    json_data enc_data;
    load_disk(enc_data);
    
    // Use fuzzy finder to get best "matches".
    // Will have a match cutoff
    struct fuzzScoreLessThan
    {
        bool operator()(const fuzzy_value_wrapper r1, const fuzzy_value_wrapper r2) const { return r1.score > r2.score; }
    };


    std::priority_queue<fuzzy_value_wrapper,vector<fuzzy_value_wrapper>, fuzzScoreLessThan> keys;
    for (json_data::iterator it = enc_data.begin(); it != enc_data.end(); ++it) {
        keys.push(
            {
                it->first,
                rapidfuzz::fuzz::token_sort_ratio(name,it->first)
            }
        );
    }





    return 0;
}



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
int query_data(std::vector<string> &ordered_query_result, string service){
    json_data enc_data;
    load_disk(enc_data);
    
    // Use fuzzy finder to get best "matches".
    // Will have a match cutoff
    struct fuzzScoreLessThan
    {
        bool operator()(const fuzzy_value_wrapper r1, const fuzzy_value_wrapper r2) const { return r1.score > r2.score; }
    };


    std::priority_queue<fuzzy_value_wrapper,vector<fuzzy_value_wrapper>, fuzzScoreLessThan> scorePQ;
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
int query_data(std::vector<string> &ordered_query_result){
    
    json_data enc_data;
    load_disk(enc_data);
    ordered_query_result.clear();

    for (json_data::iterator it = enc_data.begin(); it != enc_data.end(); ++it) {
        ordered_query_result.push_back(it->first);
    }

    return 0;
}




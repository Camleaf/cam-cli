#include <firestore.h>
#include <cpr/cpr.h>


int load_firebase(json_data &enc_json){
    cpr::Response r = cpr::Post(
        cpr::Url{kWebAddress+"/retrieve"},
        cpr::Payload{{}},
        cpr::Header{{"Content-Type","application/json"}}        
    );      
};


int write_firebase(json_data enc_json, bool prune){

};

#include <nlohmann/json_fwd.hpp>
#include <extLoad.h>
#include <fstream>
#include <nlohmann/json.hpp>
#include <filesystem>
#include <iostream>

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

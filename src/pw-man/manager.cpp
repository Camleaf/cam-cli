#include <fstream>
#include <filesystem>
#include "./manager.h"
// Start by making it without encryption, but add encryption later
// Is also possible that I can encrypt the JSON string before writing and decrypt when reading
// maybe later can add password caching for length of terminal session

// I want the format to look like this
// Will store in JSON

/*
printed to user on printall:
Website email/username   password
        email3/username2 password

stored as:

{
    [string Website]: {
        [string email/username]: password
    }
}

*/

using json = nlohmann::json;

json readFileAsJSON(std::string masterPassword){

    std::string command_string = "bash " + std::filesystem::path(assets_dir).string() + "/scripts/ensureFile.sh " + assets_dir;
    system(command_string.c_str());
    
    return json::parse("{}");
}


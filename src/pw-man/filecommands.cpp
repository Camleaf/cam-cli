#include <fstream>
#include <filesystem>
#include <iostream>
#include "./manager.h"

/* File to handle internal file interfacing
 *
 */



void runBashCommand(string commandName){
    std::string command_string = "bash " + std::filesystem::path(assets_dir).string() + "/scripts/" + commandName + ".sh " + assets_dir;
    system(command_string.c_str());

}

json readFileAsJSON(string fileLocation){
    
    // Run ensureFile bash script to make sure that the file exists before attempting to read from it
    runBashCommand("ensureFile");

    std::ifstream inStream(fileLocation);
    json data;
    try {
        data = json::parse(inStream);
    } catch (json::parse_error e) {
        cout << e.what() << endl << endl;
        cout << "cam-cli: Your password document has been modified externally and the JSON structure has been corrupted, you can fix it manually at "
            << fileLocation << endl;
    }
    return data;
}

void writeFileAsJSON(string fileLocation, json &data){
    std::string stringified = data.dump();

    std::ofstream outStream(fileLocation);

    if (!outStream.is_open()){
        cout << "cam-cli: Unable to write to password document. Changes not saved";
        return;
    }
    outStream << stringified;
}


void wipeFile(string fileLocation){ 
    runBashCommand("wipeFile");
}

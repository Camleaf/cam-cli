#include <string>

void create_locked_file(std::string password){
    system("gpg --batch --passphrase-file <(echo \"your_passphrase\") -c - > passphrase");

}

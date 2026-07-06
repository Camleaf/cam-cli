// Todo turn from proof of concept to working api

#include <gpgme++/global.h>
#include <iostream>
#include <vector>
#include <cstring> // For strdup
#include <gpgme++/context.h>
#include <gpgme++/data.h>
#include <gpgme++/encryptionresult.h>
#include <gpgme++/decryptionresult.h>
#include <gpgme++/interfaces/passphraseprovider.h>
#include <encHelper.h>

using namespace std;


class MyPassProvider : public GpgME::PassphraseProvider {
    public:
        string password = "";
        ~MyPassProvider() {}
        char * getPassphrase( const char * useridHint, const char * description, bool previousWasBad, bool & canceled ){
        return strdup(password.c_str());
    };
};


int gpg_encrypt(string password, string pat, string &encrypted_pat){
    // call GpgME::initializeLibrary(); somewhere before this 
    auto ctx = GpgME::Context::createForProtocol(GpgME::OpenPGP);
    if (!ctx) {
        cerr << "Unable to create GPG context" << endl;
        return 1;
    }
    
    ctx->setPinentryMode(GpgME::Context::PinentryLoopback);

    MyPassProvider p;
    p.password = password;
    ctx->setPassphraseProvider(&p);
    
    GpgME::Data input(pat.c_str(), pat.length(), false);
    GpgME::Data output;

    std::vector<GpgME::Key> recipients; 
    GpgME::EncryptionResult result = ctx->encrypt(recipients, input, output, GpgME::Context::AlwaysTrust);

    if (result.error()) {
        std::cerr << "Error: " << result.error().asString() << std::endl;
        return 1;
    }

    long long totalSize = output.seek(0,SEEK_END);
    std::vector<char> buffer(static_cast<size_t>(totalSize));
    output.seek(0, SEEK_SET);
    output.read(buffer.data(), buffer.size());

    std::vector<char> encrypted_vec = buffer;
    encrypted_pat = string(encrypted_vec.begin(), encrypted_vec.end());

    return 0;
}

int gpg_decrypt(string password, string encrypted_pat, string &pat){

    auto ctx = GpgME::Context::createForProtocol(GpgME::OpenPGP);
    if (!ctx) {
        cerr << "Unable to create GPG context" << endl;
        return 1;
    }
    
    ctx->setPinentryMode(GpgME::Context::PinentryLoopback);

    MyPassProvider p;
    p.password = password;
    ctx->setPassphraseProvider(&p);
    

    std::vector<char> encrypted_vec(encrypted_pat.begin(),encrypted_pat.end());

    GpgME::Data input2(encrypted_vec.data(), encrypted_vec.size(), false);
    GpgME::Data output2;

    // Decrypt
    GpgME::DecryptionResult result = ctx->decrypt(input2,output2);
      //  ctx->decrypt(input2, output2);

    if (result.error()) {
        std::cerr << "Decryption failed: " << result.error().asString() << std::endl;
        return 1;
    }

    // 3. Extract Plaintext
    long long totalSize = output2.seek(0, SEEK_END);
    output2.seek(0, SEEK_SET);

    std::vector<char> plaintext(static_cast<size_t>(totalSize));
    output2.read(plaintext.data(), plaintext.size());

    pat = string(plaintext.begin(), plaintext.end());
    
    return 0;
}

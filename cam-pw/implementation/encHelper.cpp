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


class keyProvider : public GpgME::PassphraseProvider {
    public:
        string key= "";
        int internalCount = 0;
        keyProvider(string key) {this->key=key;};
        ~keyProvider() {};
        char * getPassphrase( const char * useridHint, const char * description, bool previousWasBad, bool & canceled ){
            if (previousWasBad) {
                internalCount += 1;
                if (internalCount >= 3){
                    canceled = true;
                    return nullptr;
                }
            }
        return strdup(key.c_str());
    };
};


int gpg_encrypt(string key, string pass, string &encrypted_pass){
    // call GpgME::initializeLibrary(); somewhere before this 
    auto ctx = GpgME::Context::createForProtocol(GpgME::OpenPGP);
    if (!ctx) {
        cerr << "Unable to create GPG context" << endl;
        return 1;
    }
    
    ctx->setPinentryMode(GpgME::Context::PinentryLoopback);

    keyProvider p(key);
    ctx->setPassphraseProvider(&p);
    
    GpgME::Data input(pass.c_str(), pass.length(), false);
    GpgME::Data output;

    std::vector<GpgME::Key> recipients; 
    GpgME::EncryptionResult result = ctx->encrypt(
            recipients, 
            input, 
            output, 
            static_cast<GpgME::Context::EncryptionFlags>(
                GpgME::Context::AlwaysTrust | GpgME::Context::Symmetric
            )
    );

    if (result.error()) {
        std::cerr << "Error: " << result.error().asString() << std::endl;
        return 1;
    }

    long long totalSize = output.seek(0,SEEK_END);
    std::vector<char> buffer(static_cast<size_t>(totalSize));
    output.seek(0, SEEK_SET);
    output.read(buffer.data(), buffer.size());

    std::vector<char> encrypted_vec = buffer;
    encrypted_pass = string(encrypted_vec.begin(), encrypted_vec.end());

    return 0;
}

int gpg_decrypt(string key, string encrypted_pass, string &pass){

    auto ctx = GpgME::Context::createForProtocol(GpgME::OpenPGP);
    if (!ctx) {
        cerr << "Unable to create GPG context" << endl;
        return 1;
    }
    
    ctx->setPinentryMode(GpgME::Context::PinentryLoopback);

    keyProvider p(key);
    ctx->setPassphraseProvider(&p);
    

    std::vector<char> encrypted_vec(encrypted_pass.begin(),encrypted_pass.end());

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

    pass = string(plaintext.begin(), plaintext.end());
    
    return 0;
}

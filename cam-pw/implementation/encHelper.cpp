// Todo turn from proof of concept to working api

#include "extLoad.h"
#include "ioHelper.h"
#include <gpgme++/global.h>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring> // For strdup
#include <gpgme++/context.h>
#include <gpgme++/data.h>
#include <gpgme++/encryptionresult.h>
#include <gpgme++/decryptionresult.h>
#include <gpgme++/interfaces/passphraseprovider.h>
#include <encHelper.h>
#include <fstream>
#include <openssl/evp.h>

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
    encrypted_pass = binary_to_hex(string(encrypted_vec.begin(), encrypted_vec.end()));

    return 0;
}

int gpg_decrypt(string key, string encrypted_pass, string &pass){
    
    encrypted_pass = hex_to_binary(encrypted_pass);

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


int generateHash(std::string unhashed, std::string &hashed){
    EVP_MD_CTX* context = EVP_MD_CTX_new();
    const EVP_MD* algorithm = EVP_sha512();
    
    unsigned char hashResult[EVP_MAX_MD_SIZE];
    unsigned int hashLength = 0;

    // do the hashing
    EVP_DigestInit_ex(context, algorithm, nullptr);
    EVP_DigestUpdate(context, unhashed.c_str(), unhashed.length());
    EVP_DigestFinal_ex(context, hashResult, &hashLength);
    
    EVP_MD_CTX_free(context);

    // convert to readable hex string.
    std::stringstream ss;
    for(unsigned int i = 0; i < hashLength; ++i) {
        ss << std::hex <<  std::setfill('0') << std::setw(2) << static_cast<unsigned>(hashResult[i]);
    }
    
    hashed = ss.str();

    return 0;
}


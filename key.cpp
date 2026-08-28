#include <iostream>
#include <random>
#include <string>
#include <gmpxx.h>
#include "rsa.h"
#include "key.h"

using namespace std;

int main(){
    mpz_t p, q;
    mpz_init(p);
    mpz_init(q);

    // Finds two prime numbers that are relatively prime and saves them to p and q values
    findInitialPrimes(p, q);

    // Most commonly used public exponent
    mpz_class publicExponent = (1 << 16) + 1;

    // Creates the main RSA object that creates the public and private key for encryption
    RSA personRecepient = RSA(mpz_class(p), mpz_class(q), publicExponent);

    mpz_clear(p);
    mpz_clear(q);

    PublicKey pubKey = personRecepient.publicKey;

    // Saves the public key to the secondary RSA object which is only used for encrypting
    RSA personSender = RSA(pubKey);

    string message;
    cout << "Type something to encrypt: ";
    getline(cin, message);

    mpz_t msg, encryptedMessage, decryptedMessage;

    mpz_init(msg);
    mpz_init(encryptedMessage);
    mpz_init(decryptedMessage);

    // Converts the string to a mpz_t object
    stringToMpz(message, msg);

    // Encrypts the message using the public key
    personSender.encryptMessage(msg, encryptedMessage);

    gmp_printf("Encrypted Message: %Zd\n", encryptedMessage);

    // Decrypts the encrypted message using the private key
    personRecepient.decryptMessage(encryptedMessage, decryptedMessage);

    string text = mpzToString(decryptedMessage);

    cout << "Decrypted Message: " << text << "\n" << endl;

    mpz_clear(msg);
    mpz_clear(encryptedMessage);
    mpz_clear(decryptedMessage);
}
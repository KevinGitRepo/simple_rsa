#include "key.h"
#include <gmpxx.h>
#pragma once

class PublicKey;
class Vector2D;

class RSA{
    public:
    PublicKey publicKey;

    RSA (mpz_class& p, mpz_class& q){
        productPrimes = p * q;
        euler_totient = (p - 1) * (q - 1);
    }

    RSA (mpz_class p, mpz_class q, mpz_class& pubExponent) : publicExponent(pubExponent) {
        this->productPrimes = p * q;
        this->euler_totient = (p - 1) * (q - 1);
        this->publicKey = PublicKey(productPrimes, publicExponent);
        createPrivateKey();
    }

    RSA (PublicKey& pubKey) {
        this->publicKey = PublicKey(pubKey.key.nVal, pubKey.key.eVal);
    }

    ~RSA () {}

    void addPublicExponent (mpz_class& pubExponent) {
        this->publicExponent = pubExponent;
        this->publicKey = PublicKey(productPrimes, publicExponent);
        createPrivateKey();
    }

    void encryptMessage (mpz_t& message, mpz_t& result) {
        mpz_powm(result, message, publicKey.key.eVal.get_mpz_t(), publicKey.key.nVal.get_mpz_t());
    }

    void decryptMessage (mpz_t& message, mpz_t& result) {
        mpz_powm(result, message, privateKey.eVal.get_mpz_t(), publicKey.key.nVal.get_mpz_t());
    }

    private:
    mpz_class productPrimes;
    mpz_class euler_totient;
    Vector2D privateKey;
    mpz_class publicExponent;

    Vector2D findPrivateKey (mpz_t& key) {
        return Vector2D(euler_totient, mpz_class(key));
    }

    void createPrivateKey () {
        mpz_t key;
        mpz_init(key);
        // Finds the inverse of the Euler totient and the public exponent
        // This creates the private key
        mpz_invert(key, publicExponent.get_mpz_t(), euler_totient.get_mpz_t());
        this->privateKey = findPrivateKey(key);
        mpz_clear(key);
    }
};
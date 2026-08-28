#include <string>
#include <gmpxx.h>
#include <random>
#pragma once

using namespace std;

const int ALPHABET_SIZE = 26;

class Vector2D{
    public:
    mpz_class nVal;
    mpz_class eVal;

    Vector2D () {}

    Vector2D (mpz_class n, mpz_class e) : nVal(n), eVal(e) {}
};

class PublicKey {
    public:
    Vector2D key;

    PublicKey () {}

    PublicKey (mpz_class n, mpz_class e) : key(Vector2D(n, e)) {}
};

void generateRSAPrime (mpz_t prime, unsigned long bitLength, gmp_randstate_t& state) {
    int result = 0;
    while (result <= 0) {
        mpz_urandomb(prime, state, bitLength);

        mpz_setbit(prime, bitLength - 1);

        result = mpz_probab_prime_p(prime, 50);
    }
}

void findInitialPrimes (mpz_t p, mpz_t q) {
    gmp_randstate_t state;
    gmp_randinit_default(state);

    random_device r;

    gmp_randseed_ui(state, r());

    // 
    unsigned long bitLength = 2048;

    generateRSAPrime(p, bitLength, state);

    do {
        generateRSAPrime(q, bitLength, state);
    } while (mpz_cmp(p, q) == 0);
}

void stringToMpz (const std::string& str, mpz_t& result) {
    mpz_import(result, str.length(), 1, sizeof(char), 0, 0, str.data());
}

std::string mpzToString (mpz_t num) {
    size_t count = 0;
    void* buffer = mpz_export(NULL, &count, 1, sizeof(char), 0, 0, num);
    
    if (count == 0) return "";
    
    std::string str(reinterpret_cast<char*>(buffer), count);
    free(buffer);
    return str;
}

void encryptString (const std::string& str, mpz_t& message) {
    stringToMpz(str, message);
}
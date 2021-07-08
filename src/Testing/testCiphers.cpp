//! Unit Tests for MPAGSCipher Cipher Classes
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "CaesarCipher.hpp"
#include "VigenereCipher.hpp"
#include "PlayfairCipher.hpp"

bool testCipher( const Cipher& cipher, const CipherMode mode, const std::string& inputText, const std::string& outputText) {
    if (cipher.applyCipher(inputText, mode) == outputText) {
        return true;
    }
    else {
        return false;
    }
}

TEST_CASE("Caesar Cipher encryption", "[caesar]") {
  CaesarCipher cc{1};
  REQUIRE( testCipher(cc, CipherMode::Encrypt, "ABCDEF", "BCDEFG") );
}

TEST_CASE("Caesar Cipher decryption", "[caesar]") {
  CaesarCipher cc{1};
  REQUIRE( testCipher(cc, CipherMode::Decrypt, "BCDEFG", "ABCDEF") );
}

TEST_CASE("Playfair Cipher encryption", "[playfair]") {
  PlayfairCipher cc{"B"};
  REQUIRE( testCipher(cc, CipherMode::Encrypt, "ABCD", "CADE") );
}

TEST_CASE("Playfair Cipher decryption", "[playfair]") {
  PlayfairCipher cc{"B"};
  REQUIRE( testCipher(cc, CipherMode::Decrypt, "CADE", "ABCD") );
}

TEST_CASE("Vigenere Cipher encryption", "[vigenere]") {
  VigenereCipher cc{"B"};
  REQUIRE( testCipher(cc, CipherMode::Encrypt, "ABCDEF", "BCDEFG") );
}

TEST_CASE("Vigenere Cipher decryption", "[vigenere]") {
  VigenereCipher cc{"B"};
  REQUIRE( testCipher(cc, CipherMode::Decrypt, "BCDEFG", "ABCDEF") );
}
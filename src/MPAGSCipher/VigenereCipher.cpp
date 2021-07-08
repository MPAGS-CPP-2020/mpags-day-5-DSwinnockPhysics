// Standard library includes
#include <string>
#include <map>
#include <algorithm>
#include <iostream>

// Out project headers
#include "Alphabet.hpp"
#include "VigenereCipher.hpp"



VigenereCipher::VigenereCipher( const std::string& key )
{
  this->setKey( key );
}

void VigenereCipher::setKey( const std::string& key ) {
    // Store the key
    key_ = key;

    // Make sure the key is uppercase
    std::transform( std::begin(key_), std::end(key_), std::begin(key_), ::toupper );

    // Remove non-alphabet characters
    key_.erase( std::remove_if( std::begin(key_), std::end(key_), [](char c){ return !std::isalpha(c); } ), std::end(key_) );

    // Check if the key is empty and replace with default if so
    if ( key_.empty() ) {
        key_ = "A";
    }

    // loop over the key
    for ( std::string::size_type i{0}; i < key_.size(); ++i ) {

        // Find the letter position in the alphabet
        Alphabet::AlphabetSize letterPosition {Alphabet::alphabet.find(key_[i])};

        // Create a CaesarCipher using this position as a key
        CaesarCipher cipher { letterPosition };

        // Insert a std::pair of the letter and CaesarCipher into the lookup
        std::pair<char,CaesarCipher> keyCaesarPair {key_[i],cipher};
        charLookup_.insert(keyCaesarPair);
    }



}

std::string VigenereCipher::applyCipher( const std::string& inputText, const CipherMode cipherMode ) const {
    // Make output text variable
    std::string outputText{""};

    // For each letter in input:
    for ( std::string::size_type i{0}; i < inputText.size(); ++i) {

        // Find the corresponding letter in the key, repeating/truncating as required
        char keyLetterCurrent { key_[ i % key_.size() ] };

        // Find the Caesar cipher from the lookup
        auto cipherIter = charLookup_.find( keyLetterCurrent );
        auto currentCipher = (*cipherIter).second;

        // Run the (de)encryption
        std::string nextOutputLetter{""};
        std::string currentLetter{inputText[i]};
        nextOutputLetter = currentCipher.applyCipher( currentLetter, cipherMode );
        
        // Add the result to the output
        outputText+=nextOutputLetter;

    }

    return outputText;

}
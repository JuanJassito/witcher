#pragma once

#include "Words.hpp"
#include <string>

class Hangman {
public:
    Hangman(const std::string& wordsFile);
    bool guessLetter(char letter);
    std::string getGuessedWord() const;
    std::string getIncorrectLetters() const;
    int getLives() const;
    std::string getWordToGuess() const;

private:
    Word wordGenerator;
    std::string wordToGuess;
    std::string guessedWord;
    std::string incorrectLetters;
    int lives;
};

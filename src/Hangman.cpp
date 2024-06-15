#include "Hangman.hpp"
#include <cstdlib>
#include <ctime>
#include <stdexcept>
#include <cctype>

Hangman::Hangman(const std::string& wordsFile) : wordGenerator(wordsFile), lives(5) {
    wordToGuess = wordGenerator.generateWord();
    guessedWord = std::string(wordToGuess.length(), '_');
}

bool Hangman::guessLetter(char letter) {
    bool found = false;
    for (size_t i = 0; i < wordToGuess.length(); i++) {
        if (wordToGuess[i] == letter) {
            guessedWord[i] = letter;
            found = true;
        }
    }
    if (!found && incorrectLetters.find(letter) == std::string::npos) {
        incorrectLetters += letter;
        incorrectLetters += ' ';
        lives--;
    }
    return found;
}

std::string Hangman::getGuessedWord() const {
    return guessedWord;
}

std::string Hangman::getIncorrectLetters() const {
    return incorrectLetters;
}

int Hangman::getLives() const {
    return lives;
}

std::string Hangman::getWordToGuess() const {
    return wordToGuess;
}

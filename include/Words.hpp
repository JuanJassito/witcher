#pragma once

#include "Generator.hpp"

class Word {
private:
    textGenerator generator;

public:
    Word(const std::string& filename) : generator(filename) {}

    std::string generateWord() {
        return generator.readText();
    }

    size_t getWordLength(const std::string& word) const {
        return word.length();
    }
};


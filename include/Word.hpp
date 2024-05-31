#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <ctime>
#include <string>

class Word {
private:
    std::vector<std::string> words;

public:
    Word(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error: No se pudo abrir el archivo " << filename << std::endl;
            return;
        }

        std::string word;
        while (file >> word) {
            words.push_back(word);
        }

        file.close();
    }

    std::string getWord() const {
        if (words.empty()) {
            std::cerr << "Error: No hay palabras disponibles." << std::endl;
            return "";
        }

        // Configurar un generador de números aleatorios
        std::mt19937 rng(static_cast<unsigned int>(std::time(nullptr)));
        std::uniform_int_distribution<size_t> distribution(0, words.size() - 1);

        // Seleccionar una palabra aleatoria
        size_t index = distribution(rng);
        return words[index];
    }

    size_t getWordLength(const std::string& word) const {
        return word.length();
    }
};

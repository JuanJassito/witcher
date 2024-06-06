#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <ctime>
#include <string>

class textGenerator {
private:
    std::vector<std::string> reading;
public:
    textGenerator(const std::string& filename){
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error: No se pudo abrir el archivo " << filename << std::endl;
            return;
        }
        std::string word;
        while (file >> word) {
            reading.push_back(word);
        }
        file.close();
    }

    std::string readText(){
        if (reading.empty()) {
            std::cerr << "Error: No hay texto disponible." << std::endl;
            return "";
        }
        // Configurar un generador de números aleatorios
        std::mt19937 rng(static_cast<unsigned int>(std::time(nullptr)));
        std::uniform_int_distribution<size_t> distribution(0, reading.size() - 1);
        // Seleccionar una palabra aleatoria
        size_t index = distribution(rng);
        return reading[index];
    }

};

class numGenerator {
private:
    int min;
    int max;
    std::mt19937 rng;

public:
    numGenerator(int min, int max) : min(min), max(max) {
        if (min > max) {
            std::cerr << "Error: min debe ser menor o igual a max" << std::endl;
            throw std::invalid_argument("min debe ser menor o igual a max");
        }
        std::random_device rd;  // Obtiene un valor aleatorio de hardware
        rng = std::mt19937(rd());  // Inicializa el generador Mersenne Twister con el valor aleatorio
    }

    int generate() {
        std::uniform_int_distribution<int> distribution(min, max);
        return distribution(rng);
    }
};
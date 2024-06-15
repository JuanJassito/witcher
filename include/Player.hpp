#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class Player {
private:
    std::string name;
    int score;

public:
    Player(const std::string& playerName, int initialScore = 0)
        : name(playerName), score(initialScore) {}

    // Métodos para acceder y modificar el puntaje
    void setScore(int newScore) {
        score = newScore;
    }

    int getScore() const {
        return score;
    }

    // Método para guardar los datos del jugador en un archivo
    bool saveToFile(const std::string& filename) const {
        std::ofstream file(filename, std::ios::app); // Abre el archivo en modo append
        if (!file.is_open()) {
            std::cerr << "Error: No se pudo abrir el archivo " << filename << std::endl;
            return false;
        }

        file << name << "," << score << std::endl; // Guarda nombre y puntaje separados por coma

        file.close();
        return true;
    }

    // Método para cargar los datos de todos los jugadores desde un archivo
    static std::vector<Player> loadFromFile(const std::string& filename) {
        std::vector<Player> players;
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error: No se pudo abrir el archivo " << filename << std::endl;
            return players;
        }

        std::string line;
        while (std::getline(file, line)) {
            size_t commaPos = line.find(',');
            if (commaPos != std::string::npos) {
                std::string playerName = line.substr(0, commaPos);
                int playerScore = std::stoi(line.substr(commaPos + 1));
                players.emplace_back(playerName, playerScore);
            }
        }

        file.close();
        return players;
    }

    // Método para obtener el nombre del jugador
    std::string getName() const {
        return name;
    }

    // Método para comparar el nombre del jugador
    bool compareName(const std::string& playerName) const {
        return name == playerName;
    }
};

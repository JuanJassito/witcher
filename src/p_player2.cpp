#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include "Player.hpp"

// Función para cargar jugadores desde un archivo
std::vector<Player> loadPlayersFromFile(const std::string& filename) {
    std::vector<Player> players;
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string name;
        int score;
        while (file >> name >> score) {
            Player player(name, score);
            players.push_back(player);
        }
        file.close();
    } else {
        std::cerr << "Error: No se pudo abrir el archivo " << filename << std::endl;
    }
    return players;
}

// Función para guardar jugadores en un archivo
void savePlayersToFile(const std::string& filename, const std::vector<Player>& players) {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const auto& player : players) {
            file << player.getName() << " " << player.getScore() << std::endl;
        }
        file.close();
    } else {
        std::cerr << "Error: No se pudo abrir el archivo " << filename << " para escritura" << std::endl;
    }
}

int main() {
    // Cargar jugadores existentes desde el archivo
    std::vector<Player> players = loadPlayersFromFile("player_data.txt");

    // Crear la ventana de SFML
    sf::RenderWindow window(sf::VideoMode(800, 600), "Lista de Jugadores");

    // Fuente para los textos
    sf::Font font;
    if (!font.loadFromFile("./assets/fonts/Hamletornot.ttf")) {
        std::cerr << "Error: No se pudo cargar la fuente Hamletornot.ttf" << std::endl;
        return 1;
    }

    // Texto para mostrar los jugadores
    sf::Text playerText;
    playerText.setFont(font);
    playerText.setCharacterSize(24);
    playerText.setFillColor(sf::Color::White);
    playerText.setPosition(100.f, 100.f);

    // Texto y entrada para agregar un nuevo jugador
    sf::Text newPlayerPrompt;
    newPlayerPrompt.setFont(font);
    newPlayerPrompt.setCharacterSize(24);
    newPlayerPrompt.setFillColor(sf::Color::White);
    newPlayerPrompt.setPosition(100.f, 400.f);
    newPlayerPrompt.setString("Ingrese su nombre:");

    sf::String playerNameInput;
    sf::Text playerNameText;
    playerNameText.setFont(font);
    playerNameText.setCharacterSize(24);
    playerNameText.setFillColor(sf::Color::White);
    playerNameText.setPosition(100.f, 450.f);

    // Evento principal del bucle de SFML
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode < 128) {
                    if (event.text.unicode == '\b' && !playerNameInput.isEmpty()) {
                        playerNameInput.erase(playerNameInput.getSize() - 1);
                    } else if (event.text.unicode != '\b') {
                        playerNameInput += static_cast<char>(event.text.unicode);
                    }
                    playerNameText.setString(playerNameInput);
                }
            } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                // Crear un nuevo jugador con el nombre ingresado y puntaje inicial 0
                Player newPlayer(playerNameInput, 0);
                players.push_back(newPlayer);
                savePlayersToFile("player_data.txt", players);
                playerNameInput.clear();
                playerNameText.setString("");
            }
        }

        // Construir el texto con los nombres y puntajes de los jugadores
        std::string playersInfo;
        for (const auto& player : players) {
            playersInfo += "Nombre: " + player.getName() + ", Puntaje: " + std::to_string(player.getScore()) + "\n";
        }
        playerText.setString(playersInfo);

        // Limpiar la ventana y dibujar el texto
        window.clear();
        window.draw(playerText);
        window.draw(newPlayerPrompt);
        window.draw(playerNameText);
        window.display();
    }

    return 0;
}

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include "Player.hpp" // Clase Player que definimos anteriormente

int main() {
    // Crear jugadores y guardarlos
    Player player1("John Doe", 100);
    Player player2("Jane Smith", 150);
    Player player3("Alice", 200);

    player1.saveToFile("./docs/player_data.txt");
    player2.saveToFile("./docs/player_data.txt");
    player3.saveToFile("./docs/player_data.txt");

    // Cargar jugadores desde el archivo
    std::vector<Player> players = Player::loadFromFile("./docs/player_data.txt");

    // Configurar la ventana de SFML
    sf::RenderWindow window(sf::VideoMode(800, 600), "Datos de Jugadores");

    // Cargar fuente para texto
    sf::Font font;
    if (!font.loadFromFile("./assets/fonts/Hamletornot.ttf")) {
        std::cerr << "Error al cargar la fuente." << std::endl;
        return 1;
    }

    // Crear texto para mostrar los jugadores
    sf::Text playerText;
    playerText.setFont(font);
    playerText.setCharacterSize(24);
    playerText.setFillColor(sf::Color::White);

    // Variable para controlar qué jugador se muestra actualmente
    size_t currentPlayerIndex = 0;

    // Bucle principal de la ventana
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Cambiar al siguiente jugador cuando se presiona espacio
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
            }
        }

        // Mostrar datos del jugador actual en la ventana
        if (!players.empty()) {
            const Player& currentPlayer = players[currentPlayerIndex];
            std::string playerInfo = "Nombre: " + currentPlayer.getName() + "\n";
            playerInfo += "Puntaje: " + std::to_string(currentPlayer.getScore());

            playerText.setString(playerInfo);
        } else {
            playerText.setString("No hay jugadores para mostrar.");
        }

        // Limpiar la ventana
        window.clear();

        // Dibujar el texto en la ventana
        window.draw(playerText);

        // Mostrar la ventana
        window.display();
    }

    return 0;
}

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <Acussed.hpp>
#include <Generator.hpp>

int main() {
    numGenerator ng(0, 1);
    imageGenerator ig;

    // Crear una lista de objetos Accused
    std::vector<Accused> accusedList;
    for (int i = 0; i < 4; ++i) {
        accusedList.push_back(Accused(ng, ig));
    }

    sf::RenderWindow window(sf::VideoMode(800, 600), "Generador de Acusados");

    sf::Font font;
    if (!font.loadFromFile("./assets/fonts/Hamletornot.ttf")) {
        std::cerr << "Error: No se pudo cargar la fuente Hamletornot.ttf" << std::endl;
        return 1;
    }

    int currentAccusedIndex = 0;
    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Cambiar al siguiente acusado cada 20 segundos
        if (clock.getElapsedTime().asSeconds() >= 5.0f) {
            currentAccusedIndex = (currentAccusedIndex + 1) % accusedList.size();
            clock.restart();
        }

        Accused& currentAccused = accusedList[currentAccusedIndex];

        sf::Texture texture;
        if (!texture.loadFromFile(currentAccused.getImagePath())) {
            std::cerr << "Error: No se pudo cargar la imagen " << currentAccused.getImagePath() << std::endl;
            return 1;
        }

        sf::Sprite sprite;
        sprite.setTexture(texture);
        sprite.setPosition(100, 200);

        sf::Vector2u textureSize = texture.getSize();
        sprite.setScale(
            400.0f / textureSize.x,
            300.0f / textureSize.y
        );

        sf::Text nameText;
        nameText.setFont(font);
        nameText.setString("Name: " + currentAccused.getName());
        nameText.setCharacterSize(24);
        nameText.setFillColor(sf::Color::White);
        nameText.setPosition(100, 50);

        sf::Text genderText;
        genderText.setFont(font);
        genderText.setString("Gender: " + currentAccused.getGenderString());
        genderText.setCharacterSize(24);
        genderText.setFillColor(sf::Color::White);
        genderText.setPosition(100, 100);

        sf::Text reasonText;
        reasonText.setFont(font);
        reasonText.setString("Reason: " + currentAccused.getReason());
        reasonText.setCharacterSize(24);
        reasonText.setFillColor(sf::Color::White);
        reasonText.setPosition(100, 150);

        window.clear();
        window.draw(sprite);
        window.draw(nameText);
        window.draw(genderText);
        window.draw(reasonText);
        window.display();
    }

    return 0;
}

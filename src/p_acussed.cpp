#include <iostream>
#include <SFML/Graphics.hpp>
#include "Acussed.hpp"

int main() {
    numGenerator ng(0, 1);
    imageGenerator ig;

    Accused accused(ng, ig);

    sf::RenderWindow window(sf::VideoMode(800, 600), "Generador de Acusados");

    sf::Texture texture;
    if (!texture.loadFromFile(accused.getImagePath())) {
        std::cerr << "Error: No se pudo cargar la imagen " << accused.getImagePath() << std::endl;
        return 1;
    }

    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(100, 150);

    sf::Vector2u textureSize = texture.getSize();
    sprite.setScale(
        400.0f / textureSize.x,
        300.0f / textureSize.y
    );

    sf::Font font;
    if (!font.loadFromFile("./assets/fonts/Hamletornot.ttf")) {
        std::cerr << "Error: No se pudo cargar la fuente arial.ttf" << std::endl;
        return 1;
    }

    sf::Text nameText;
    nameText.setFont(font);
    nameText.setString("Nombre: " + accused.getName());
    nameText.setCharacterSize(24);
    nameText.setFillColor(sf::Color::White);
    nameText.setPosition(100, 50);

    sf::Text genderText;
    genderText.setFont(font);
    genderText.setString("Genero: " + accused.getGenderString());
    genderText.setCharacterSize(24);
    genderText.setFillColor(sf::Color::White);
    genderText.setPosition(100, 100);

    std::string reason = accused.getReason();
    sf::Text reasonText;
    reasonText.setFont(font);
    reasonText.setString(reason);
    reasonText.setCharacterSize(24);
    reasonText.setFillColor(sf::Color::White);
    reasonText.setPosition(100, 150);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(sprite);
        window.draw(nameText);
        window.draw(genderText);
        window.draw(reasonText);
        window.display();
    }

    return 0;
}
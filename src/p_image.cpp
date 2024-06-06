#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <ctime>
#include <string>
#include <filesystem>
#include <SFML/Graphics.hpp>
#include "Generator.hpp"

int main() {
    // Inicialización del generador de imágenes
    imageGenerator ig;
    // Inicialización del generador de números para género (0: hombre, 1: mujer)
    numGenerator genderGenerator(0, 1);
    int gender = genderGenerator.generate();

    std::cout << "Género generado: " << (gender == 0 ? "Hombre" : "Mujer") << std::endl;
    std::string imagePath = ig.generateImage(gender);
    std::cout << "Imagen generada: " << imagePath << std::endl;

    if (imagePath.empty()) {
        return 1; // Salir si no se ha generado ninguna imagen
    }

    // Crear una ventana SFML
    sf::RenderWindow window(sf::VideoMode(800, 600), "Generador de Imagenes");

    // Cargar la textura de la imagen
    sf::Texture texture;
    if (!texture.loadFromFile(imagePath)) {
        std::cerr << "Error: No se pudo cargar la imagen " << imagePath << std::endl;
        return 1;
    }

    // Crear un sprite para mostrar la imagen
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(10, 10); // Ajustar la posición si es necesario

    sf::Vector2u textureSize = texture.getSize();
    sprite.setScale(
        800.0f / textureSize.x, // Escalar para ajustar a la ventana
        600.0f / textureSize.y  // Escalar para ajustar a la ventana
    );

    // Bucle principal de la ventana
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(sprite);
        window.display();
    }

    return 0;
}

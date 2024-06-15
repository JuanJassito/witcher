#pragma once

#include <SFML/Graphics.hpp>
#include <Acussed.hpp>
#include "Generator.hpp"

class AccusedManager {
private:
    Accused accused;
    numGenerator& ng;
    imageGenerator& ig;
    sf::Font font;
    sf::Text nameText;
    sf::Text genderText;
    sf::Text reasonText;
    sf::Text witchText;
    sf::Sprite accusedSprite;

public:
    AccusedManager(numGenerator& ng, imageGenerator& ig) : ng(ng), ig(ig) {
        if (!font.loadFromFile("./assets/fonts/Hamletornot.ttf")) {
            std::cerr << "Error: No se pudo cargar la fuente Hamletornot.ttf" << std::endl;
        }

        // Generar datos del acusado
        int gender = ng.generate();
        int witch = ng.generate();
        std::string nameFile = (gender == 0) ? "./assets/text/m_names.txt" : "./assets/text/w_names.txt";
        textGenerator tg(nameFile);
        std::string name = tg.readText();
        std::string reasons = textGenerator("./assets/text/reasons.txt").readText();

        // Inicializar el objeto Accused con los datos generados
        accused = Accused(gender, witch, name, reasons);

        // Configurar el sprite del acusado
        std::string imagePath = ig.generateImage(gender); // Obtener la ruta de la imagen del acusado
        sf::Texture texture;
        if (!texture.loadFromFile(imagePath)) {
            std::cerr << "Error: No se pudo cargar la imagen " << imagePath << std::endl;
        }
        accusedSprite.setTexture(texture);
        accusedSprite.setScale(0.5f, 0.5f); // Escalado del sprite según sea necesario
        accusedSprite.setPosition(400, 200); // Posición del sprite en la ventana

        // Configurar los textos con datos del acusado
        nameText.setFont(font);
        nameText.setCharacterSize(24);
        nameText.setFillColor(sf::Color::White);
        nameText.setPosition(100, 50);

        genderText.setFont(font);
        genderText.setCharacterSize(24);
        genderText.setFillColor(sf::Color::White);
        genderText.setPosition(100, 100);

        reasonText.setFont(font);
        reasonText.setCharacterSize(24);
        reasonText.setFillColor(sf::Color::White);
        reasonText.setPosition(100, 150);

        witchText.setFont(font);
        witchText.setCharacterSize(24);
        witchText.setPosition(100, 200);
    }

    void update() {
        // Actualizar los textos con los datos del acusado actual
        nameText.setString("Name: " + accused.getName());
        genderText.setString("Gender: " + accused.getGenderString());
        reasonText.setString("Reason: " + accused.getReasons());

        // Configurar el color del texto de witch dependiendo del valor obtenido
        if (accused.getWitch() == 0) {
            witchText.setString("Witch: Yes");
            witchText.setFillColor(sf::Color::Red);
        } else if (accused.getWitch() == 1) {
            witchText.setString("Witch: No");
            witchText.setFillColor(sf::Color::Green);
        }
    }

    void render(sf::RenderWindow& window) {
        // Dibujar los textos y el sprite del acusado en la ventana
        window.draw(nameText);
        window.draw(genderText);
        window.draw(reasonText);
        window.draw(witchText);
        window.draw(accusedSprite); // Dibujar el sprite del acusado
    }

    Accused& getAccused() {
        return accused;
    }
};

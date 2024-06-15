#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <Acussed.hpp>
#include "Generator.hpp"

class AccusedManager {
private:
    std::vector<Accused> accusedList;
    numGenerator& ng;
    imageGenerator& ig;
    sf::Font font;
    int currentAccusedIndex;
    sf::Clock clock;
    bool displaySelectionPrompt;
    bool showAccused;
    sf::Clock showClock;

public:
    AccusedManager(numGenerator& ng, imageGenerator& ig) : ng(ng), ig(ig), currentAccusedIndex(0), displaySelectionPrompt(false), showAccused(false) {
        if (!font.loadFromFile("./assets/fonts/Hamletornot.ttf")) {
            std::cerr << "Error: No se pudo cargar la fuente Hamletornot.ttf" << std::endl;
        }

        // Crear una lista de objetos Accused
        for (int i = 0; i < 4; ++i) {
            accusedList.push_back(Accused(ng, ig));
        }
    }

    void update() {
        if (showAccused && showClock.getElapsedTime().asSeconds() >= 3.0f) {
            showAccused = false;
            displaySelectionPrompt = true;
        }

        if (!displaySelectionPrompt && !showAccused && clock.getElapsedTime().asSeconds() >= 2.0f) {
            currentAccusedIndex = (currentAccusedIndex + 1) % accusedList.size();
            if (currentAccusedIndex == 0) {
                displaySelectionPrompt = true;
            }
            clock.restart();
        }
    }

    void draw(sf::RenderWindow& window) {
        if (displaySelectionPrompt) {
            drawPrompt(window);
        } else if (showAccused) {
            drawAccused(window, accusedList[currentAccusedIndex]);
        } else {
            drawAccused(window, accusedList[currentAccusedIndex]);
        }
    }

    void drawAccused(sf::RenderWindow& window, const Accused& accused) {
        sf::Texture texture;
        if (!texture.loadFromFile(accused.getImagePath())) {
            std::cerr << "Error: No se pudo cargar la imagen " << accused.getImagePath() << std::endl;
            return;
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
        nameText.setString("Name: " + accused.getName());
        nameText.setCharacterSize(24);
        nameText.setFillColor(sf::Color::White);
        nameText.setPosition(100, 50);

        sf::Text genderText;
        genderText.setFont(font);
        genderText.setString("Gender: " + accused.getGenderString());
        genderText.setCharacterSize(24);
        genderText.setFillColor(sf::Color::White);
        genderText.setPosition(100, 100);

        sf::Text reasonText;
        reasonText.setFont(font);
        reasonText.setString("Reason: " + accused.getReason());
        reasonText.setCharacterSize(24);
        reasonText.setFillColor(sf::Color::White);
        reasonText.setPosition(100, 150);

        sf::Text witchText;
        witchText.setFont(font);
        witchText.setString(accused.getWitchString());
        witchText.setCharacterSize(24);
        witchText.setFillColor(sf::Color::White);
        witchText.setPosition(100, 200);

        window.draw(sprite);
        window.draw(nameText);
        window.draw(genderText);
        window.draw(reasonText);
        window.draw(witchText);
    }

    void drawPrompt(sf::RenderWindow& window) {
        sf::Text promptText;
        promptText.setFont(font);
        promptText.setString("Enter accused number (0-3): ");
        promptText.setCharacterSize(24);
        promptText.setFillColor(sf::Color::White);
        promptText.setPosition(100, 50);
        window.draw(promptText);
    }

    void setDisplaySelectionPrompt(bool value) {
        displaySelectionPrompt = value;
    }

    void setShowAccused(bool value) {
        showAccused = value;
        showClock.restart();
    }

    void setCurrentAccusedIndex(int index) {
        currentAccusedIndex = index;
    }

    const std::vector<Accused>& getAccusedList() const {
        return accusedList;
    }
};

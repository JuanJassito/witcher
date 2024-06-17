#ifndef GAME_PROTOTYPE_HPP
#define GAME_PROTOTYPE_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include <chrono>
#include "hanger.hpp"
#include <AcussedManager.hpp>

class GamePrototype {
public:
    GamePrototype();
    void run();

private:
    void initialize();
    void loadAssets();
    void setupSprites();
    void setupTexts();
    void resetGame();
    void gameLoop();
    void processEvents();
    void update();
    void render();
    void handleInput(char enteredChar);

    sf::RenderWindow window;
    sf::Font font;
    Hangman game;
    AccusedManager accusedManager;
    numGenerator ng;
    imageGenerator ig;

    sf::Texture texture;
    sf::Sprite accusedSprite;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Texture benchTexture;
    sf::Sprite benchSprite;
    sf::Texture treeTexture;
    sf::Sprite treeSprite;

    sf::Text nameText;
    sf::Text genderText;
    sf::Text reasonText;
    sf::Text witchText;
    sf::Text guessedWordText;
    sf::Text incorrectLettersText;
    sf::Text livesText;
    sf::Text resultText;
};

#endif // GAME_PROTOTYPE_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

enum GameState { MAIN_MENU, ENTER_NAME, DIFFICULTY_SELECTION, PLAYING, EXIT };

std::string playerName;
GameState currentState = MAIN_MENU;
std::string difficultyMessage;

void drawMainMenu(sf::RenderWindow& window, sf::Font& font);
void drawEnterNameMenu(sf::RenderWindow& window, sf::Font& font);
void drawDifficultyMenu(sf::RenderWindow& window, sf::Font& font);
void drawPlayingScreen(sf::RenderWindow& window, sf::Font& font);
void handleMainMenuEvent(sf::RenderWindow& window, sf::Event& event);
void handleEnterNameEvent(sf::RenderWindow& window, sf::Event& event);
void handleDifficultyMenuEvent(sf::RenderWindow& window, sf::Event& event);
void handlePlayingEvent(sf::RenderWindow& window, sf::Event& event);

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Menu System");
    sf::Font font;
    if (!font.loadFromFile("./assets/fonts/Hamletornot.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
        return -1;
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            switch (currentState) {
                case MAIN_MENU:
                    handleMainMenuEvent(window, event);
                    break;
                case ENTER_NAME:
                    handleEnterNameEvent(window, event);
                    break;
                case DIFFICULTY_SELECTION:
                    handleDifficultyMenuEvent(window, event);
                    break;
                case PLAYING:
                    handlePlayingEvent(window, event);
                    break;
                case EXIT:
                    window.close();
                    break;
            }
        }

        window.clear();
        switch (currentState) {
            case MAIN_MENU:
                drawMainMenu(window, font);
                break;
            case ENTER_NAME:
                drawEnterNameMenu(window, font);
                break;
            case DIFFICULTY_SELECTION:
                drawDifficultyMenu(window, font);
                break;
            case PLAYING:
                drawPlayingScreen(window, font);
                break;
            case EXIT:
                // Window will be closed in event handling
                break;
        }
        window.display();
    }

    return 0;
}

void drawMainMenu(sf::RenderWindow& window, sf::Font& font) {
    sf::Text playText("Play", font, 30);
    playText.setPosition(350, 200);

    sf::Text exitText("Exit", font, 30);
    exitText.setPosition(350, 300);

    window.draw(playText);
    window.draw(exitText);
}

void drawEnterNameMenu(sf::RenderWindow& window, sf::Font& font) {
    sf::Text namePrompt("Enter your name:", font, 30);
    namePrompt.setPosition(200, 200);

    sf::Text nameText(playerName, font, 30);
    nameText.setPosition(200, 300);

    window.draw(namePrompt);
    window.draw(nameText);
}

void drawDifficultyMenu(sf::RenderWindow& window, sf::Font& font) {
    sf::Text easyText("Easy", font, 30);
    easyText.setPosition(350, 200);

    sf::Text mediumText("Medium", font, 30);
    mediumText.setPosition(350, 300);

    sf::Text hardText("Hard", font, 30);
    hardText.setPosition(350, 400);

    sf::Text exitText("Exit", font, 30);
    exitText.setPosition(350, 500);

    window.draw(easyText);
    window.draw(mediumText);
    window.draw(hardText);
    window.draw(exitText);
}

void drawPlayingScreen(sf::RenderWindow& window, sf::Font& font) {
    sf::Text playerText(playerName, font, 24);
    playerText.setPosition(10, 10);
    window.draw(playerText);

    sf::Text messageText(difficultyMessage, font, 24);
    messageText.setPosition(10, 50);
    window.draw(messageText);

    sf::Text continueText("Press Enter to return to difficulty selection", font, 24);
    continueText.setPosition(10, 100);
    window.draw(continueText);
}

void handleMainMenuEvent(sf::RenderWindow& window, sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            if (mousePos.x >= 350 && mousePos.x <= 450) {
                if (mousePos.y >= 200 && mousePos.y <= 230) {
                    currentState = ENTER_NAME;
                } else if (mousePos.y >= 300 && mousePos.y <= 330) {
                    currentState = EXIT;
                }
            }
        }
    }
}

void handleEnterNameEvent(sf::RenderWindow& window, sf::Event& event) {
    if (event.type == sf::Event::TextEntered) {
        if (event.text.unicode == '\b') { // Handle backspace
            if (!playerName.empty())
                playerName.pop_back();
        } else if (event.text.unicode == '\r' || event.text.unicode == '\n') { // Handle enter
            currentState = DIFFICULTY_SELECTION;
        } else if (event.text.unicode < 128) { // Handle other ASCII characters
            playerName += static_cast<char>(event.text.unicode);
        }
    }
}

void handleDifficultyMenuEvent(sf::RenderWindow& window, sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            if (mousePos.x >= 350 && mousePos.x <= 450) {
                if (mousePos.y >= 200 && mousePos.y <= 230) {
                    difficultyMessage = "You selected Easy";
                    currentState = PLAYING;
                } else if (mousePos.y >= 300 && mousePos.y <= 330) {
                    difficultyMessage = "You selected Medium";
                    currentState = PLAYING;
                } else if (mousePos.y >= 400 && mousePos.y <= 430) {
                    difficultyMessage = "You selected Hard";
                    currentState = PLAYING;
                } else if (mousePos.y >= 500 && mousePos.y <= 530) {
                    currentState = MAIN_MENU;
                }
            }
        }
    }
}

void handlePlayingEvent(sf::RenderWindow& window, sf::Event& event) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
        currentState = DIFFICULTY_SELECTION;
    }
}

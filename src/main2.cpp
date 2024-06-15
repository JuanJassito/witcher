#include <SFML/Graphics.hpp>
#include <iostream>
#include <hanger.hpp>
#include <thread>
#include <chrono>

int main(int argc, char const *argv[]) {
    Hangman game("./assets/text/easy.txt");

    sf::RenderWindow window(sf::VideoMode(800, 600), "Hangman Game");

    sf::Font font;
    if (!font.loadFromFile("./assets/fonts/Salium.ttf")) {
        std::cerr << "Error loading font" << std::endl;
        return -1;
    }

    sf::Text guessedWordText(game.getGuessedWord(), font, 30);
    guessedWordText.setPosition(100, 100);

    sf::Text incorrectLettersText("Incorrect Letters: ", font, 30);
    incorrectLettersText.setPosition(100, 200);

    sf::Text livesText("Lives: " + std::to_string(game.getLives()), font, 30);
    livesText.setPosition(100, 300);

    bool gameOver = false;
    sf::Text resultText("", font, 28);
    resultText.setPosition(100, 400);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::TextEntered && !gameOver) {
                char enteredChar = static_cast<char>(event.text.unicode);
                if (isalpha(enteredChar)) {
                    enteredChar = tolower(enteredChar);
                    game.guessLetter(enteredChar);

                    guessedWordText.setString(game.getGuessedWord());
                    incorrectLettersText.setString("Incorrect Letters: " + game.getIncorrectLetters());
                    livesText.setString("Lives: " + std::to_string(game.getLives()));
                }
            }
        }

        window.clear();
        window.draw(guessedWordText);
        window.draw(incorrectLettersText);
        window.draw(livesText);

        if (!gameOver && (game.getGuessedWord() == game.getWordToGuess() || game.getLives() <= 0)) {
            gameOver = true;
            if (game.getGuessedWord() == game.getWordToGuess()) {
                resultText.setString("Congratulations! You guessed the word: " + game.getWordToGuess());
                std::cout << "Congratulations! You guessed the word: " << game.getWordToGuess() << std::endl;
            } else {
                resultText.setString("Game Over! The word was: " + game.getWordToGuess());
                std::cout << "Game Over! The word was: " << game.getWordToGuess() << std::endl;
            }
        }

        if (gameOver) {
            window.draw(resultText);
            window.display();
            std::this_thread::sleep_for(std::chrono::seconds(3));
            window.close();
        } else {
            window.display();
        }
    }

    return 0;
}

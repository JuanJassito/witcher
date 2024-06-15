#include <SFML/Graphics.hpp>
#include <iostream>
#include <hanger.hpp>
#include <thread>
#include <chrono>
#include <AcussedManager.hpp>

using namespace std;

int main(int argc, char const *argv[]){
// Crear la ventana de SFML
    sf::RenderWindow window(sf::VideoMode(800, 600), "GAME PROTOTYPE");

//hanger.hpp
    Hangman game("./assets/text/easy.txt"); //create teh game from hanger.hpp

//instances numGenerator and imageGenerator
    numGenerator ng(0, 1);  // Ejemplo de creación de numGenerator
    imageGenerator ig;      // Ejemplo de creación de imageGenerator

// Crear un objeto AccusedManager
    AccusedManager accusedManager(ng, ig);

// creation about sprite 
    sf::Texture texture;
    std::string imagePath = ig.generateImage(accusedManager.getAccused().getGender());
    if (!texture.loadFromFile(imagePath)) {
        std::cerr << "Error: No se pudo cargar la imagen del acusado desde " << imagePath << std::endl;
        return 1;
    }
    sf::Sprite accusedSprite(texture);
    accusedSprite.setScale(0.2f, 0.2f);  // Escalar el sprite si es necesario
    accusedSprite.setPosition(-50, 100);  // Ejemplo de posición fija

//fuente
    sf::Font font;
    if (!font.loadFromFile("./assets/fonts/Hamletornot.ttf")) {
        std::cerr << "Error loading font" << std::endl;
        return -1;
    }

//creacion de los datos del acusado
    sf::Text nameText;
    nameText.setFont(font);
    nameText.setCharacterSize(18);
    nameText.setFillColor(sf::Color::White);
    nameText.setString("Name: " + accusedManager.getAccused().getName());
    nameText.setPosition(400, 50);  // Posición fija para el nombre

    sf::Text genderText;
    genderText.setFont(font);
    genderText.setCharacterSize(18);
    genderText.setFillColor(sf::Color::White);
    genderText.setString("Gender: " + accusedManager.getAccused().getGenderString());
    genderText.setPosition(400, 100);  // Posición fija para el género

    sf::Text reasonText;
    reasonText.setFont(font);
    reasonText.setCharacterSize(18);
    reasonText.setFillColor(sf::Color::White);
    reasonText.setString("Reason: " + accusedManager.getAccused().getReasons());
    reasonText.setPosition(400, 150);  // Posición fija para la razón

    sf::Text witchText;
    witchText.setFont(font);
    witchText.setCharacterSize(18);
    witchText.setFillColor(sf::Color::White);
    witchText.setString("Witch: " + accusedManager.getAccused().getWitchString());
    witchText.setPosition(400, 200);  // Posición fija para el estatus de bruja

// crear las instancias del juego
    sf::Text guessedWordText(game.getGuessedWord(), font, 22);
    guessedWordText.setPosition(400, 400);

    sf::Text incorrectLettersText("Incorrect Letters: ", font, 22);
    incorrectLettersText.setPosition(400, 450);

    sf::Text livesText("Lives: " + std::to_string(game.getLives()), font, 22);
    livesText.setPosition(400, 500);

    bool gameOver = false;
    sf::Text resultText("", font, 30);
    resultText.setPosition(0, 0);

//bucle de la ventana sfml
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
        ///juego 
        window.draw(guessedWordText);
        window.draw(incorrectLettersText);
        window.draw(livesText);
        ///acusado
        window.draw(accusedSprite);
        window.draw(nameText);
        window.draw(genderText);
        window.draw(reasonText);
        window.draw(witchText);


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

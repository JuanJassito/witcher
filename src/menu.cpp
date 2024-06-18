#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <hanger.hpp>
#include <AcussedManager.hpp>


enum GameState { MAIN_MENU, ENTER_NAME, DIFFICULTY_SELECTION, PLAYING, EXIT };

std::string playerName;
GameState currentState = MAIN_MENU;
std::string difficultyMessage;
int diffucult;
int score;

void drawMainMenu(sf::RenderWindow& window, sf::Font& font);
void drawEnterNameMenu(sf::RenderWindow& window, sf::Font& font);
void drawDifficultyMenu(sf::RenderWindow& window, sf::Font& font);
void drawPlayingScreen(sf::RenderWindow& window, sf::Font& font);
void handleMainMenuEvent(sf::RenderWindow& window, sf::Event& event);
void handleEnterNameEvent(sf::RenderWindow& window, sf::Event& event);
void handleDifficultyMenuEvent(sf::RenderWindow& window, sf::Event& event);
void handlePlayingEvent(sf::RenderWindow& window, sf::Event& event);

int main() {
    sf::Music music;
    numGenerator nm(0,4);
    int mus = nm.generate();
    switch (mus)
    {
    case 0:
        music.openFromFile("./assets/sounds/b_de_bellako.ogg");
        break;
    case 1:
        music.openFromFile("./assets/sounds/crazy_forg.ogg");
        break;
    case 2:
        music.openFromFile("./assets/sounds/hey_brother.ogg");
        break;

    case 3:
        music.openFromFile("./assets/sounds/nueva_vida.ogg");
        break;

    case 4:
        music.openFromFile("./assets/sounds/Toothless.ogg");
        break;

    default:
        music.openFromFile("./assets/sounds/el_gavilan.ogg");
        break;
    }
    music.play();

    sf::RenderWindow window(sf::VideoMode(800, 600), "HANGMAN");
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
    sf::Text tittle("Hangman The Game", font, 50);
    tittle.setColor(sf::Color::Black);
    tittle.setPosition(150, 100);

    sf::Texture back;
    back.loadFromFile("./assets/images/elements/fondo_p.png");
    sf::Sprite bg(back);
    bg.setScale(0.4f, 0.4f);
    bg.setPosition(
        (window.getSize().x - bg.getGlobalBounds().width) / 2,
        (window.getSize().y - bg.getGlobalBounds().height) / 2
    );

    sf::Texture tree;
    tree.loadFromFile("./assets/images/elements/arbol.png");
    sf::Sprite tb(tree);
    tb.setScale(0.3f, 0.3f);
    tb.setPosition(-200, -50);


    
    sf::Text playText("Play", font, 30);
    playText.setColor(sf::Color::Black);
    playText.setPosition(350, 200);

    sf::Text exitText("Exit", font, 30);
    exitText.setColor(sf::Color::Red);
    exitText.setPosition(350, 300);

    window.draw(bg);
    window.draw(tb);
    window.draw(tittle);
    window.draw(playText);
    window.draw(exitText);
}

void drawEnterNameMenu(sf::RenderWindow& window, sf::Font& font) {
    sf::Text namePrompt("Enter your name:", font, 30);
    namePrompt.setFillColor(sf::Color::Black);
    namePrompt.setPosition(200, 200);

    sf::Text nameText(playerName, font, 30);
    nameText.setFillColor(sf::Color::Black);
    nameText.setPosition(200, 300);

    sf::Texture back;
    back.loadFromFile("./assets/images/elements/fondo_p.png");
    sf::Sprite bg(back);
    bg.setScale(0.4f, 0.4f);
    bg.setPosition(
        (window.getSize().x - bg.getGlobalBounds().width) / 2,
        (window.getSize().y - bg.getGlobalBounds().height) / 2
    );
    sf::Texture tree;
    tree.loadFromFile("./assets/images/elements/arbol.png");
    sf::Sprite tb(tree);
    tb.setScale(0.3f, 0.3f);
    tb.setPosition(-200, -50);

    window.draw(bg);
    window.draw(tb);
    window.draw(namePrompt);
    window.draw(nameText);
}

void drawDifficultyMenu(sf::RenderWindow& window, sf::Font& font) {
    sf::Text easyText("Easy", font, 30);
    easyText.setColor(sf::Color::Black);
    easyText.setPosition(350, 200);

    sf::Text mediumText("Medium", font, 30);
    mediumText.setColor(sf::Color::Black);
    mediumText.setPosition(350, 300);

    sf::Text hardText("Hard", font, 30);
    hardText.setColor(sf::Color::Black);
    hardText.setPosition(350, 400);

    sf::Text exitText("Exit", font, 30);
    exitText.setColor(sf::Color::Red);
    exitText.setPosition(350, 500);

    sf::Texture back;
    back.loadFromFile("./assets/images/elements/fondo_p.png");
    sf::Sprite bg(back);
    bg.setScale(0.4f, 0.4f);
    bg.setPosition(
        (window.getSize().x - bg.getGlobalBounds().width) / 2,
        (window.getSize().y - bg.getGlobalBounds().height) / 2
    );
    sf::Texture tree;
    tree.loadFromFile("./assets/images/elements/arbol.png");
    sf::Sprite tb(tree);
    tb.setScale(0.3f, 0.3f);
    tb.setPosition(-200, -50);

    window.draw(bg);
    window.draw(tb);
    window.draw(easyText);
    window.draw(mediumText);
    window.draw(hardText);
    window.draw(exitText);
}

void drawPlayingScreen(sf::RenderWindow& window, sf::Font& font) {
    std::string diff;
    if(diffucult==0){
        diff = "./assets/text/easy.txt";
    }else if(diffucult==1){
        diff = "./assets/text/medium.txt";
    }else if(diffucult==2){
        diff = "./assets/text/hard.txt";
    }

    sf::Text playerText(playerName, font, 28);
    playerText.setPosition(520, 500);
    playerText.setColor(sf::Color::Red);
    window.draw(playerText);

    std::string sscore = std::to_string(score);
    sf::Text sc(sscore, font, 30);
    sc.setPosition(520,535);
    sc.setColor(sf::Color::Red);
    window.draw(sc);

    // hanger.hpp

    Hangman game(diff); // crear el juego desde hanger.hpp

    // instances numGenerator and imageGenerator
    numGenerator ng(0, 1);  // Ejemplo de creación de numGenerator
    imageGenerator ig;      // Ejemplo de creación de imageGenerator

    // Crear un objeto AccusedManager
    AccusedManager accusedManager(ng, ig);

    // creation about sprite 
    sf::Texture texture;
    std::string imagePath = ig.generateImage(accusedManager.getAccused().getGender());
    if (!texture.loadFromFile(imagePath)) {
        std::cerr << "Error: No se pudo cargar la imagen del acusado desde " << imagePath << std::endl;
        return;
    }
    sf::Sprite accusedSprite(texture);
    accusedSprite.setScale(0.25f, 0.25f);  // Escalar el sprite si es necesario
    accusedSprite.setPosition(-100, 150);  // Ejemplo de posición fija

    // fondo
    sf::Texture back;
    back.loadFromFile("./assets/images/elements/fondo_p.png");
    sf::Sprite bg(back);
    bg.setScale(0.4f, 0.4f);
    bg.setPosition(
        (window.getSize().x - bg.getGlobalBounds().width) / 2,
        (window.getSize().y - bg.getGlobalBounds().height) / 2
    );

    // banquito
    sf::Texture sit;
    sit.loadFromFile("./assets/images/elements/banco.png");
    sf::Sprite bench(sit);
    bench.setScale(0.09f, 0.09f);
    bench.setPosition(70, 450);

    // arbol
    sf::Texture tree;
    tree.loadFromFile("./assets/images/elements/arbol.png");
    sf::Sprite tb(tree);
    tb.setScale(0.3f, 0.3f);
    tb.setPosition(-200, -50);

    // creacion de los datos del acusado
    sf::Text nameText;
    nameText.setFont(font);
    nameText.setCharacterSize(20);
    nameText.setFillColor(sf::Color::Black);
    nameText.setString("Name: " + accusedManager.getAccused().getName());
    nameText.setPosition(350, 50);  // Posición fija para el nombre

    sf::Text genderText;
    genderText.setFont(font);
    genderText.setCharacterSize(20);
    genderText.setFillColor(sf::Color::Black);
    genderText.setString("Gender: " + accusedManager.getAccused().getGenderString());
    genderText.setPosition(350, 100);  // Posición fija para el género

    sf::Text reasonText;
    reasonText.setFont(font);
    reasonText.setCharacterSize(20);
    reasonText.setFillColor(sf::Color::Black);
    reasonText.setString("Reason: " + accusedManager.getAccused().getReasons());
    reasonText.setPosition(350, 150);  // Posición fija para la razón

    sf::Text witchText;
    witchText.setFont(font);
    witchText.setCharacterSize(20);
    witchText.setFillColor(sf::Color::Black);
    witchText.setString("Witch: " + accusedManager.getAccused().getWitchString());
    witchText.setPosition(350, 200);  // Posición fija para el estatus de bruja

    // crear las instancias del juego
    sf::Text guessedWordText(game.getGuessedWord(), font, 22);
    guessedWordText.setFillColor(sf::Color::Black);
    guessedWordText.setPosition(350, 350);

    sf::Text incorrectLettersText("Incorrect Letters: ", font, 22);
    incorrectLettersText.setFillColor(sf::Color::Black);
    incorrectLettersText.setPosition(350, 400);

    sf::Text livesText("Lives: " + std::to_string(game.getLives()), font, 22);
    livesText.setFillColor(sf::Color::Black);
    livesText.setPosition(350, 450);

    sf::Text resultText("", font, 30);
    resultText.setFillColor(sf::Color::Red);
    resultText.setPosition(50, 250);

    while (window.isOpen() && game.getLives() > 0) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::TextEntered) {
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

        window.clear(sf::Color(161, 130, 98, 255));
        // fondo
        window.draw(bg);
        window.draw(tb);
        window.draw(bench);

        // juego 
        window.draw(guessedWordText);
        window.draw(incorrectLettersText);
        window.draw(livesText);

        // acusado
        window.draw(accusedSprite);
        window.draw(nameText);
        window.draw(genderText);
        window.draw(reasonText);
        window.draw(witchText);

        window.draw(playerText);
        window.draw(sc);

        if (game.getGuessedWord() == game.getWordToGuess()) {
            resultText.setString("Congratulations! You guessed the word: " + game.getWordToGuess());
            int multi = 10*(game.getLives());
            std::cout<<multi;
            
            if(accusedManager.getAccused().getWitch() == 0){
                std::cout<<accusedManager.getAccused().getWitch();
                score = score + 100;
            }else{
                std::cout<<accusedManager.getAccused().getWitch();
                score = score + 100 + multi;
                multi = 0;
            }
            window.draw(resultText);
            window.display();
            std::this_thread::sleep_for(std::chrono::seconds(3));
            break;
        }

        window.display();
    }

    if (game.getLives() <= 0) {
        resultText.setString("Game Over! The word was: " + game.getWordToGuess());
        window.draw(resultText);
        window.display();
        std::this_thread::sleep_for(std::chrono::seconds(3));
        //window.close();
        currentState = DIFFICULTY_SELECTION;
    }
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
                    diffucult = 0;
                    currentState = PLAYING;
                } else if (mousePos.y >= 300 && mousePos.y <= 330) {
                    difficultyMessage = "You selected Medium";
                    diffucult = 1;
                    currentState = PLAYING;
                } else if (mousePos.y >= 400 && mousePos.y <= 430) {
                    difficultyMessage = "You selected Hard";
                    currentState = PLAYING;
                    diffucult = 2;
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

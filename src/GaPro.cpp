#include <GaPro.hpp>

GamePrototype::GamePrototype()
    : window(sf::VideoMode(800, 650), "GAME PROTOTYPE"),
      game("./assets/text/easy.txt"),
      accusedManager(ng, ig),
      ng(0, 1),
      ig() {
    initialize();
}

void GamePrototype::initialize() {
    loadAssets();
    setupSprites();
    setupTexts();
}

void GamePrototype::loadAssets() {
    if (!font.loadFromFile("./assets/fonts/Hamletornot.ttf")) {
        std::cerr << "Error loading font" << std::endl;
        exit(-1);
    }

    backgroundTexture.loadFromFile("./assets/images/elements/fondo_p.png");
    benchTexture.loadFromFile("./assets/images/elements/banco.png");
    treeTexture.loadFromFile("./assets/images/elements/arbol.png");
}

void GamePrototype::setupSprites() {
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(0.4f, 0.4f);
    backgroundSprite.setPosition(
        (window.getSize().x - backgroundSprite.getGlobalBounds().width) / 2,
        (window.getSize().y - backgroundSprite.getGlobalBounds().height) / 2
    );

    benchSprite.setTexture(benchTexture);
    benchSprite.setScale(0.09f, 0.09f);
    benchSprite.setPosition(70, 450);

    treeSprite.setTexture(treeTexture);
    treeSprite.setScale(0.3f, 0.3f);
    treeSprite.setPosition(-200, -50);
}

void GamePrototype::setupTexts() {
    nameText.setFont(font);
    nameText.setCharacterSize(20);
    nameText.setFillColor(sf::Color::Black);

    genderText.setFont(font);
    genderText.setCharacterSize(20);
    genderText.setFillColor(sf::Color::Black);

    reasonText.setFont(font);
    reasonText.setCharacterSize(20);
    reasonText.setFillColor(sf::Color::Black);

    witchText.setFont(font);
    witchText.setCharacterSize(20);
    witchText.setFillColor(sf::Color::Black);

    guessedWordText.setFont(font);
    guessedWordText.setCharacterSize(22);
    guessedWordText.setFillColor(sf::Color::Black);
    guessedWordText.setPosition(350, 350);

    incorrectLettersText.setFont(font);
    incorrectLettersText.setCharacterSize(22);
    incorrectLettersText.setFillColor(sf::Color::Black);
    incorrectLettersText.setPosition(350, 400);

    livesText.setFont(font);
    livesText.setCharacterSize(22);
    livesText.setFillColor(sf::Color::Black);
    livesText.setPosition(350, 450);

    resultText.setFont(font);
    resultText.setCharacterSize(30);
    resultText.setFillColor(sf::Color::Red);
    resultText.setPosition(50, 250);
}

void GamePrototype::resetGame() {
    game = Hangman("./assets/text/easy.txt");
    accusedManager = AccusedManager(ng, ig);

    std::string imagePath = ig.generateImage(accusedManager.getAccused().getGender());
    if (!texture.loadFromFile(imagePath)) {
        std::cerr << "Error: No se pudo cargar la imagen del acusado desde " << imagePath << std::endl;
        exit(1);
    }
    accusedSprite.setTexture(texture);
    accusedSprite.setScale(0.25f, 0.25f);  
    accusedSprite.setPosition(-100, 150);

    nameText.setString("Name: " + accusedManager.getAccused().getName());
    genderText.setString("Gender: " + accusedManager.getAccused().getGenderString());
    reasonText.setString("Reason: " + accusedManager.getAccused().getReasons());
    witchText.setString("Witch: " + accusedManager.getAccused().getWitchString());

    guessedWordText.setString(game.getGuessedWord());
    incorrectLettersText.setString("Incorrect Letters: " + game.getIncorrectLetters());
    livesText.setString("Lives: " + std::to_string(game.getLives()));
    resultText.setString("");
}

void GamePrototype::run() {
    gameLoop();
}

void GamePrototype::gameLoop() {
    while (window.isOpen()) {
        resetGame();
        while (window.isOpen() && game.getLives() > 0) {
            processEvents();
            update();
            render();
        }

        if (game.getLives() <= 0) {
            resultText.setString("Game Over! The word was: " + game.getWordToGuess());
            window.draw(resultText);
            window.display();
            std::this_thread::sleep_for(std::chrono::seconds(3));
            window.close();
        } else {
            resultText.setString("Congratulations! You guessed the word: " + game.getWordToGuess());
            window.draw(resultText);
            window.display();
            std::this_thread::sleep_for(std::chrono::seconds(3));
        }
    }
}

void GamePrototype::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::TextEntered) {
            char enteredChar = static_cast<char>(event.text.unicode);
            if (isalpha(enteredChar)) {
                enteredChar = tolower(enteredChar);
                handleInput(enteredChar);
            }
        }
    }
}

void GamePrototype::update() {
    guessedWordText.setString(game.getGuessedWord());
    incorrectLettersText.setString("Incorrect Letters: " + game.getIncorrectLetters());
    livesText.setString("Lives: " + std::to_string(game.getLives()));
}

void GamePrototype::render() {
    window.clear(sf::Color(161, 130, 98, 255));
    window.draw(backgroundSprite);
    window.draw(treeSprite);
    window.draw(benchSprite);
    window.draw(guessedWordText);
    window.draw(incorrectLettersText);
    window.draw(livesText);
    window.draw(accusedSprite);
    window.draw(nameText);
    window.draw(genderText);
    window.draw(reasonText);
    window.draw(witchText);
    window.display();
}

void GamePrototype::handleInput(char enteredChar) {
    game.guessLetter(enteredChar);
}

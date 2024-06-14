#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include <Words.hpp>

using namespace std;

const int MAX_LIVES = 5;

string chooseRandomWord(const vector<string>& words) {
    srand(time(0));
    int randomIndex = rand() % words.size();
    return words[randomIndex];
}

void loadWords(const string& filename, vector<string>& words) {
    ifstream file(filename);
    if (file.is_open()) {
        string word;
        while (file >> word) {
            words.push_back(word);
        }
        file.close();
    } else {
        cerr << "Unable to open file " << filename << endl;
    }
}

int main(int argc, char const *argv[])
{
    vector<string> words;
    loadWords("./assets/text/easy.txt", words);

    string wordToGuess = chooseRandomWord(words);
    string guessedWord(wordToGuess.length(), '_');
    string incorrectLetters = "";

    int lives = MAX_LIVES;

    sf::RenderWindow window(sf::VideoMode(800, 600), "Hangman Game");

    sf::Font font;
    if (!font.loadFromFile("./assets/fonts/Salium.ttf")) {
        cerr << "Error loading font" << endl;
        return -1;
    }

    sf::Text guessedWordText(guessedWord, font, 30);
    guessedWordText.setPosition(100, 100);

    sf::Text incorrectLettersText("Incorrect Letters: ", font, 30);
    incorrectLettersText.setPosition(100, 200);

    sf::Text livesText("Lives: " + to_string(lives), font, 30);
    livesText.setPosition(100, 300);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::TextEntered) {
                char enteredChar = static_cast<char>(event.text.unicode);
                if (isalpha(enteredChar)) {
                    enteredChar = tolower(enteredChar);

                    bool found = false;
                    for (size_t i = 0; i < wordToGuess.length(); i++) {
                        if (wordToGuess[i] == enteredChar) {
                            guessedWord[i] = enteredChar;
                            found = true;
                        }
                    }

                    if (!found) {
                        if (incorrectLetters.find(enteredChar) == string::npos) {
                            incorrectLetters += enteredChar;
                            incorrectLetters += ' ';
                            lives--;
                        }
                    }

                    guessedWordText.setString(guessedWord);
                    incorrectLettersText.setString("Incorrect Letters: " + incorrectLetters);
                    livesText.setString("Lives: " + to_string(lives));
                }
            }
        }

        window.clear();
        window.draw(guessedWordText);
        window.draw(incorrectLettersText);
        window.draw(livesText);
        window.display();

        if (guessedWord == wordToGuess || lives <= 0) {
            window.close();
        }
    }

    if (guessedWord == wordToGuess) {
        cout << "Congratulations! You guessed the word: " << wordToGuess << endl;
    } else {
        cout << "Game Over! The word was: " << wordToGuess << endl;
    }

    return 0;
}
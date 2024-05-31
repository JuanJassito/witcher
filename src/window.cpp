#include <sfml/Graphics.hpp> // sfml library
#include <SFML/Graphics/Color.hpp> // sfml library
#include <SFML/Audio.hpp> // sfml library
#include <iostream>
#include <Word.hpp> //library write by us to use the words

//? this is the main, have prubes of the sfml library
int main(){
//** initialize screen
    sf::RenderWindow window (sf::VideoMode(768, 768), "THE HANGER WITCH", sf::Style::Close | sf::Style::Resize);
    sf::RectangleShape player(sf::Vector2f(100.0f,100.0f));
    player.setFillColor(sf::Color::White);
    player.setOrigin(25.0f,25.0f);
    sf::Texture playerTexture;
    playerTexture.loadFromFile("./assets/images/a.jpg");
    player.setTexture(&playerTexture);

//** initialize fonts and text
//first text
    sf::Font font;
    font.loadFromFile("./assets/fonts/Hamletornot.ttf");
    sf::Text text("Mercado es guapo",font,45);
    text.setPosition(200, 200);
    text.setFillColor(sf::Color::White);
// second text 
    sf::Font font2;
    font2.loadFromFile("./assets/fonts/Salium.ttf");
    sf::Text text2("NADAQUEVERIENTO",font2,60);
    text2.setPosition(100, 100);
    text2.setFillColor(sf::Color::White);

//** initialize the music 
    sf::Music music;
    if (!music.openFromFile("./assets/sounds/el_gavilan.ogg"))
    {
        // Error al cargar el archivo de música
        return -1;
    }
    music.play();//start music

//** initialize the word of our library 
//! this word is only show on terminal
    Word word("./assets/text/easy.txt"); //TODO: show the word in the window
    int length;
    std::string aword = word.getWord();
    if (!aword.empty()) {
        std::cout << "Palabra aleatoria seleccionada: " << aword << std::endl;
        length = word.getWordLength(aword);
        std::cout << "Longitud de la palabra: " << length << std::endl;
    }

//** initialize a color in RGB
    sf::Color color(198,33,133); //wine

//** things to do if the window is open
    while(window.isOpen()){
        sf::Event evnt;
        

        while(window.pollEvent(evnt)){
            switch (evnt.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::Resized:
                std:: cout << evnt.size.width << evnt.size.height << std::endl;
                break;
            case sf::Event::TextEntered:
                if(evnt.text.unicode < 128){
                    printf("%c", evnt.text.unicode); 
                }
                break;

            default:
                break;
            }
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)){
            player.move(-0.5f, 0.0f);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)){
            player.move(0.5f, 0.0f);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)){
            player.move(0.0f, -0.5f);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)){
            player.move(0.0f, 0.5f);
        }

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            player.setPosition((float)mousePos.x, static_cast<float>(mousePos.y));
        }

        if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
            text2.setFillColor(color);
            window.draw(text2);
        }
//** this is for show the window 
        window.clear();
        window.draw(text);//first layer
        window.draw(player);//second layer
        window.draw(text2);//third layer
        
        window.display();

    }

    return 0;
}
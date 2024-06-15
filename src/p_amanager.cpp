#include <SFML/Graphics.hpp>
#include <AcussedManager.hpp>
#include "Generator.hpp"

int main() {
    numGenerator ng(0, 1);
    imageGenerator ig;
    AccusedManager manager(ng, ig);

    sf::RenderWindow window(sf::VideoMode(800, 600), "Generador de Acusados");
    std::string input;
    int accusedIndex = -1;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::TextEntered && manager.getAccusedList().size() == 4) {
                if (event.text.unicode == '\b') {
                    if (!input.empty())
                        input.pop_back();
                } else if (event.text.unicode < 128) {
                    input += static_cast<char>(event.text.unicode);
                }
                if (event.text.unicode == '\r' || event.text.unicode == '\n') {
                    try {
                        accusedIndex = std::stoi(input);
                        if (accusedIndex >= 0 && accusedIndex < 4) {
                            manager.setCurrentAccusedIndex(accusedIndex);
                            manager.setShowAccused(true);
                            manager.setDisplaySelectionPrompt(false);
                        }
                    } catch (...) {
                        accusedIndex = -1;
                    }
                    input.clear();
                }
            }
        }

        manager.update();

        window.clear();
        manager.draw(window);
        window.display();
    }

    return 0;
}

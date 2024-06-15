#include <SFML/Graphics.hpp>
#include <AcussedManager.hpp>

int main() {
    // Crear la ventana de SFML
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Accused Details");

    // Crear instancias de numGenerator y imageGenerator
    numGenerator ng(0, 1);  // Ejemplo de creación de numGenerator
    imageGenerator ig;      // Ejemplo de creación de imageGenerator

    // Crear un objeto AccusedManager
    AccusedManager accusedManager(ng, ig);

    // Cargar la textura desde el archivo de imagen del acusado
    sf::Texture texture;
    std::string imagePath = ig.generateImage(accusedManager.getAccused().getGender());
    if (!texture.loadFromFile(imagePath)) {
        std::cerr << "Error: No se pudo cargar la imagen del acusado desde " << imagePath << std::endl;
        return 1;
    }

    // Configurar el sprite del acusado con la textura cargada
    sf::Sprite accusedSprite(texture);
    accusedSprite.setScale(0.2f, 0.2f);  // Escalar el sprite si es necesario

    // Posicionar el sprite en una posición fija en la ventana
    accusedSprite.setPosition(-50, 100);  // Ejemplo de posición fija

    // Crear textos para mostrar los detalles del acusado
    sf::Font font;
    if (!font.loadFromFile("./assets/fonts/Hamletornot.ttf")) {
        std::cerr << "Error: No se pudo cargar la fuente Hamletornot.ttf" << std::endl;
        return 1;
    }

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

    // Bucle principal
    while (window.isOpen()) {
        // Procesar eventos
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Limpiar la ventana (borrar lo que se dibujó anteriormente)
        window.clear();

        // Dibujar el sprite del acusado en la ventana
        window.draw(accusedSprite);

        // Dibujar los textos con los detalles del acusado en la ventana
        window.draw(nameText);
        window.draw(genderText);
        window.draw(reasonText);
        window.draw(witchText);

        // Mostrar lo dibujado en la ventana
        window.display();
    }

    return 0;
}

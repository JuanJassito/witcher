#include <SFML/Graphics.hpp>
#include <AcussedManager.hpp> // Asegúrate de incluir correctamente el encabezado donde está definida AccusedManager

int main() {
    // Crear la ventana de SFML
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Accused Sprite");

    // Crear instancias de numGenerator y imageGenerator
    numGenerator ng(0, 1);  // Ejemplo de creación de numGenerator
    imageGenerator ig;      // Ejemplo de creación de imageGenerator

    // Crear un objeto AccusedManager
    AccusedManager accusedManager(ng, ig);

    // Bucle principal
    while (window.isOpen()) {
        // Procesar eventos
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Actualizar datos del acusado (opcional, dependiendo de la implementación de AccusedManager)
        accusedManager.update();

        // Limpiar la ventana (borrar lo que se dibujó anteriormente)
        window.clear();

        // Dibujar el sprite del acusado en la ventana
        window.draw(accusedManager.accusedSprite);

        // Mostrar lo dibujado en la ventana
        window.display();
    }

    return 0;
}

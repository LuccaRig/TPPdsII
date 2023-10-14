#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(500, 500), "SFML Funciona! Teste Bola Branca");
    sf::CircleShape shape(250.f);
    shape.setFillColor(sf::Color(255, 255, 255));

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    sf::RenderWindow knightWindow(sf::VideoMode(256, 256), "Teste com sprite do Knight");
    knightWindow.setVerticalSyncEnabled(true);

    sf::Texture t;
    t.loadFromFile("Knight64x64.png");

    while (knightWindow.isOpen()) {
        sf::Event e;
        while (knightWindow.pollEvent(e)) {
            if (e.type == sf::Event::Closed) knightWindow.close();
        }

        sf::Sprite knight(t);

        knightWindow.clear();
        knightWindow.draw(knight);
        knightWindow.display();
    }
    
    return 0;
}
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;

int main() {
    // SFML 3'te VideoMode artık Vector2u alıyor
    sf::RenderWindow window(sf::VideoMode({800, 600}), "SFML 3 Test");

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    // SFML 3'te setPosition artık Vector2f alıyor
    shape.setPosition({300.f, 200.f});

    while (window.isOpen()) {
        // SFML 3'te event yönetimi değişti, pollEvent artık opsiyonel dönüyor
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}
#include "Funtions.h"
#include "Constants.h"
#include <SFML/Graphics.hpp>

int main() {

    sf::RenderWindow window(sf::VideoMode(ScreenWidth, ScreenHeight), "Sneak");
    window.setFramerateLimit(FPS);
    if (window.isOpen()) {
        WaitPlayerAction(window);
    }

    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // clear the window with black color
        window.clear(sf::Color::Black);
        Play(window);
        window.display();
    }
	return 0;
}
#include <SFML/Graphics.hpp>
#include "Headers/Chain.h"
#include <thread>
#include <iostream>
#include <atomic>

unsigned int width, height;

int main()
{
    width = sf::VideoMode::getDesktopMode().size.x;
    height = sf::VideoMode::getDesktopMode().size.y;

    auto window = sf::RenderWindow(sf::VideoMode({ width, height}), "CMake SFML Project", sf::State::Fullscreen);
    //window.setFramerateLimit(60);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        window.clear();
        window.display();
    }
}

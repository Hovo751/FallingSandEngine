#include <SFML/Graphics.hpp>
#include "Headers/Chain.h"
#include "Headers/TextureArr.h"
#include <thread>
#include <iostream>
#include <atomic>
#include <cstdlib>

unsigned int width, height;
sf::Time deltaTime;

bool checkNode(void* ptr) {
    if (reinterpret_cast<uintptr_t>(ptr) == 0xdddddddddddddddd || reinterpret_cast<uintptr_t>(ptr) == 0xdddddddd) {
        std::cout << "Memory is marked as 0xDDDDDDDD (freed or uninitialized)." << std::endl;
        return false;
    }
    else {
        return true;
    }
}

int main()
{
    unsigned int thread_count = std::thread::hardware_concurrency() / 2;

    width = sf::VideoMode::getDesktopMode().size.x;
    height = sf::VideoMode::getDesktopMode().size.y;

    //Textures
    sf::Texture physicsTx(sf::Vector2u(width, height));

    //Texture arrays
    TextureArr physicsArr(width, height);

    //Sprites
    sf::Sprite physicsLayer(physicsTx);

    for (int i = 0; i < width * height; i++)
    {
        physicsArr.setColor(i, i, i, i, i);
    }

    auto window = sf::RenderWindow(sf::VideoMode({ width, height}), "CMake SFML Project", sf::State::Fullscreen);
    //window.setFramerateLimit(60);

    while (window.isOpen())
    {
        sf::Clock clock;
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        window.clear();


        for (int i = 0; i < width * height; i++)
        {
            physicsArr.SwapPixels(i, i + 1);
        }
        
        //Drawing sprites
        window.draw(physicsLayer);

        window.display();

        //Updating textures
        physicsTx.update(physicsArr.data());

        deltaTime = clock.restart();
    }
}

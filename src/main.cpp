#include <SFML/Graphics.hpp>
#include "Headers/Chain.h"
#include "Headers/TextureArr.h"
#include "Headers/Pixel.h"
#include "Headers/PixelManager.h"
#include <thread>
#include <iostream>
#include <atomic>
#include <cstdlib>
#include <functional>

std::atomic<bool> stopThreads(false);
unsigned int width, height;
sf::Time deltaTime;

void updatePixels(IntChain* updateChainA, TextureArr* physicsArrA, std::vector<IntChain>* updateChainsA)
{
    unsigned int thread_count = std::thread::hardware_concurrency() / 2;
    IntChain& updateChain = *updateChainA;
    TextureArr& physicsArr = *physicsArrA;
    std::vector<IntChain>& updateChains = *updateChainsA;
    sf::Clock clock;
    while (!stopThreads)
    {
        Node* node = updateChain.start;
        int anIntitger = 0;
        while (node != nullptr)
        {
            anIntitger++;
            if (!checkNode(node)) {
                std::cerr << "Invalid node or next pointer." << std::endl << anIntitger << std::endl;
                break;
            }
            node->gettingEdited = true;

            Node* nextNode = node->next;

            const uint8_t r = physicsArr.getPixelCol(node->value)[0];
            const uint8_t b = physicsArr.getPixelCol(node->value)[1];
            const uint8_t g = physicsArr.getPixelCol(node->value)[2];
            const uint8_t a = physicsArr.getPixelCol(node->value)[3];

            Pixel px = GetPixel(r, b, g, a);
            Pixel pxN = GetPixel(r, b, g, a);
            Node* ndN;

            uint8_t* rgbaN;
            int x = node->value % width;
            int y = node->value / width;

            switch (px.type)
            {
            case SANDLIKE:
                rgbaN = physicsArr.getPixelCol(node->value + width);
                pxN = GetPixel(rgbaN[0], rgbaN[1], rgbaN[2], rgbaN[3]);
                ndN = physicsArr.getPixelNode(node->value + width);
                if (ndN != nullptr && checkNode(ndN)) if (ndN->gettingEdited) break;
                if (pxN.type == LIQUID || pxN.type == AIR)
                {
                    if (ndN != nullptr && checkNode(ndN)) ndN->gettingEdited = true;
                    physicsArr.SwapPixels(node->value, node->value + width);
                    int min = 0, size = updateChains[0].size();
                    for (int j = 1; j < updateChains.size(); j++)
                    {
                        min = (size > updateChains[j].size()) ? j : min;
                        size = (size > updateChains[j].size()) ? updateChains[j].size() : size;
                    }
                    for (int dy = -1; dy <= 1; dy++)
                    {
                        for (int dx = -1; dx <= 1; dx++)
                        {
                            int nx = x + dx;
                            int ny = y + dy;
                            int i = ny * width + nx;
                            ndN = physicsArr.getPixelNode(i);
                            if (ndN != nullptr && checkNode(ndN)) if (ndN->gettingEdited) continue;
                            if (ndN != nullptr && checkNode(ndN)) ndN->gettingEdited = true;

                            if (nx >= 0 && nx < width && ny >= 0 && ny < height)
                            {
                                std::uint8_t rA = physicsArr.getPixelCol(nx, ny)[0];
                                std::uint8_t gA = physicsArr.getPixelCol(nx, ny)[1];
                                std::uint8_t bA = physicsArr.getPixelCol(nx, ny)[2];
                                std::uint8_t aA = physicsArr.getPixelCol(nx, ny)[3];
                                if (GetPixel(rA, gA, bA, aA).type != AIR && GetPixel(rA, gA, bA, aA).type != PASSIVE && physicsArr.getPixelNode(i) == nullptr)
                                {
                                    Node* nodeNew = updateChains[min].add(i, 0);
                                    physicsArr.setNode(nodeNew, i);
                                }
                            }
                            if (ndN != nullptr && checkNode(ndN)) ndN->gettingEdited = false;
                        }
                    }
                    if (ndN) ndN->gettingEdited = false;
                    break;
                }

                if (std::rand() % 1000 < px.stopChance * 1000 && physicsArr.getPixelNode(node->value + width) == nullptr && pxN.type != AIR && pxN.type != LIQUID)
                {
                    physicsArr.setNode(nullptr, node->value);
                    updateChain.deleteByAdr(node);
                    break;
                }

                rgbaN = physicsArr.getPixelCol(node->value + width + 1);
                pxN = GetPixel(rgbaN[0], rgbaN[1], rgbaN[2], rgbaN[3]);
                ndN = physicsArr.getPixelNode(node->value + width + 1);
                if (ndN != nullptr && checkNode(ndN)) if (ndN->gettingEdited) break;
                if (pxN.type == LIQUID || pxN.type == AIR)
                {
                    if (ndN != nullptr && checkNode(ndN)) ndN->gettingEdited = true;
                    physicsArr.SwapPixels(node->value, node->value + width + 1);
                    int min = 0, size = updateChains[0].size();
                    for (int j = 1; j < updateChains.size(); j++)
                    {
                        min = (size > updateChains[j].size()) ? j : min;
                        size = (size > updateChains[j].size()) ? updateChains[j].size() : size;
                    }
                    for (int dy = -1; dy <= 1; dy++)
                    {
                        for (int dx = -1; dx <= 1; dx++)
                        {
                            int nx = x + dx;
                            int ny = y + dy;
                            int i = ny * width + nx;
                            ndN = physicsArr.getPixelNode(i);
                            if (ndN != nullptr && checkNode(ndN)) if (ndN->gettingEdited) continue;
                            if (ndN != nullptr && checkNode(ndN)) ndN->gettingEdited = true;

                            if (nx >= 0 && nx < width && ny >= 0 && ny < height)
                            {
                                std::uint8_t rA = physicsArr.getPixelCol(nx, ny)[0];
                                std::uint8_t gA = physicsArr.getPixelCol(nx, ny)[1];
                                std::uint8_t bA = physicsArr.getPixelCol(nx, ny)[2];
                                std::uint8_t aA = physicsArr.getPixelCol(nx, ny)[3];
                                if (GetPixel(rA, gA, bA, aA).type != AIR && GetPixel(rA, gA, bA, aA).type != PASSIVE && physicsArr.getPixelNode(i) == nullptr)
                                {
                                    Node* nodeNew = updateChains[min].add(i, 0);
                                    physicsArr.setNode(nodeNew, i);
                                }
                            }
                            if (ndN != nullptr && checkNode(ndN)) ndN->gettingEdited = false;
                        }
                    }
                    if (ndN) ndN->gettingEdited = false;
                    break;
                }
                rgbaN = physicsArr.getPixelCol(node->value + width - 1);
                pxN = GetPixel(rgbaN[0], rgbaN[1], rgbaN[2], rgbaN[3]);
                ndN = physicsArr.getPixelNode(node->value + width - 1);
                if (ndN != nullptr && checkNode(ndN)) if (ndN->gettingEdited) break;
                if (pxN.type == LIQUID || pxN.type == AIR)
                {
                    if (ndN != nullptr && checkNode(ndN)) ndN->gettingEdited = true;
                    physicsArr.SwapPixels(node->value, node->value + width - 1);
                    int min = 0, size = updateChains[0].size();
                    for (int j = 1; j < updateChains.size(); j++)
                    {
                        min = (size > updateChains[j].size()) ? j : min;
                        size = (size > updateChains[j].size()) ? updateChains[j].size() : size;
                    }
                    for (int dy = -1; dy <= 1; dy++)
                    {
                        for (int dx = -1; dx <= 1; dx++)
                        {
                            int nx = x + dx;
                            int ny = y + dy;
                            int i = ny * width + nx;
                            ndN = physicsArr.getPixelNode(i);
                            if (ndN != nullptr && checkNode(ndN)) if (ndN->gettingEdited) continue;
                            if (ndN != nullptr && checkNode(ndN)) ndN->gettingEdited = true;

                            if (nx >= 0 && nx < width && ny >= 0 && ny < height)
                            {
                                std::uint8_t rA = physicsArr.getPixelCol(nx, ny)[0];
                                std::uint8_t gA = physicsArr.getPixelCol(nx, ny)[1];
                                std::uint8_t bA = physicsArr.getPixelCol(nx, ny)[2];
                                std::uint8_t aA = physicsArr.getPixelCol(nx, ny)[3];
                                if (GetPixel(rA, gA, bA, aA).type != AIR && GetPixel(rA, gA, bA, aA).type != PASSIVE && physicsArr.getPixelNode(i) == nullptr)
                                {
                                    Node* nodeNew = updateChains[min].add(i, 0);
                                    physicsArr.setNode(nodeNew, i);
                                }
                            }
                            if (ndN != nullptr && checkNode(ndN)) ndN->gettingEdited = false;
                        }
                    }
                    if (ndN) ndN->gettingEdited = false;
                    break;
                }
                physicsArr.setNode(nullptr, node->value);
                updateChain.deleteByAdr(node);
                break;
            case AIR:
                std::cout << "ERROR" << std::endl;
                physicsArr.setNode(nullptr, node->value);
                updateChain.deleteByAdr(node);
                break;
            default:
                break;
            }

            node->gettingEdited = false;
            node = nextNode;
        }
        anIntitger = 0;
        sf::sleep(sf::milliseconds(16) - clock.reset());
    }
}

void noneAction()
{
    return;
}

int main()
{
    unsigned int thread_count = std::thread::hardware_concurrency();

    AddPixel(Pixel(PASSIVE, 1, 1, 255, 255, 255, 0, noneAction));
    AddPixel(Pixel(SANDLIKE, 1, 0.5f, 255, 255, 0, 255, noneAction));
    AddPixel(Pixel(SANDLIKE, 1, 0.5f, 255, 150, 0, 255, noneAction));

    width = sf::VideoMode::getDesktopMode().size.x;
    height = sf::VideoMode::getDesktopMode().size.y;

    //Textures
    sf::Texture physicsTx(sf::Vector2u(width, height));

    //Texture arrays
    TextureArr physicsArr(width, height);

    //Sprites
    sf::Sprite physicsLayer(physicsTx);

    //Chains
    std::vector<IntChain> updateChains(thread_count / 2);

    /*for (int i = 0; i < width * height; i++)
    {
        physicsArr.setColor(i, i, i, i, i);
    }*/

    auto window = sf::RenderWindow(sf::VideoMode({ width, height}), "CMake SFML Project", sf::State::Fullscreen);
    //window.setFramerateLimit(15);

    std::vector<std::thread> SimulationThreads;
    for (int i = 0; i < updateChains.size(); i++)
    {
        SimulationThreads.emplace_back(updatePixels, &updateChains[i], &physicsArr, &updateChains);
    }

    while (window.isOpen())
    {
        sf::Clock clock;
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                stopThreads = true;
                for (auto& th : SimulationThreads) {
                    if (th.joinable())
                        th.join();
                }
                window.close();
            }
        }

        window.clear();


        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            sf::Vector2i position = sf::Mouse::getPosition(window);
            unsigned int i = position.y * width + position.x;
            uint8_t* cl = physicsArr.getPixelCol(i);
            Pixel AFPIXELTHATIHATE = GetPixel(cl[0], cl[1], cl[2], cl[3]);
            if (AFPIXELTHATIHATE.type == AIR)
            {
                physicsArr.setColor(255, (std::rand() % 100 < 50) ? 255 : 150, 0, 255, i);
                Node* node;
                int min = 0, size = updateChains[0].size();
                for (int j = 1; j < updateChains.size(); j++)
                {
                    min = (size > updateChains[j].size()) ? j : min;
                    size = (size > updateChains[j].size()) ? updateChains[j].size() : size;
                }
                node = updateChains[min].add(i, 0);
                physicsArr.setNode(node, i);
            }
        }
        
        //Drawing sprites
        window.draw(physicsLayer);

        window.display();

        //Updating textures
        physicsTx.update(physicsArr.data());

        deltaTime = clock.restart();
    }
}

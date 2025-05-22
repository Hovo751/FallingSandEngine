#pragma once
#include <iostream>
#include <functional>

enum PixelType {
    LIQUID,
    PASSIVE,
    SANDLIKE,
    AIR
};

struct Pixel
{
    PixelType type;
    //int main;
    int density;
    float stopChance;
    uint8_t r, g, b, a;
    std::function<void()> action;

    Pixel(PixelType tp, int d, float st, uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha, std::function<void()> func)
        : type(tp), density(d), stopChance(st), r(red), g(green), b(blue), a(alpha), action(func) {
    }

    void runAction()
    {
        if (action)
            action();
    }

    void printInfo()
    {
        std::cout << "Type: " << type
            << ", Density: " << density
            << ", Color: (" << r << ", " << g << ", " << b << ", " << a << ")"
            << std::endl;
    }
};

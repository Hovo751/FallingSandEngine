#pragma once
#include <iostream>
#include <functional>

struct Pixel
{
    int type;
    int density;
    int r, g, b, a;
    std::function<void()> action;

    Pixel(int t, int d, int red, int green, int blue, int alpha, std::function<void()> func)
        : type(t), density(d), r(red), g(green), b(blue), a(alpha), action(func) {
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

#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Chain.h"
#include <algorithm>

class TextureArr {
    std::vector<std::uint8_t> pixels;
    std::vector<Node*> pixelRef;
    std::uint8_t colorNt[4] = { 255, 255, 255, 0 };
    unsigned width, height;
public:
    TextureArr(unsigned int x, unsigned int y) : pixels(x* y * 4), pixelRef(x* y), width(x), height(y) {}

    unsigned getHeight()
    {
        return height;
    }

    unsigned getWidth()
    {
        return width;
    }

    void setColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a, unsigned i) {
        if (i < 0 || i * 4 + 3 >= pixels.size()) return;
        pixels[i * 4] = r;
        pixels[i * 4 + 1] = g;
        pixels[i * 4 + 2] = b;
        pixels[i * 4 + 3] = a;
    }

    void setColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a, unsigned x, unsigned y) {
        unsigned int i = y * width + x;
        if (i < 0 || i * 4 + 3 >= pixels.size()) return;
        pixels[i * 4] = r;
        pixels[i * 4 + 1] = g;
        pixels[i * 4 + 2] = b;
        pixels[i * 4 + 3] = a;
    }

    void setNode(Node* node, unsigned i) {
        if (i < 0 || i >= pixelRef.size()) return;
        pixelRef[i] = node;
    }

    void setNode(Node* node, unsigned x, unsigned y) {
        unsigned int i = y * width + x;
        if (i < 0 || i >= pixelRef.size()) return;
        pixelRef[i] = node;
    }

    std::uint8_t* getData() {
        return pixels.data();
    }

    std::uint8_t* getPixelCol(unsigned int i) {
        if (i >= 0 && i * 4 + 3 < pixels.size()) {
            return &pixels[i * 4];
        }
        return colorNt;
    }

    std::uint8_t* getPixelCol(unsigned int x, unsigned int y) {
        unsigned int i = y * width + x;
        if (i >= 0 && i * 4 + 3 < pixels.size()) {
            return &pixels[i * 4];
        }
        return colorNt;
    }

    Node* getPixelNode(unsigned int i) {
        if (i >= 0 && i < pixelRef.size())
            return pixelRef[i];
        return nullptr;
    }

    Node* getPixelNode(unsigned int x, unsigned int y) {
        unsigned int i = y * width + x;
        if (i >= 0 && i < pixelRef.size())
            return pixelRef[i];
        return nullptr;
    }

    void SwapPixels(unsigned int i1, unsigned int i2) {
        std::uint8_t* c1 = getPixelCol(i1);
        std::uint8_t* c2 = getPixelCol(i2);

        for (int i = 0; i < 4; i++) {
            c1[i] += c2[i];
            c2[i] = c1[i] - c2[i];
            c1[i] -= c2[i];
        }

        Node* node1 = getPixelNode(i1);
        setNode(getPixelNode(i2), i2);
        setNode(node1, i1);
    }

    void SwapPixels(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2) {
        SwapPixels(y1 * width + x1, y2 * width + x2);
    }
};
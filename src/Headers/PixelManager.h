#pragma once
#include "Pixel.h"

void nA()
{
	return;
}

std::vector<Pixel> pixelTypes;
Pixel air(AIR, 0, 0, 0, 0, 0, 0, nA);

void AddPixel(Pixel px) {
	pixelTypes.push_back(px);
}

Pixel GetPixel(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	for (size_t i = 0; i < pixelTypes.size(); i++)
	{
		if (pixelTypes[i].r == r && pixelTypes[i].g == g && pixelTypes[i].b == b && pixelTypes[i].a == a)
			return pixelTypes[i];
	}
	return air;
}
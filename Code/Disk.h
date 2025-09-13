#pragma once

#include <SFML/Graphics.hpp>

struct Disk 
{
    int size; // розм≥р (1 Ч найменший, n Ч найб≥льший)
    sf::RectangleShape shape; // в≥зуальне представленн€ диска

    Disk(int sizeIndex, float width, float height, sf::Color color);
};

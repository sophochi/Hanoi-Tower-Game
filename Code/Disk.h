#pragma once

#include <SFML/Graphics.hpp>

struct Disk 
{
    int size; // ����� (1 � ���������, n � ���������)
    sf::RectangleShape shape; // �������� ������������� �����

    Disk(int sizeIndex, float width, float height, sf::Color color);
};

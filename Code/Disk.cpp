#include "Disk.h"

Disk::Disk(int sizeIndex, float width, float height, sf::Color color)
    : size(sizeIndex)
{
    shape.setSize(sf::Vector2f(width, height)); //  ������
    shape.setFillColor(color); // ����
    shape.setOrigin(width / 2.0f, height); // ������� � ����� ����
}

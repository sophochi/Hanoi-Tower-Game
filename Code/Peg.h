#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Disk.h"

class Peg
{
public:
    // ������������
    Peg();
    Peg(float xPos, float baseY, float rodHeight, float rodWidth, sf::Color color);

    void pushDisk(Disk* disk);  // ������ ���� �� ��������
    Disk* popDisk(); // ����� ������ ����
    Disk* getTopDisk() const; // ���������� ������ ����
    bool isEmpty() const; // ���������, �� �������� �������
    std::vector<Disk*>& getDisks(); // ������ �� ������ �����

    void clear()
    {
        disks.clear();
    }

    // ��� �����������
    float x; // ������� ������� �� X
    const sf::RectangleShape& getRodShape() const; // ��������� ��'��� �������

private:
    std::vector<Disk*> disks; // ������ ����� �� ������ (����)
    sf::RectangleShape rod; // �������� ������������� �������
};





#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Disk.h"

class Peg
{
public:
    // конструктори
    Peg();
    Peg(float xPos, float baseY, float rodHeight, float rodWidth, sf::Color color);

    void pushDisk(Disk* disk);  // додати диск на стрижень
    Disk* popDisk(); // зняти верхній диск
    Disk* getTopDisk() const; // подивитися верхній диск
    bool isEmpty() const; // перевірити, чи стрижень порожній
    std::vector<Disk*>& getDisks(); // доступ до списку дисків

    void clear()
    {
        disks.clear();
    }

    // Для відображення
    float x; // позиція стрижня по X
    const sf::RectangleShape& getRodShape() const; // графічний об'єкт стрижня

private:
    std::vector<Disk*> disks; // вектор дисків на стрижні (стек)
    sf::RectangleShape rod; // візуальне представлення стрижня
};





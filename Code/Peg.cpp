#include "Peg.h"

Peg::Peg() : x(0) {}

Peg::Peg(float xPos, float baseY, float rodHeight, float rodWidth, sf::Color color)
    : x(xPos)
{
    rod.setSize(sf::Vector2f(rodWidth, rodHeight));
    rod.setFillColor(color);
    rod.setOrigin(rodWidth / 2.f, rodHeight);
    rod.setPosition(xPos, baseY);
}

void Peg::pushDisk(Disk* disk) 
{
    disks.push_back(disk);
}

Disk* Peg::popDisk() 
{
    if (disks.empty()) return nullptr;
    Disk* top = disks.back();
    disks.pop_back();
    return top;
}

Disk* Peg::getTopDisk() const 
{
    if (disks.empty()) return nullptr;
    return disks.back();
}

bool Peg::isEmpty() const 
{
    return disks.empty();
}

std::vector<Disk*>& Peg::getDisks() 
{
    return disks;
}

const sf::RectangleShape& Peg::getRodShape() const 
{
    return rod;
}

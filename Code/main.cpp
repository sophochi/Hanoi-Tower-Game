#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "HanoiGame.h"


int main()
{
    const unsigned int windowWidth = 1200;
    const unsigned int windowHeight = 800;
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Hanoi Tower", sf::Style::Close);
    window.setFramerateLimit(60);

    while (true)
    {
        Menu menu;
        int numDisks = menu.run(window);  // ������ ���� �� ������� ������� ����� ��� 0 ��� ������

        if (numDisks == 0)
            break; // ���� ������ ����� � ��������� ���

        // ��������� ������� �����
        if (numDisks < 3) numDisks = 3;
        if (numDisks > 20) numDisks = 20;

        HanoiGame game(numDisks);

        // run ������� true, ���� ��������� Restart (����� ���������� � ����)
        // false � ���� ���������� ������ ���� ��� �������� ���
        bool restart = game.run(window);

        if (!restart)
            break; // ���� ��� ��������� � �������� � �����
        // ���� restart == true � continue: �������� ���� �����
    }

    return 0;
}

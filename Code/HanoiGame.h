#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "Disk.h"
#include "Peg.h"

class HanoiGame
{
public:
    // ����������� ������ ������� �����
    HanoiGame(int numDisks);

    // ����������� ��� � ������������ ��������
    void initGame(sf::Vector2u winSize);

    // �������� ���� ���
    bool run(sf::RenderWindow& window);

    // ������� ���� ���� (����������, �������������, ������ �� ������)
    void handleEvents(sf::RenderWindow& window);

    // �������� ��� � ���������� ����
    void resetToInitialState();

    // ��������, �� ������ ����������
    void checkUserVictory(sf::RenderWindow& window);

    // ����� ��������� � ������ ����������� ����
    void showVictoryPopup(sf::RenderWindow& window);


    sf::RectangleShape aboutButton;
    sf::Text aboutText;

    bool showRulesWindow = false;




private:
    int diskCount; // ������� �����
    int userMoves; // ������� ���� �����������
    float baseY; // Y-������� ������
    float diskHeight; // ������ ������ �����
    float rodWidth; // ������ �������

    bool isSolving; // �� ����� ��������������
    bool gameWon = false; // �� ������ ����������
    int solveMoveIndex; // ������ ��������� ���� ��������������

    bool shouldReturnToMenu = false;


    std::vector<std::pair<int, int>> solveMoves; // ����������� ����
    std::vector<Disk*> disks; // �� �����
    Peg pegs[3];  // ����� � ����� �������

    Disk* movingDisk; // �������� ����, ���� ������������ �����
    int fromPeg;  // � ����� ������� ���� ��� ������


    sf::RectangleShape base; // ������
    sf::RectangleShape solveButton; // ������ Solve
    sf::Text solveText;  // ����� �� ������
    sf::Text movesText; // �������� ����

	sf::RectangleShape restartButton; // ������ Restart
    sf::Text restartText; // ����� �� ������

    sf::Font font; // �����

    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
};

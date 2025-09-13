#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "Disk.h"
#include "Peg.h"

class HanoiGame
{
public:
    // конструктор приймаЇ к≥льк≥сть диск≥в
    HanoiGame(int numDisks);

    // ≥н≥ц≥ал≥зац≥€ гри Ч розташуванн€ елемент≥в
    void initGame(sf::Vector2u winSize);

    // основний цикл гри
    bool run(sf::RenderWindow& window);

    // обробка под≥й миш≥ (натисканн€, перет€гуванн€, натиск на кнопки)
    void handleEvents(sf::RenderWindow& window);

    // скиданн€ веж≥ у початковий стан
    void resetToInitialState();

    // перев≥рка, чи виграв користувач
    void checkUserVictory(sf::RenderWindow& window);

    // показ прив≥танн€ у вигл€д≥ спливаючого в≥кна
    void showVictoryPopup(sf::RenderWindow& window);


    sf::RectangleShape aboutButton;
    sf::Text aboutText;

    bool showRulesWindow = false;




private:
    int diskCount; // к≥льк≥сть диск≥в
    int userMoves; // к≥льк≥сть ход≥в користувача
    float baseY; // Y-позиц≥€ основи
    float diskHeight; // висота одного диска
    float rodWidth; // ширина стрижн€

    bool isSolving; // чи триваЇ авторозвТ€занн€
    bool gameWon = false; // чи виграв користувач
    int solveMoveIndex; // ≥ндекс поточного ходу авторозвТ€занн€

    bool shouldReturnToMenu = false;


    std::vector<std::pair<int, int>> solveMoves; // посл≥довн≥сть ход≥в
    std::vector<Disk*> disks; // вс≥ диски
    Peg pegs[3];  // масив з трьох стрижн≥в

    Disk* movingDisk; // поточний диск, €кий перет€гуЇтьс€ мишею
    int fromPeg;  // з €кого стрижн€ диск був вз€тий


    sf::RectangleShape base; // основа
    sf::RectangleShape solveButton; // кнопка Solve
    sf::Text solveText;  // напис на кнопц≥
    sf::Text movesText; // л≥чильник ход≥в

	sf::RectangleShape restartButton; // кнопка Restart
    sf::Text restartText; // напис на кнопц≥

    sf::Font font; // шрифт

    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
};

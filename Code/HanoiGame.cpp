#include "HanoiGame.h"
#include "TowerSolver.h"
#include <SFML/Audio.hpp>
#include <thread>
#include <chrono>
#include <iostream>

// конструктор гри
HanoiGame::HanoiGame(int numDisks)
    : diskCount(numDisks), userMoves(0), isSolving(false), solveMoveIndex(0),
    movingDisk(nullptr), baseY(0), diskHeight(0), rodWidth(0),
    fromPeg(-1), gameWon(false), shouldReturnToMenu(false) {}


// ініціалізує гру - створює основу, стрижні, диски та кнопки
void HanoiGame::initGame(sf::Vector2u winSize) 
{
    float winW = static_cast<float>(winSize.x);
    float winH = static_cast<float>(winSize.y);

    // фон
    if (backgroundTexture.loadFromFile("background.jpg")) 
    {
        backgroundSprite.setTexture(backgroundTexture);
        backgroundSprite.setScale(
            winW / backgroundTexture.getSize().x,
            winH / backgroundTexture.getSize().y );
    }

    // основа гри
    base.setSize(sf::Vector2f(600.f, 50.f));
    base.setFillColor(sf::Color(139, 69, 19));
    base.setOrigin(base.getSize().x / 2.f, base.getSize().y / 2.f);
    base.setPosition(winW / 2.f, winH - 40.f);
    baseY = base.getPosition().y;

    // створення трьох стрижнів
    float rodHeight = 200.f;
    rodWidth = 10.f;
    float xSpacing = 200.f;
    float startX = winW / 2.f - xSpacing;
    sf::Color rodColor(160, 82, 45);

    for (int i = 0; i < 3; ++i)
        pegs[i] = Peg(startX + i * xSpacing, baseY, rodHeight, rodWidth, rodColor);

    // створення дисків
    diskHeight = 20.f;
    float maxW = 160.f;
    float minW = 60.f;
    disks.clear();

    for (int i = diskCount; i >= 1; --i) 
    {
        float width = minW + (i - 1) * (maxW - minW) / (diskCount - 1);
        sf::Color color = sf::Color(100 + 15 * i, 100 + 10 * i, 255 - 10 * i);
        Disk* d = new Disk(i, width, diskHeight, color);
        d->shape.setPosition(pegs[0].x, baseY - pegs[0].getDisks().size() * diskHeight);
        pegs[0].pushDisk(d);
        disks.push_back(d);
    }


   // створення кнопки Solve
    solveButton.setSize(sf::Vector2f(120.f, 50.f)); // розміри кнопки
    solveButton.setFillColor(sf::Color::White); // білий фон
    solveButton.setOutlineThickness(4.f); // товщина обводки
    solveButton.setOutlineColor(sf::Color(81, 147, 159)); // голуба обводка

    // отримання розміру вікна для позиціювання
    sf::Vector2u windowSize = winSize; 

    // розміщення кнопки в правому верхньому куті з відступом 20 пікселів
    solveButton.setPosition( windowSize.x - solveButton.getSize().x - 20.f, 20.f );




    // створення кнопки Restart
    restartButton.setSize(sf::Vector2f(120.f, 50.f)); // розміри кнопки
    restartButton.setFillColor(sf::Color::White); // білий фон
    restartButton.setOutlineThickness(4.f); // товщина обводки
    restartButton.setOutlineColor(sf::Color(81, 147, 159)); // голуба обводка


    // розміщення кнопки лівіше від Solve
    restartButton.setPosition(
        solveButton.getPosition().x - restartButton.getSize().x - 15.f,
        solveButton.getPosition().y );


    // тексти
    if (font.loadFromFile("MyFont.ttf"))
    {
        solveText.setFont(font);
        solveText.setString("Solve");
        solveText.setCharacterSize(30);
        solveText.setFillColor(sf::Color::Black);
        solveText.setPosition(solveButton.getPosition().x + 15.f, solveButton.getPosition().y + 5.f);

        movesText.setFont(font);
        movesText.setCharacterSize(35);
        movesText.setFillColor(sf::Color::Black);
        movesText.setPosition(20.f, 20.f);
        movesText.setString("Moves: 0");

        restartText.setFont(font);
        restartText.setCharacterSize(30);
        restartText.setFillColor(sf::Color::Black);
        restartText.setPosition(restartButton.getPosition().x + 15.f, restartButton.getPosition().y + 5.f);
        restartText.setString("Restart");
    }
}

// обробка подій миші
void HanoiGame::handleEvents(sf::RenderWindow& window) 
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed) window.close();

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            float mx = static_cast<float>(event.mouseButton.x);
            float my = static_cast<float>(event.mouseButton.y);

            if (solveButton.getGlobalBounds().contains(mx, my))
            {
                resetToInitialState();
                TowerSolver::solveHanoi(diskCount, 0, 2, 1, solveMoves);
                isSolving = true;
                solveMoveIndex = 0;
            }


            else if (restartButton.getGlobalBounds().contains(mx, my))
            {
                shouldReturnToMenu = true; // повернення до меню
            }

            else
            {
                for (int i = 0; i < 3; ++i) 
                {
                    if (!pegs[i].getDisks().empty())
                    {
                        Disk* topDisk = pegs[i].getDisks().back();
                        if (topDisk->shape.getGlobalBounds().contains(mx, my)) 
                        {
                            movingDisk = topDisk;
                            fromPeg = i;
                            break;
                        }
                    }
                }
            }
        }
        else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
            if (movingDisk) 
            {
                float mx = static_cast<float>(event.mouseButton.x);
                int targetPeg = -1;
                for (int i = 0; i < 3; ++i) 
                {
                    if (std::abs(mx - pegs[i].x) < 80.f) 
                    {
                        targetPeg = i;
                        break;
                    }
                }

                if (targetPeg != -1 && (pegs[targetPeg].getDisks().empty() ||
                    movingDisk->size < pegs[targetPeg].getDisks().back()->size)) 
                {

                    pegs[fromPeg].popDisk();
                    int index = pegs[targetPeg].getDisks().size();
                    movingDisk->shape.setPosition(pegs[targetPeg].x, baseY - index * diskHeight);
                    pegs[targetPeg].pushDisk(movingDisk);
                    userMoves++;
                    movesText.setString("Moves: " + std::to_string(userMoves));

                  
                    checkUserVictory(window);
                }

                movingDisk = nullptr;
            }
        }

    }
}

// основний цикл
bool  HanoiGame::run(sf::RenderWindow& window)
{
    initGame(window.getSize());
    window.setFramerateLimit(60);

    while (window.isOpen()) 
    {
        handleEvents(window);

        if (shouldReturnToMenu)
            return true;


        if (isSolving && solveMoveIndex < solveMoves.size()) 
        {
            int from = solveMoves[solveMoveIndex].first;
            int to = solveMoves[solveMoveIndex].second;

            Disk* disk = pegs[from].popDisk();
            int index = pegs[to].getDisks().size();
            disk->shape.setPosition(pegs[to].x, baseY - index * diskHeight);
            pegs[to].pushDisk(disk);
            solveMoveIndex++;

            userMoves++;
            movesText.setString("Moves: " + std::to_string(userMoves));

            std::this_thread::sleep_for(std::chrono::milliseconds(150));
        }

        else if (isSolving && solveMoveIndex >= solveMoves.size())
        {
            isSolving = false;
            gameWon = true;  // позначка про перемогу
        }


        window.clear();
        window.draw(backgroundSprite);
        window.draw(base);

        for (int i = 0; i < 3; ++i)
            window.draw(pegs[i].getRodShape());

        for (int i = 0; i < 3; ++i)
            for (Disk* d : pegs[i].getDisks())
                window.draw(d->shape);

        if (movingDisk)
            window.draw(movingDisk->shape);

        window.draw(solveButton);
        window.draw(solveText);
        window.draw(movesText);

        window.draw(restartButton);
        window.draw(restartText);


        if (gameWon)
        {
            showVictoryPopup(window);
            gameWon = false;
        }

        window.display();
    }

    return shouldReturnToMenu; // повертаємо позначку true — повернення в меню


}



void HanoiGame::resetToInitialState() 
{
    for (int i = 0; i < 3; ++i)
        pegs[i].clear();

    for (int i = diskCount; i >= 1; --i) 
    {
        Disk* d = disks[diskCount - i];
        d->shape.setPosition(pegs[0].x, baseY - pegs[0].getDisks().size() * diskHeight);
        pegs[0].pushDisk(d);
    }

    userMoves = 0;
    movesText.setString("Moves: 0");
}


void HanoiGame::checkUserVictory(sf::RenderWindow& window) 
{
    if (pegs[2].getDisks().size() == diskCount) 
    {
        gameWon = true;
    }
}

   
void HanoiGame::showVictoryPopup(sf::RenderWindow& window)
{
    // завантаження шрифту
    sf::Font popupFont;
    popupFont.loadFromFile("MyFont2.ttf");

    // створення тексту
    sf::Text popupText;
    popupText.setFont(popupFont);
    popupText.setString("Congratulations!\nYou solved the Tower!");
    popupText.setCharacterSize(40);
    popupText.setFillColor(sf::Color::White);
    popupText.setOutlineColor(sf::Color::Black);
    popupText.setOutlineThickness(3);

    // центрування тексту
    sf::FloatRect textBounds = popupText.getLocalBounds();
    popupText.setOrigin(textBounds.left + textBounds.width / 2.f, textBounds.top + textBounds.height / 2.f);
    popupText.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);

    // прямокутник позаду тексту
    sf::RectangleShape box(sf::Vector2f(600, 200));
    box.setFillColor(sf::Color(0, 0, 0, 200));
    box.setOrigin(box.getSize().x / 2.f, box.getSize().y / 2.f);
    box.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);

    // музика
    sf::SoundBuffer buffer;
    sf::Sound sound;
    if (buffer.loadFromFile("Congrats.mp3"))
    {
        sound.setBuffer(buffer);
        sound.play();
    }

    // анімація
    for (int i = 0; i < 300; ++i)
    {
        window.clear();
        window.draw(backgroundSprite);
        window.draw(base);
        for (int i = 0; i < 3; ++i)
            window.draw(pegs[i].getRodShape());
        for (int i = 0; i < 3; ++i)
            for (Disk* d : pegs[i].getDisks())
                window.draw(d->shape);

        window.draw(box);
        window.draw(popupText);
        window.display();

        std::this_thread::sleep_for(std::chrono::milliseconds(3));
    }
    sound.stop();
}

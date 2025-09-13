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
        int numDisks = menu.run(window);  // показуЇ меню та повертаЇ к≥льк≥сть диск≥в або 0 дл€ виходу

        if (numDisks == 0)
            break; // €кщо обрано вих≥д Ч завершуЇмо гру

        // обмеженн€ к≥лькост≥ диск≥в
        if (numDisks < 3) numDisks = 3;
        if (numDisks > 20) numDisks = 20;

        HanoiGame game(numDisks);

        // run повертаЇ true, €кщо натиснуто Restart (тобто поверненн€ в меню)
        // false Ч €кщо користувач закрив в≥кно або завершив гру
        bool restart = game.run(window);

        if (!restart)
            break; // €кщо гра завершена Ч виходимо з циклу
        // €кщо restart == true Ч continue: показати меню знову
    }

    return 0;
}

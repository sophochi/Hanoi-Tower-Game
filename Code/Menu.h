#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class Menu
{
public:
    Menu();
    int run(sf::RenderWindow& window);

private:
    sf::Font font;
    sf::Font font2;

    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

	sf::Texture cloudeTexture;
	sf::Sprite cloudeSprite;

    sf::Text welcomeText;
    sf::Text titleText;
    sf::Text inputText;
    sf::RectangleShape inputBox;
    sf::Text userInput;
    sf::Text hintText;

    sf::RectangleShape rulesButton;
    sf::Text rulesText;


    std::string inputString;

    void processEvent(sf::RenderWindow& window, sf::Event& event, bool& running, int& diskCount);

    void render(sf::RenderWindow& window);

    void centerText(sf::Text& text, float x, float y);

    void showRulesWindow();

};

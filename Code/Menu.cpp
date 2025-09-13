#include "Menu.h"

Menu::Menu()
{
    // фон
    backgroundTexture.loadFromFile("background.jpg");
    backgroundSprite.setTexture(backgroundTexture);  

    // шрифти
    font.loadFromFile("MyFont.ttf");
    font2.loadFromFile("MyFont2.ttf");

    // хмара
    cloudeTexture.loadFromFile("cloude.png");
	cloudeSprite.setTexture(cloudeTexture);

    // текст привітання 
    welcomeText.setFont(font);
    welcomeText.setString("Hi there, welcome to");
    welcomeText.setCharacterSize(40);
    welcomeText.setFillColor(sf::Color::White);   // Білий колір тексту
    welcomeText.setOutlineColor(sf::Color::Black); // Чорна обводка
    welcomeText.setOutlineThickness(3);

    // текст назви гри 
    titleText.setFont(font);
    titleText.setString("Hanoi Tower Game");
    titleText.setCharacterSize(60);
    titleText.setFillColor(sf::Color::White);
    titleText.setOutlineColor(sf::Color::Black);
    titleText.setOutlineThickness(4);

    // текст з проханням ввести кількість дисків
    inputText.setFont(font2);
    inputText.setString("Please,\nEnter number of discs (>=3):"); 
    inputText.setCharacterSize(30);
    inputText.setFillColor(sf::Color::White);
    inputText.setOutlineColor(sf::Color::Black);
    inputText.setOutlineThickness(3);

    // прямокутник для введення тексту
    inputBox.setFillColor(sf::Color(0, 0, 0, 200)); // Напівпрозорий чорний
    inputBox.setSize(sf::Vector2f(400, 50));  // Розміри поля
    inputBox.setOrigin(inputBox.getSize() / 2.f); // Центруємо поле

    // текст введених користувачем символів (числа дисків)
    userInput.setFont(font);
    userInput.setCharacterSize(45);
    userInput.setFillColor(sf::Color::White);
    userInput.setOutlineColor(sf::Color::Black);
    userInput.setOutlineThickness(3);

    // підказка внизу
    hintText.setFont(font2);
    hintText.setString("Press ENTER to start, or ESC to quit");
    hintText.setCharacterSize(30);
    hintText.setFillColor(sf::Color::White);
    hintText.setOutlineColor(sf::Color::Black);
    hintText.setOutlineThickness(3);

    // кнопка "Rules"
    rulesButton.setSize(sf::Vector2f(150.f, 45.f));
    rulesButton.setFillColor(sf::Color(175, 200, 199));
    rulesButton.setOutlineThickness(4.f);
    rulesButton.setOutlineColor(sf::Color(60, 110, 187));

    // текст на кнопці
    rulesText.setFont(font2);
    rulesText.setCharacterSize(25);
    rulesText.setFillColor(sf::Color::Black);
    rulesText.setString("Rules");
}

int Menu::run(sf::RenderWindow& window)
{
    inputString = ""; // рядок в який буде записуватись те, що вводить користувач
    bool running = true; // чи триває робота меню
    int diskCount = -1; // кількість дисків (ще не вибрана)

    // основний цикл меню 
    while (running && window.isOpen()) // поки вікно відкрите і меню активне
    {
        sf::Event event;
        while (window.pollEvent(event))  // перевіряємо усі події (натискання клавіш, закриття вікна)
        {
            processEvent(window, event, running, diskCount);
        }

       sf::Vector2u windowSize = window.getSize();
        backgroundSprite.setScale(
            float(windowSize.x) / backgroundTexture.getSize().x,
            float(windowSize.y) / backgroundTexture.getSize().y ); 
  
        cloudeSprite.setScale(
            float(windowSize.x) / cloudeTexture.getSize().x * 0.7,
			float(windowSize.y) / cloudeTexture.getSize().y * 0.9 );
		cloudeSprite.setPosition(
			windowSize.x / 2.f - cloudeSprite.getGlobalBounds().width / 2.f,
			windowSize.y / 2.f - cloudeSprite.getGlobalBounds().height / 2.f );
		cloudeSprite.setColor(sf::Color(255, 255, 255, 150)); // напівпрозорий білий


        sf::Vector2f center(windowSize.x / 2.f, windowSize.y / 2.f); // центр екрану

        inputBox.setPosition(center.x, center.y + 80); // поле введення трохи нижче центра

        // центруємо інші тексти
        centerText(welcomeText, center.x, center.y - 150);
        centerText(titleText, center.x, center.y - 90);
        centerText(inputText, center.x, center.y);

        // для userInput робимо вирівнювання 
        sf::FloatRect bounds = userInput.getLocalBounds();
        userInput.setOrigin(0, bounds.top + bounds.height / 2.f);
        userInput.setPosition(inputBox.getPosition().x - inputBox.getSize().x / 2.f + 20, inputBox.getPosition().y + 4);

        centerText(hintText, center.x, center.y + 160);  // підказка внизу
    
        userInput.setString(inputString); // оновлюємо текст, який ввів користувач

        // розміщення кнопки "Rules" у правому нижньому куті
        rulesButton.setPosition(
            windowSize.x - rulesButton.getSize().x - 20.f,
            windowSize.y - rulesButton.getSize().y - 20.f );
        rulesText.setPosition(
            rulesButton.getPosition().x + 40.f,
            rulesButton.getPosition().y + 7.f );


        render(window);
    }

    return diskCount; // Повертаємо кількість дисків
}

void Menu::showRulesWindow()
{
    sf::RenderWindow rulesWin(sf::VideoMode(600, 400), "Game Rules");

    sf::Text rules;
    rules.setFont(font2);
    rules.setCharacterSize(22);
    rules.setFillColor(sf::Color::Black);
    rules.setPosition(50.f, 50.f);
    rules.setString(
        "Tower of Hanoi Rules:\n\n"
        "1. Only one disk can be moved at a time.\n"
        "2. A disk can only be moved if it is the uppermost disk.\n"
        "3. No disk may be placed on top of a smaller disk.\n"
        "\nGoal: Move the full tower to another rod."
    );

    sf::RectangleShape backButton(sf::Vector2f(120.f, 50.f));
    backButton.setFillColor(sf::Color::White);
    backButton.setOutlineThickness(4.f);
    backButton.setOutlineColor(sf::Color(60, 110, 187));
    backButton.setPosition(230.f, 320.f);

    sf::Text backText;
    backText.setFont(font2);
    backText.setString("Back");
    backText.setCharacterSize(24);
    backText.setFillColor(sf::Color::Black);
    backText.setPosition(backButton.getPosition().x + 30.f, backButton.getPosition().y + 8.f);

    while (rulesWin.isOpen())
    {
        sf::Event event;
        while (rulesWin.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                rulesWin.close();

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                float mx = static_cast<float>(event.mouseButton.x);
                float my = static_cast<float>(event.mouseButton.y);

                if (backButton.getGlobalBounds().contains(mx, my))
                    rulesWin.close();
            }
        }

        rulesWin.clear(sf::Color(240, 240, 240));
        rulesWin.draw(rules);
        rulesWin.draw(backButton);
        rulesWin.draw(backText);
        rulesWin.display();
    }
}


// Обробка подій користувача
void Menu::processEvent(sf::RenderWindow& window, sf::Event& event, bool& running, int& diskCount)
{
    if (event.type == sf::Event::Closed)
        window.close(); // Закриття вікна

    if (event.type == sf::Event::TextEntered)
    {
        if (event.text.unicode >= '0' && event.text.unicode <= '9') // Якщо натиснута цифра
        {
            inputString += static_cast<char>(event.text.unicode); // Додаємо символ
        }
        else if (event.text.unicode == 8 && !inputString.empty()) // Backspace - видалити символ
        {
            inputString.pop_back();
        }
    }

    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Escape)
        {
            running = false; // Вийти з меню
            window.close();
        }

        if (event.key.code == sf::Keyboard::Enter && !inputString.empty())
        {
            // Коли натиснуто Enter і рядок не порожній -> пробуємо перетворити текст на число
            int num = std::stoi(inputString);
            if (num >= 3)
            {
                diskCount = num;  // Зберігаємо кількість дисків
                running = false;  // Закінчуємо меню
            }
        }

    }
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    {
        float mx = static_cast<float>(event.mouseButton.x);
        float my = static_cast<float>(event.mouseButton.y);

        if (rulesButton.getGlobalBounds().contains(mx, my))
        {
            showRulesWindow(); // виклик функції, яка покаже правила
        }
    }

}

// функція, яка малює все на екран
void Menu::render(sf::RenderWindow& window)
{
    window.clear(); // очищення вікна
    window.draw(backgroundSprite);
    window.draw(cloudeSprite); 
    window.draw(welcomeText); 
    window.draw(titleText);
    window.draw(inputText);
    window.draw(inputBox);  
    window.draw(userInput);
    window.draw(hintText); 
    window.draw(rulesButton);
    window.draw(rulesText);
    window.display(); // показати усе на екрані
}

// функція для центрування тексту по центру екрана
void Menu::centerText(sf::Text& text, float x, float y)
{
    sf::FloatRect bounds = text.getLocalBounds();  // отримуємо розміри тексту
    text.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f); // встановлюємо точку кріплення в центр
    text.setPosition(x, y); // розміщуємо в центр
}

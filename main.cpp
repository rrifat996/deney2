#include <SFML/Graphics.hpp>
#include <iostream>
int main()
{
    sf::RenderWindow window(sf::VideoMode(1024,1024), "SFML Application");
    sf::View view;
    view.setSize(1024.f, 1024.f);
    view.setCenter(window.getSize().x / 2.f, window.getSize().y / 2.f);
    window.setFramerateLimit(60);

    const int gridSize = 64;
    float gridSizeF = 16.f;
    float dt = 0.f;
    sf::Clock dtClock;
    unsigned gridSizeU = static_cast<unsigned>(gridSizeF);

    sf::RectangleShape shape(sf::Vector2f(gridSizeF, gridSizeF));

    std::vector<std::vector<sf::RectangleShape>> tileMap;
    tileMap.resize(gridSize * gridSize, std::vector<sf::RectangleShape>());
    for (int x = 0; x < gridSize; x++)
    {
        tileMap[x].resize(gridSize, sf::RectangleShape());
        for (int y = 0; y < gridSize; y++)
        {
            tileMap[x][y].setSize(sf::Vector2f(gridSizeF, gridSizeF));
            tileMap[x][y].setFillColor(sf::Color::White);
            tileMap[x][y].setOutlineThickness(1.f);
            tileMap[x][y].setOutlineColor(sf::Color::Black);
            tileMap[x][y].setPosition(x * gridSizeF, y * gridSizeF);
        }
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                    window.close();
                    break;

            case sf::Event::MouseButtonPressed:
                std::cout << "pressed";
                sf::Vector2<int> vec = sf::Mouse::getPosition(window);
                std::cout << vec.x / 16 << " and " << vec.y / 16 << std::endl;
                    break;
            }

        }
        //update dt
        dt = dtClock.restart().asSeconds();

        //render
        window.clear();

        //render game elements
        window.setView(window.getDefaultView());

        for (int x = 0; x < gridSize; x++)
        {
            for (int y = 0; y < gridSize; y++)
            {
                window.draw(tileMap[x][y]);
            }
        }
        //render ui

        window.display();
    }
}
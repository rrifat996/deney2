#include <SFML/Graphics.hpp>
#include <iostream>
#define IX(i,j) ((i)+(N+2)*(j))
const int N = 64;

void diffuse ( int N, int b, float * x, float * x0, float diff, float dt )
{
    int i, j, k;
    float a=dt*diff*N*N;
    for ( k=0 ; k<20 ; k++ ) {
        for ( i=1 ; i<=N ; i++ ) {
            for ( j=1 ; j<=N ; j++ ) {
                x[IX(i,j)] = (x0[IX(i,j)] + a*(x[IX(i-1,j)]+x[IX(i+1,j)]+
                                               x[IX(i,j-1)]+x[IX(i,j+1)]))/(1+4*a);
            }
        }
       // set_bnd ( N, b, x );
    }
}


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
    const int newSize = (N + 2) * (N + 2);
    static float u[newSize], v[newSize], u_prev[newSize], v_prev[newSize];
    static float dens[newSize], dens_prev[newSize];

    for (int x = 0; x < gridSize; x++)
    {
        for (int y = 0; y < gridSize; y++)
        {
            dens_prev[IX(x,y)] = 0;
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
                    dens_prev[IX(vec.x / 16, vec.y / 16)] = 255;
                    std::cout << vec.x / 16 << " and " << vec.y / 16 << std::endl;
                    break;
            }
        }
        //updating
        diffuse(N, 0, dens, dens_prev, 1.f/100 , 1.f/500);

        //render
        window.clear();
        //render game elements
        window.setView(window.getDefaultView());

        for (int x = 0; x < gridSize; x++)
        {
            for (int y = 0; y < gridSize; y++)
            {
                dens_prev[IX(x,y)] = dens[IX(x,y)];
                sf::Color color(dens[IX(x,y)],dens[IX(x,y)],dens[IX(x,y)]);
                tileMap[x][y].setSize(sf::Vector2f(gridSizeF, gridSizeF));
                tileMap[x][y].setFillColor(color);
                tileMap[x][y].setOutlineThickness(1.f);
                tileMap[x][y].setOutlineColor(sf::Color::Black);
                tileMap[x][y].setPosition(x * gridSizeF, y * gridSizeF);

                window.draw(tileMap[x][y]);
            }
        }
        //render ui,
        window.display();
    }
}
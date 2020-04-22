#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>

const int Width = 1366,
          Height = 765;
const int Scalar = 10;
const int FieldWidth = Width / Scalar,
          FieldHeight = Height / Scalar;

int Field[FieldHeight][FieldWidth];

auto Random() -> float;
auto CountAliveNeighbours(int CurrentX, int CurrentY, int Field[FieldHeight][FieldWidth]) -> int;

int main()
{
    sf::RenderWindow Window(sf::VideoMode(Width, Height), "Game of Life");
    Window.setVerticalSyncEnabled(true);
    Window.setFramerateLimit(10);
    sf::RectangleShape Rectangles[FieldHeight][FieldWidth];

    for (int Y = 0; Y < FieldHeight; ++Y) 
    {
        for (int X = 0; X < FieldWidth; ++X) 
        {
            auto &Current = Rectangles[Y][X];
            Current.setSize(sf::Vector2f(Scalar, Scalar));
            Current.setPosition(sf::Vector2f(X * Scalar, Y * Scalar));

            Field[Y][X] = Random() > 0.5 ? 1 : 0;
        }
    }

    while (Window.isOpen())
    {
        sf::Event Event;
        while (Window.pollEvent(Event))
        {
            if (Event.type == sf::Event::Closed)
                Window.close();
        }

        Window.clear();

        int NextField[FieldHeight][FieldWidth];

        for (int Y = 0; Y < FieldHeight; ++Y) 
        {
            for (int X = 0; X < FieldWidth; ++X) 
            {
                auto &Current = Rectangles[Y][X];

                if (Field[Y][X] == 1)
                    Current.setFillColor(sf::Color::White);
                else
                    Current.setFillColor(sf::Color::Black);

                Window.draw(Current);

                auto &Next = NextField[Y][X];
                // ful
                int AliveNeighbours = CountAliveNeighbours(X, Y, Field);

                if (AliveNeighbours == 3) 
                    Next = 1;
                else if (Field[Y][X] == 1 && AliveNeighbours == 2)
                    Next = 1;
                else
                    Next = 0;
            }
        }
        Window.display();

        for (int Y = 0; Y < FieldHeight; ++Y) 
        {
            for (int X = 0; X < FieldWidth; ++X) 
            {
                Field[Y][X] = NextField[Y][X];
            }
        }
    }

    return 0;
}

auto Random() -> float
{
    static std::random_device SourceRNG;
    static std::default_random_engine RNG(SourceRNG());

    std::uniform_real_distribution<float> Distribution;

    return Distribution(RNG);
}

auto CountAliveNeighbours(int CurrentX, int CurrentY, int Field[FieldHeight][FieldWidth]) -> int
{
    int Count = 0;

    for (int Y = -1; Y < 2; ++Y) 
    {
        for (int X = -1; X < 2; ++X) 
        {
            if (X == 0 && Y == 0)
                continue;

            int SumX = CurrentX + X,
                SumY = CurrentY + Y;

            // That sucks
            // Make it ful pruf
            if (SumY >= 0 && SumY <= FieldHeight &&
                SumX >= 0 && SumX <= FieldWidth)
                if (Field[SumY][SumX] == 1)
                    ++Count;
        }
    }

    return Count;
}

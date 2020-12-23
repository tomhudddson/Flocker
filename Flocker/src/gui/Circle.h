#pragma once

#include "SFML/Graphics.hpp"

namespace flock
{

/*
Dummy class to provide gui usage and nameing consistency across the program.
*/
class Circle
{
public:
    Circle(const float radius, const float midx, const float midy);

    void Update();
    void Render(sf::RenderWindow& window);

    void SetMidpoint(const sf::Vector2f& pos);
    inline void SetRadius(const float radius)
    {
        m_Circle.setRadius(radius);
    }
    inline void SetFillColor(const sf::Color color)
    {
        m_Circle.setFillColor(color);
    }

private:
    sf::CircleShape  m_Circle;
    sf::Vector2f     m_Midpoint;
};

}
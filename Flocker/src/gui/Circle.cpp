#include "Circle.h"

namespace flock
{

Circle::Circle(const float radius, const float midx, const float midy)
    : m_Circle(radius),
    m_Midpoint(midx, midy)
{
    m_Circle.setPointCount(100);
}

void Circle::Update()
{
    
}

void Circle::Render(sf::RenderWindow& window)
{
    window.draw(m_Circle);
}

void Circle::SetMidpoint(const sf::Vector2f& pos)
{
    m_Midpoint = pos;
    m_Circle.setPosition(sf::Vector2f(pos.x - m_Circle.getRadius(),
                                      pos.y - m_Circle.getRadius()));
}

}
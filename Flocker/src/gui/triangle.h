#pragma once

#include <SFML/Graphics.hpp>

namespace flock
{

class Triangle
{
public:
    Triangle(const sf::Vector2f& p1, const sf::Vector2f& p2, const sf::Vector2f& p3);
    Triangle(const sf::Vector2f& midpoint, const float base, const float height, const float angle, const sf::Color& color);
    
    void Update(const float dt);
    void Render(sf::RenderWindow& win);
    void Move(const float speed);
    void Rotate(const float angle);
    
    // Set the position of the midpoint of the triangle. 
    void SetX(const float x);
    void SetY(const float y);

    inline const sf::VertexArray& GetVertices() const { return m_Vertices; }
    inline sf::Vector2f GetMidpoint() { return m_Midpoint; }

private:
    float            m_Base;
    float            m_Height; 
    sf::Vector2f     m_Midpoint;
    sf::VertexArray  m_Vertices;
    float            m_Angle;


    void ReCalculateVertices();
};

}
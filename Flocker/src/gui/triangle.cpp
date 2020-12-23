#include "triangle.h"

#include <math.h>
#include <iostream>

# define PI           3.14159265358979323846

namespace flock
{

Triangle::Triangle(const sf::Vector2f& p1, const sf::Vector2f& p2, const sf::Vector2f& p3)
{
    m_Vertices.setPrimitiveType(sf::Triangles);
    m_Vertices.append(sf::Vertex(p1, sf::Color::Red));
    m_Vertices.append(sf::Vertex(p2, sf::Color::Red));
    m_Vertices.append(sf::Vertex(p3, sf::Color::Red));
}

Triangle::Triangle(const sf::Vector2f& midpoint,
                   const float base, const float height,
                   const float angle,
                   const sf::Color& color)
{
    m_Midpoint = midpoint;

    sf::Vector2f p1 = { midpoint.x, midpoint.y - height / 2 };             // top
    sf::Vector2f p2 = { midpoint.x - base / 2, midpoint.y + height / 2 };  // bottom left
    sf::Vector2f p3 = { midpoint.x + base / 2, midpoint.y + height / 2 };  // bottom right

    m_Vertices.setPrimitiveType(sf::Triangles);
    m_Vertices.append(sf::Vertex(p1, sf::Color::Red));
    m_Vertices.append(sf::Vertex(p2, sf::Color::Red));
    m_Vertices.append(sf::Vertex(p3, sf::Color::Red));

    Rotate(angle);
}

void Triangle::ReCalculateVertices()
{

}

void Triangle::Update(const float dt)
{

}

void Triangle::Render(sf::RenderWindow& window)
{
    window.draw(m_Vertices);
}

void Triangle::Move(const float speed)
{
    float xoffset = speed * (float)std::sin(PI / 180 * m_Angle);
    float yoffset = speed * (float)std::cos(PI / 180 * m_Angle);

    sf::Transform translation;
    translation.translate(xoffset, -yoffset);

    m_Vertices[0].position = translation.transformPoint(m_Vertices[0].position);
    m_Vertices[1].position = translation.transformPoint(m_Vertices[1].position);
    m_Vertices[2].position = translation.transformPoint(m_Vertices[2].position);
    m_Midpoint = translation.transformPoint(m_Midpoint);
}

void Triangle::Rotate(const float angle)
{
    m_Angle = angle;

    sf::Transform rotation;
    rotation.rotate(angle, m_Midpoint);

    // No need to rotate midpoint. It is the center of rotation so stays 
    // in the same position.
    m_Vertices[0].position = rotation.transformPoint(m_Vertices[0].position);
    m_Vertices[1].position = rotation.transformPoint(m_Vertices[1].position);
    m_Vertices[2].position = rotation.transformPoint(m_Vertices[2].position);
}

void Triangle::SetX(const float x) 
{
    // Calculate distance to translate so the new positions in regards to rotation 
    // do not have to be calcualted. TODO: find out whether this is more efficient
    // than working out the positions manually.
    float d = x - m_Midpoint.x;

    sf::Transform translation;
    translation.translate(d, 0);
    m_Vertices[0].position = translation.transformPoint(m_Vertices[0].position);
    m_Vertices[1].position = translation.transformPoint(m_Vertices[1].position);
    m_Vertices[2].position = translation.transformPoint(m_Vertices[2].position);
    m_Midpoint = translation.transformPoint(m_Midpoint);

    //m_Vertices[0].position = { m_Midpoint.x, m_Midpoint.y - m_Height / 2 };               // top
    //m_Vertices[1].position = { m_Midpoint.x - m_Base / 2, m_Midpoint.y + m_Height / 2 };  // bottom left
    //m_Vertices[2].position = { m_Midpoint.x + m_Base / 2, m_Midpoint.y + m_Height / 2 };  // bottom right
}

void Triangle::SetY(const float y) 
{
    float d = y - m_Midpoint.y;

    sf::Transform translation;
    translation.translate(0, d);
    m_Vertices[0].position = translation.transformPoint(m_Vertices[0].position);
    m_Vertices[1].position = translation.transformPoint(m_Vertices[1].position);
    m_Vertices[2].position = translation.transformPoint(m_Vertices[2].position);
    m_Midpoint = translation.transformPoint(m_Midpoint);
}

}
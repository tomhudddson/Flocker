#pragma once

#include <vector>

#include "../gui/triangle.h"
#include "../gui/Circle.h"

namespace flock
{

class Agent
{
public:
    Agent(const sf::Vector2f& midpoint, const float base, const float height, const float angle);

    void Update(float dt, 
                const unsigned int screenWidth, const unsigned int screenHeight,
                const sf::Vector2f& avgPos, float kc, float ks, float ka);
    void Render(sf::RenderWindow& window);

    inline void SetSpeed(const float speed) { m_Speed = speed; }
    inline void SetLocalRadius(const float radius, const sf::Color& color)
    {
        m_LocalRadius = radius;
        m_RadiusCircle.SetRadius(radius);
        m_RadiusCircle.SetFillColor(color);
    }
    inline void SetLocalRadiusColor(const sf::Color& color) 
    {
        m_RadiusCircle.SetFillColor(color);
    }

    inline sf::Vector2f GetMidpoint() { return m_Body.GetMidpoint(); }

private:
    float  m_LocalRadius;
    float  m_Speed;

    Triangle  m_Body;
    Circle    m_RadiusCircle;

    enum class OffScreenState
    {
        INSIDE,
        TOP,
        BOTTOM,
        LEFT,
        RIGHT
    };


    void Move(const unsigned int simWidth, const unsigned int simHeight);

    // Determine whether the agent is fully off the screen.
    OffScreenState IsOffScreen(const unsigned int simWidth, const unsigned int simHeight);
};

}

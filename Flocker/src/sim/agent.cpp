#include "Agent.h"

#include <iostream>

namespace flock
{

Agent::Agent(const sf::Vector2f& midpoint, const float base, const float height, const float angle)
    : m_LocalRadius(0.0f),
    m_ShowLocalRadius(false),
    m_Speed(0.0f),
    m_Body(midpoint, base, height, angle, sf::Color::Red),
    m_RadiusCircle(0.0f, 0.0f, 0.0f)
{
}

static float ValidateMultiplier(float& multiplier) 
{
    if (multiplier < 0.f) 
        return 0.f;
    else if (multiplier > 1.f)
        return 1.f;
    else
        return multiplier;
}

void Agent::Update(float dt, 
                   const unsigned int simWidth, const unsigned int simHeight,
                   const sf::Vector2f& localAgentsAvgPos,
                   float kc, float ks, float ka)
{
    ValidateMultiplier(kc);
    ValidateMultiplier(ks);
    ValidateMultiplier(ka);

    this->Move(simWidth, simHeight);
    m_Body.Move(m_Speed);
    m_Body.Update(dt);

    m_RadiusCircle.SetMidpoint(m_Body.GetMidpoint());
}

void Agent::Render(sf::RenderWindow& window)
{
    if (m_ShowLocalRadius)
        m_RadiusCircle.Render(window);
    m_Body.Render(window);
}

void Agent::Move(const unsigned int simWidth, const unsigned int simHeight)
{
    switch (IsOffScreen(simWidth, simHeight))
    {
    case OffScreenState::TOP:
        m_Body.SetY(simHeight);
        break;
    case OffScreenState::BOTTOM:
        m_Body.SetY(0);
        break;
    case OffScreenState::RIGHT:
        m_Body.SetX(0);
        break;
    case OffScreenState::LEFT:
        m_Body.SetX(simWidth);
        break;
    }
}

Agent::OffScreenState Agent::IsOffScreen(const unsigned int simWidth, const unsigned int simHeight)
{
    // Very rudimentary. TODO: could change to midpoint based checking.

    // Top side.
    if (m_Body.GetVertices()[0].position.y < 0 &&
        m_Body.GetVertices()[1].position.y < 0 &&
        m_Body.GetVertices()[2].position.y < 0)
    {
        return OffScreenState::TOP;
    }

    // Bottom side.
    else if (m_Body.GetVertices()[0].position.y > simHeight &&
             m_Body.GetVertices()[1].position.y > simHeight &&
             m_Body.GetVertices()[2].position.y > simHeight)
    {
        return OffScreenState::BOTTOM;
    }

    // Right hand side.
    else if (m_Body.GetVertices()[0].position.x > simWidth &&
             m_Body.GetVertices()[1].position.x > simWidth &&
             m_Body.GetVertices()[2].position.x > simWidth)
    {
        return OffScreenState::RIGHT;
    }

    // Left hande side.
    else if (m_Body.GetVertices()[0].position.x < 0 &&
             m_Body.GetVertices()[1].position.x < 0 &&
             m_Body.GetVertices()[2].position.x < 0)
    {
        return OffScreenState::LEFT;
    }

    return OffScreenState::INSIDE;
}


}
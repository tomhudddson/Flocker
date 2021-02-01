#include "simulation.h"

#include <stdlib.h>
#include <time.h>
#include <math.h>

namespace flock
{

Simulation::Simulation(const unsigned int simWidth, const unsigned int simHeight)
    : m_SimWidth(simWidth), m_SimHeight(simHeight)
{
    m_LocalRadius = FLOCK_DEF_LOCAl_RAD;
    m_Kc = FLOCK_DEF_COHESION;
    m_Ks = FLOCK_DEF_SEPARATION;
    m_Ka = FLOCK_DEF_ALIGNMENT;
}

Simulation::~Simulation()
{}

static float Dist(const sf::Vector2f& p1, const sf::Vector2f& p2)
{
    return std::sqrt(((p1.x - p2.x) * (p1.x - p2.x)) +
                     ((p1.y - p2.y) * (p1.y - p2.y)));
}

static float ValidateMultiplier(const float multiplier)
{
    if (multiplier < 0.f)
        return 0.f;
    else if (multiplier > 1.f)
        return 1.f;
    else
        return multiplier;
}

void Simulation::Update(const float dt,
                          const float kcSliderVal,
                          const float ksSliderVal,
                          const float kaSliderVal)
{
    m_Kc = ValidateMultiplier(kcSliderVal);
    m_Ks = ValidateMultiplier(ksSliderVal);
    m_Ka = ValidateMultiplier(kaSliderVal);

    float xSum = 0;
    float ySum = 0;
    int localAgents = 0;
    sf::Vector2f avgPos;

    for (auto& agent : m_Agents)
    {
        // Find the coordinates of any agent in the local radius of this agent.
        for (auto& externAgent : m_Agents)
        {
            // TODO: add comparison operator for Agent class to compate agent
            // and externAgent to see if they are the same and skip that 
            // position.

            float d = Dist(agent.GetMidpoint(), externAgent.GetMidpoint());
            if (d <= m_LocalRadius)
            {
                xSum += externAgent.GetMidpoint().x;
                ySum += externAgent.GetMidpoint().y;
                localAgents++;
                agent.SetLocalRadiusColor(sf::Color(0, 234, 234, 50));
            }
        }

        avgPos.x = xSum / localAgents;
        avgPos.y = ySum / localAgents;

        this->SimulateCohesion(avgPos);
        this->SimulateSeparation(avgPos);
        this->SimulateAlignment(avgPos);
        agent.Update(dt, m_SimWidth, m_SimHeight, avgPos, m_Kc, m_Ks, m_Ka);

        xSum = 0;
        ySum = 0;
        localAgents = 0;
    }
}

void Simulation::Render(sf::RenderWindow& window)
{
    for (auto& agent : m_Agents)
    {
        agent.Render(window);
    }
}

void Simulation::SpawnAgents(const int n)
{
    srand((unsigned int)time(NULL));

    for (int i = 0; i < n; i++)
    {
        sf::Vector2f pos = { (float)(rand() % m_SimWidth), (float)(rand() % m_SimHeight) };
        float rot = (float)(rand() % 360);

        Agent agent(pos, 10, 25, rot);
        agent.SetSpeed(1.5f);
        agent.SetLocalRadius(200.f, sf::Color(234, 234, 234, 50));
        m_Agents.push_back(agent);
    }
}

void Simulation::SimulateCohesion(const sf::Vector2f& avgPos)
{
    // Calculate the angle 
}

void Simulation::SimulateSeparation(const sf::Vector2f& avgPos)
{

}

void Simulation::SimulateAlignment(const sf::Vector2f& avgPos)
{

}

}
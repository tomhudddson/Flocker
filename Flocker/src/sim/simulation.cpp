#include "simulation.h"

#include <stdlib.h>
#include <time.h>

namespace flock
{

Simulation::Simulation(const unsigned int simWidth, const unsigned int simHeight)
    : m_SimWidth(simWidth), m_SimHeight(simHeight)
{
    m_LocalRadius = FLOCK_DEF_LOCAl_RAD;
    m_Cohesion = FLOCK_DEF_COHESION;
    m_Separation = FLOCK_DEF_SEPARATION;
    m_Alignment = FLOCK_DEF_ALIGNMENT;
}

Simulation::~Simulation()
{}

void Simulation::Update(const float dt) 
{
    for (auto& agent : m_Agents)
    {
        agent.Update(dt, m_SimWidth, m_SimHeight);
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

}
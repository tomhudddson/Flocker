#pragma once

// Default simulation values.
#define FLOCK_DEF_LOCAl_RAD   30
#define FLOCK_DEF_COHESION    0.0f
#define FLOCK_DEF_SEPARATION  0.0f
#define FLOCK_DEF_ALIGNMENT   0.0f

#define FLOCK_MULTIPLIER_INCREMENT 0.05f

#include <SFML/Graphics.hpp>
#include <vector>

#include "Agent.h"

namespace flock
{

enum class Multiplier
{
    COHESION,
    SEPARATION,
    ALIGNMENT
};

class Simulation
{
public:
    Simulation(const unsigned int simWidth, const unsigned int simHeight);
    ~Simulation();

    void Update(const float dt);
    void Render(sf::RenderWindow& window);

    void SpawnAgents(const int n);
    void ShowAgentsLocalRadius(const bool render);

    void IncrementCohesionMultiplier(float increment);
    void IncrementSeparationMultiplier(float increment);
    void IncrementAlignmentMultiplier(float increment);
    inline float GetCohesionMultipler() { return m_Kc; }
    inline float GetSeparationMultipler() { return m_Ks; }
    inline float GetAlignmentMultiplier() { return m_Ka; }

private:    
    unsigned int  m_SimWidth;
    unsigned int  m_SimHeight;

    std::vector<Agent>  m_Agents;

    // The local radius is the radius in which each agent can see other agents
    // and interact with them. Outside of this radius, other agents will have
    // no effect on each agent.
    unsigned int  m_LocalRadius;

    // The cohesion behaviour is the desire for agents to steer to move 
    // towards the crowd. The value must be in the range [0, 1] inclusive.
    float  m_Kc; 

    // The separation behaviour is the desire for agents to steer away from a 
    // crowd. The value must be in the range [0, 1] inclusive.
    float  m_Ks;

    // The alignment behaviuour is the desire for agents to steer in the same
    // direction of the flock. The value must be in the range [0, 1] inclusive.
    float  m_Ka;

    void SimulateCohesion(const sf::Vector2f& avgPos);
    void SimulateSeparation(const sf::Vector2f& avgPos);
    void SimulateAlignment(const sf::Vector2f& avgPos);
};

}
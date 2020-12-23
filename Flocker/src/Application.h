#pragma once

#include <string>
#include <SFML/Graphics.hpp>

#include "sim/simulation.h"
#include "util/Timer.h"

namespace flock
{

class Application
{
public:
    Application(const std::string& title, const int w, const int h);

    void Run();

private:    
    std::string       m_Title;
    sf::RenderWindow  m_Window;
    Simulation        m_Sim;

    int           m_Frames;
    int           m_Updates;
    timerCount_t  m_Timer;

    void Update();
    void Render();

    void UpdateTitle();
};

}
#pragma once

#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <string>


#include "sim/simulation.h"
#include "util/Timer.h"
#include "gui/Trackbar.h"

namespace flock
{

class Application
{
public:
    
    Application(const std::string& title, const int w, const int h, const int nCmdShow);
    
    void Run();

private:
    int m_NCmdShow;
    HWND m_Hwnd;
    HWND m_HSfmlView;

    sf::RenderWindow  m_Window;
    int m_WinWidth;
    int m_WinHeight;
    Simulation        m_Sim;

    Trackbar  m_CohesionSlider;
    Trackbar  m_SeparationSlider;
    Trackbar  m_AlignmentSlider;

    int           m_Frames;
    int           m_Updates;
    timerCount_t  m_Timer;

    void Update();
    void Render();

    void UpdateTitle();
};

}
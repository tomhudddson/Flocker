#include "Application.h"

#define DEBUG_MODE

#include <sstream>

#include "util/Timer.h"

namespace flock
{

Application::Application(const std::string& title, const int w, const int h)
    : m_Title(title),
    m_Window(sf::VideoMode(w, h), title),
    m_Sim(w, h),
    m_Frames(0), m_Updates(0),
    m_Timer(0)
{

}

static void UpdateDt(timerCount_t& lastTime, float& dt)
{
    static const float ns = 1000000000.0f / 60.0f;
    auto now = Timer::GetNanoSeconds();
    dt += Timer::Duration(lastTime, now) / ns;
    lastTime = now;
}

void Application::UpdateTitle()
{
    if (Timer::GetMilliSeconds() - m_Timer > 1000)
    {
        m_Timer += 1000;

        std::stringstream ss;
#ifdef DEBUG_MODE            
        ss << "Flocker | "
            << m_Updates << " ups, "
            << m_Frames << " fps | "
            << "Kc: " << m_Sim.GetCohesionMultipler() << " "
            << "Ks: " << m_Sim.GetSeparationMultipler() << " "
            << "Ka: " << m_Sim.GetAlignmentMultiplier();
#else
        ss << "Flocker";
#endif

        m_Window.setTitle(ss.str());
        m_Updates = 0;
        m_Frames = 0;
    }
}

void Application::HandleKeyPress()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) 
        m_Sim.IncrementCohesionMultiplier(-FLOCK_MULTIPLIER_INCREMENT);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        m_Sim.IncrementCohesionMultiplier(FLOCK_MULTIPLIER_INCREMENT);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        m_Sim.IncrementSeparationMultiplier(-FLOCK_MULTIPLIER_INCREMENT);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        m_Sim.IncrementSeparationMultiplier(FLOCK_MULTIPLIER_INCREMENT);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
        m_Sim.IncrementAlignmentMultiplier(-FLOCK_MULTIPLIER_INCREMENT);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
        m_Sim.IncrementAlignmentMultiplier(FLOCK_MULTIPLIER_INCREMENT);
}

void Application::Update()
{
    sf::Event event;
    while (m_Window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            m_Window.close();
            break;

        case sf::Event::KeyPressed:
            HandleKeyPress();
            break;
        }
    }

    m_Sim.Update(1.0f);
}

void Application::Render()
{
    m_Window.clear();
    m_Sim.Render(m_Window);
    m_Window.display();
}

void Application::Run()
{
    m_Sim.SpawnAgents(50);

    float dt = 0.0f;

    auto lastTime = Timer::GetNanoSeconds();
    m_Timer = Timer::GetMilliSeconds();

    while (m_Window.isOpen())
    {
        UpdateDt(lastTime, dt);

        while (dt >= 1)
        {
            Update();
            m_Updates++;
            dt--;
        }

        Render();
        m_Frames++;

        UpdateTitle();
    }
}

}
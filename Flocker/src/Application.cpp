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

void Application::Update()
{
    sf::Event event;
    while (m_Window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            m_Window.close();
    }

    m_Sim.Update(1.0f);
}

void Application::Render()
{
    m_Window.clear();
    m_Sim.Render(m_Window);
    m_Window.display();
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
        ss << "Flocker | " << m_Updates << " ups, " << m_Frames << " fps";
#else
        ss << "Flocker";
#endif

        m_Window.setTitle(ss.str());
        m_Updates = 0;
        m_Frames = 0;
    }
}

void Application::Run()
{
    m_Sim.SpawnAgents(3);

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
#include "Application.h"

#define DEBUG_MODE

#include <sstream>

#include "util/Timer.h"
#include "gui/Trackbar.h"

namespace flock 
{

Application::Application(const std::string& title, const int w, const int h, const int nCmdShow)
    : m_NCmdShow(nCmdShow), m_Window(), m_WinWidth(w), m_WinHeight(h), m_Sim(w * 0.8, h),
      m_Frames(0), m_Updates(0), m_Timer(0)
{
}

LRESULT CALLBACK WndCallback(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}


static void InitWndClass(WNDCLASS& wc)
{
    wc.style = 0;
    wc.lpfnWndProc = &WndCallback;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = GetModuleHandle(NULL);
    wc.hIcon = NULL;
    wc.hCursor = NULL;
    wc.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_BACKGROUND);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = "Flocker";
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
        ss << "Flocker | " << m_Updates << " ups, " << m_Frames << " fps" << "| Kc: " << m_CohesionSlider.GetValue()
                                                                          << "| Ks: " << m_SeparationSlider.GetValue()
                                                                          << "| Ka: " << m_AlignmentSlider.GetValue();
#else
        ss << "Flocker";
#endif

        //m_Window.setTitle(ss.str()");
        SetWindowText(m_Hwnd, ss.str().c_str());
        m_Updates = 0;
        m_Frames = 0;
    }
}

void Application::Update()
{
    sf::Event event;
    while (m_Window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            m_Window.close();
    }

    m_Sim.Update(1.0f, m_CohesionSlider.GetValue(), m_SeparationSlider.GetValue(), m_AlignmentSlider.GetValue());
}

void Application::Render()
{
    m_Window.clear();
    m_Sim.Render(m_Window);
    m_Window.display();
}

void Application::Run()
{
    WNDCLASS wc;
    InitWndClass(wc);
    RegisterClass(&wc);

    // Create the main window.
    m_Hwnd = CreateWindow("Flocker", "Flocker", WS_SYSMENU | WS_VISIBLE, 0, 0, m_WinWidth, m_WinHeight, NULL, NULL, GetModuleHandle(NULL), NULL);

    // Create SFML view.
    DWORD style = WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS;
    m_HSfmlView = CreateWindow("STATIC", NULL, style, 0, 0, m_Sim.GetWidth(), m_Sim.GetHeight(), m_Hwnd, NULL, GetModuleHandle(NULL), NULL);

    m_CohesionSlider.Init(m_Hwnd, m_Sim.GetWidth() + 20, 20, 200, 40, 0, 1000, 100);
    m_SeparationSlider.Init(m_Hwnd, m_Sim.GetWidth() + 20, 80, 200, 40, 0, 1000, 100);
    m_AlignmentSlider.Init(m_Hwnd, m_Sim.GetWidth() + 20, 140, 200, 40, 0, 1000, 100);

    m_Window.create(m_HSfmlView);

    m_Sim.SpawnAgents(3);

    float dt = 0.0f;

    auto lastTime = Timer::GetNanoSeconds();
    m_Timer = Timer::GetMilliSeconds();

    MSG msg = { };
    msg.message = ~WM_QUIT;
    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            // If a message was waiting in the message queue, process it.
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
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

    DestroyWindow(m_Hwnd);
    UnregisterClass("SFML App", GetModuleHandle(NULL));
}

};

/*











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

*/
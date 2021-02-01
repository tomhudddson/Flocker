#include "Trackbar.h"

namespace flock 
{

void Trackbar::Init(HWND parentHandle, 
                      const int x, const int y,
                      const int w, const int h,
                      const unsigned int min,
                      const unsigned int max,
                      const unsigned int divisor)
{
    m_Min = min;
    m_Max = max;
    m_Divisor = divisor;

    m_Icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
    m_Icex.dwICC = ICC_BAR_CLASSES;
    InitCommonControlsEx(&m_Icex);

    m_TrackbarHandle = CreateWindowEx(
        0,
        TRACKBAR_CLASS,
        "Trackbar Control",
        WS_CHILD | WS_VISIBLE | TBS_AUTOTICKS | TBS_ENABLESELRANGE,
        x, y, w, h,
        parentHandle,
        NULL,
        GetModuleHandle(NULL),
        NULL
    );

    SendMessage(m_TrackbarHandle, TBM_SETPOS, TRUE, 0);
}

float Trackbar::GetValue()
{
    LRESULT val = SendMessage(m_TrackbarHandle, TBM_GETPOS, 0, 0);
    return (float)((float)val / (float)m_Divisor);
}

};
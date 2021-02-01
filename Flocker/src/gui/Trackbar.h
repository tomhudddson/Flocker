#pragma once

#include <Windows.h>
#include <commctrl.h>

namespace flock
{

class Trackbar
{
public:
    void Init(HWND parentHandle,
              const int x, const int y,
              const int w, const int h,
              const unsigned int min,
              const unsigned int max,
              const unsigned int divisor);

    float GetValue();

private:
    unsigned int m_Min;
    unsigned int m_Max;
    unsigned int m_Divisor;

    INITCOMMONCONTROLSEX m_Icex;
    HWND m_TrackbarHandle;

};

};
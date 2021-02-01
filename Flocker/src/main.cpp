#include "Application.h"

#include <Windows.h>

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{
    flock::Application app("Flocker", 1366, 768, nCmdShow);
    app.Run();

    return 0;
}
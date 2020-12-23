#include "Application.h"

int main()
{
    flock::Application app("Flocker", 1366, 768);
    app.Run();

    return 0;
}

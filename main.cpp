#include <app/app.h>

int main()
{
    App app;

    app.Init();
    app.Run();
    app.Destroy();

    return 0;
}

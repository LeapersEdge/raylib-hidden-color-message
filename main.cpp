#include "raylib.h"     // sudo pacman -S raylib
#include "MyGUI.h"
#include "Game.h"
#include "VectorD.h"

#include <ctime>

constexpr unsigned int SCREEN_WIDTH = 1080;
constexpr unsigned int SCREEN_HEIGHT = 720;

int main()
{
    // raylib init
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "pipiPOPO watermelon");
    SetTargetFPS(25);
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    
    Game game;
    
    float delta_time = 0.0f;
    
    game.Init();

    // main loop
    while(!WindowShouldClose())
    {
        const clock_t begin_time = clock();
        
        game.Update(delta_time);

        BeginDrawing();
        ClearBackground(WHITE);
        game.Render();
        game.Post_Render();
        EndDrawing();

        delta_time = float(clock() - begin_time) / CLOCKS_PER_SEC;
    }

    game.Shutdown();
    CloseWindow();

    return 0;
}

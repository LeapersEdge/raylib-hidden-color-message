#pragma once

#include "raylib.h"
#include <vector>
#include "MyGUI.h"
#include "VectorD.h"

class Game
{
public:
    Game();
public:
    void Init();
    void Shutdown();

    void Update(float& delta_time);
    void Render();
    void Post_Render();
private:
    void DrawLetter(char letter, popo::Vector2D position);
private:
    MyGUI gui;

    std::vector<char> letters;
    unsigned char* bmp_data;
    popo::Vector2D letter_size;
    popo::Vector2D bitmap_size;

    std::vector<Color> red_light_colors;
    std::vector<Color> red_dark_colors;
};
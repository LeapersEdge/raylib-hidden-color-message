#pragma once

#include "raylib.h"
#include <vector>
#include "MyGUI.h"
#include "VectorD.h"
#include <string>
#include <random>

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
    void Draw_Letter(char letter, popo::Vector2D position, std::mt19937& rng);
private:
    MyGUI gui;

    std::vector<char> letters;
    std::string bmp_data_path;
    unsigned char* bmp_data;
    popo::Vector2D letter_size;
    popo::Vector2D bitmap_size;

    std::string message;
    int rng_seed;

    std::vector<Color> red_light_colors;
    std::vector<Color> red_dark_colors;
    std::uniform_int_distribution<int> red_light_colors_dist;
    std::uniform_int_distribution<int> red_dark_colors_dist;
};
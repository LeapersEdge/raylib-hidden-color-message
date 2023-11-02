#include "Game.h"
#include <algorithm>
#include "Bitmap.h"
#include <fstream>

Game::Game() 
    : 
    gui(true),
    zero_ten_dist(0, 10),
    camera_position(0, 0),
    text_scale(1),
    camera_speed(1),
    color_dist(0,255),
    light_color_dist(200, 225),
    dark_color_dist(0, 180)
{
    bmp_data = popo::read_BMP("./resources/Consolas13x24.bmp");
    letter_size = popo::Vector2D(13, 24);
    bitmap_size = popo::size_BMP("./resources/Consolas13x24.bmp");
}

void Game::Init()
{
    letters.push_back(' ');
    letters.push_back('!');
    letters.push_back('"');
    letters.push_back('#');
    letters.push_back('$');
    letters.push_back('%');
    letters.push_back('&');
    letters.push_back('\'');
    letters.push_back('(');
    letters.push_back(')');
    letters.push_back('*');
    letters.push_back('+');
    letters.push_back(',');
    letters.push_back('-');
    letters.push_back('.');
    letters.push_back('/');
    letters.push_back('0');
    letters.push_back('1');
    letters.push_back('2');
    letters.push_back('3');
    letters.push_back('4');
    letters.push_back('5');
    letters.push_back('6');
    letters.push_back('7');
    letters.push_back('8');
    letters.push_back('9');
    letters.push_back(':');
    letters.push_back(';');
    letters.push_back('<');
    letters.push_back('=');
    letters.push_back('>');
    letters.push_back('?');
    letters.push_back('@');
    letters.push_back('A');
    letters.push_back('B');
    letters.push_back('C');
    letters.push_back('D');
    letters.push_back('E');
    letters.push_back('F');
    letters.push_back('G');
    letters.push_back('H');
    letters.push_back('I');
    letters.push_back('J');
    letters.push_back('K');
    letters.push_back('L');
    letters.push_back('M');
    letters.push_back('N');
    letters.push_back('O');
    letters.push_back('P');
    letters.push_back('Q');
    letters.push_back('R');
    letters.push_back('S');
    letters.push_back('T');
    letters.push_back('U');
    letters.push_back('V');
    letters.push_back('W');
    letters.push_back('X');
    letters.push_back('Y');
    letters.push_back('Z');
    letters.push_back('[');
    letters.push_back('\\');
    letters.push_back(']');
    letters.push_back('^');
    letters.push_back('_');
    letters.push_back('`');
    letters.push_back('a');
    letters.push_back('b');
    letters.push_back('c');
    letters.push_back('d');
    letters.push_back('e');
    letters.push_back('f');
    letters.push_back('g');
    letters.push_back('h');
    letters.push_back('i');
    letters.push_back('j');
    letters.push_back('k');
    letters.push_back('l');
    letters.push_back('m');
    letters.push_back('n');
    letters.push_back('o');
    letters.push_back('p');
    letters.push_back('q');
    letters.push_back('r');
    letters.push_back('s');
    letters.push_back('t');
    letters.push_back('u');
    letters.push_back('v');
    letters.push_back('w');
    letters.push_back('x');
    letters.push_back('y');
    letters.push_back('z');
    letters.push_back('{');
    letters.push_back('|');
    letters.push_back('}');
    letters.push_back('~');
}

void Game::Shutdown()
{
    gui.Shutdown();
    delete[] bmp_data;
}

// update for game logic
void Game::Update(float& delta_time)
{
    if (gui.generate_message)
    {
        gui.generate_message = false;
        message = gui.message;

        rng_seed = rand();
    }

    if (IsKeyDown(KEY_UP))
        camera_position.y -= camera_speed;
    if (IsKeyDown(KEY_DOWN))
        camera_position.y += camera_speed;
    if (IsKeyDown(KEY_LEFT))
        camera_position.x -= camera_speed;
    if (IsKeyDown(KEY_RIGHT))
        camera_position.x += camera_speed; 

    if (IsKeyPressed(KEY_R))
    {
        camera_position.x = 0;
        camera_position.y = 0;
        camera_speed = 1;
    }

    if (IsKeyDown(KEY_KP_ADD) && camera_speed < 100)
        camera_speed++;
    if (IsKeyDown(KEY_KP_SUBTRACT) && camera_speed > 1)
        camera_speed--;

    text_scale = gui.message_text_scale;
}

// rendering graphics
void Game::Render()
{
    std::mt19937 rng(rng_seed);
    int y = 0;
    int x = 0;
    for (int i = 0; i < message.size(); i++, x++)
    {
        if (message[i] == '\n')
        {
            y++;
            x = -1;
            continue;
        }
        Draw_Letter(message[i], popo::Vector2D(x * letter_size.x, y * letter_size.y), rng);
    }
}

// post render function (stuff is drawn over whats in render)
void Game::Post_Render()
{
    gui.Render();
}

// -------------------------------------------------------
// private functions
// -------------------------------------------------------

void Game::Draw_Letter(char letter, popo::Vector2D position, std::mt19937 &rng)
{   
    if(std::find(letters.begin(), letters.end(), letter) != letters.end()) 
    {
        int index = std::distance(letters.begin(), std::find(letters.begin(), letters.end(), letter));
        int x_index = index % (int)(bitmap_size.x / letter_size.x);
        int y_index = index / (int)(bitmap_size.x / letter_size.x);
        
        for (int y = 0; y < letter_size.y; y++)
        {
            for (int x = 0; x < letter_size.x; x++)
            {
                if (bmp_data[(unsigned int)((bitmap_size.y - (y_index * letter_size.y + y) - 1) * bitmap_size.x + x_index * letter_size.x + x) * 3] == 0)
                {                
                    DrawRectangle(
                        position.x * text_scale + x * text_scale - camera_position.x, 
                        position.y * text_scale + y * text_scale - camera_position.y,
                        text_scale, 
                        text_scale, 
                        {light_color_dist(rng), color_dist(rng), color_dist(rng), 255}
                    );
                }
                else
                {
                    int i = zero_ten_dist(rng);
                    if (i < 7)
                        DrawRectangle(
                            position.x * text_scale + x * text_scale - camera_position.x, 
                            position.y * text_scale + y * text_scale - camera_position.y, 
                            text_scale,
                            text_scale,
                            {dark_color_dist(rng), color_dist(rng), color_dist(rng), 255}
                        );
                    else
                        DrawRectangle(
                            position.x * text_scale + x * text_scale - camera_position.x, 
                            position.y * text_scale + y * text_scale - camera_position.y, 
                            text_scale,
                            text_scale,
                            {light_color_dist(rng), color_dist(rng), color_dist(rng), 255}
                        );
                }
            }
        }
    }
}

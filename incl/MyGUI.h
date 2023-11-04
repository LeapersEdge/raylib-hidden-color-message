#pragma once

#include "rlImGui.h"
#include "imgui.h"
#include "raylib.h"
#include <string>
#include <iostream>

class MyGUI
{
public:
    MyGUI(bool dark_theme);

    void Render();
    void Shutdown();
private:
    // private data ------------------------------------

    // plz no touch this one variable
    bool open_main_dockspace;
    ImGuiDockNodeFlags main_dockspace_flags;

public:
    // public data -------------------------------------
    std::string message = "";
    bool generate_message = false;
    int message_text_scale;
    int light_color_minimum;
    int dark_color_maximum;
    int noise_factor;

private:
    // private functions -------------------------------
    void HelpMarker(const char* desc);

    void Setup_Main_Docking_Window(bool* open);
    
    void Show_Main_Menu_Bar();
    void Show_Main_Menu_Bar_View();

    void Show_Message_Generator_Menu_Bar();
    void Show_Message_Generator();

    int max_message_size;
    int max_message_size_buffer;
    std::string message_buffer = "";
    float message_generator_font_scale;
};
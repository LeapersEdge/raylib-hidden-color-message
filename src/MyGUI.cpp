#include "MyGUI.h"

MyGUI::MyGUI(bool dark_theme)
    :
    open_main_dockspace(true),
    max_message_size(100),
    max_message_size_buffer(max_message_size),
    message_generator_font_scale(1.0f),
    message_text_scale(4)
{
    rlImGuiSetup(dark_theme);

    // enabling docking for dockerspaces
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    main_dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;
}

void MyGUI::Render()
{
    rlImGuiBegin();

    // render gui ----------------------
    
    // setting up main windoow (dockable and main menu bar)
    Setup_Main_Docking_Window(&open_main_dockspace);

    Show_Message_Generator();

    //ImGui::ShowDemoWindow();

    // ---------------------------------

    rlImGuiEnd();
}

void MyGUI::Shutdown()
{
    rlImGuiShutdown();
}

void MyGUI::HelpMarker(const char *desc)
{
    ImGui::TextDisabled("(?)");
    if (ImGui::BeginItemTooltip())
    {
        ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
        ImGui::TextUnformatted(desc);
        ImGui::PopTextWrapPos();
        ImGui::EndTooltip();
    }
}

void MyGUI::Show_Main_Menu_Bar()
{
    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("Settings"))
        {
            ImGui::MenuItem("Nothing for now", "", false, false);
            ImGui::EndMenu();
        }

        Show_Main_Menu_Bar_View();

        ImGui::EndMenuBar();
    }
}

void MyGUI::Setup_Main_Docking_Window(bool* open)
{
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking;
    const ImGuiViewport* viewport = ImGui::GetMainViewport();

    // setting up viewpoint
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);
    ImGui::SetNextWindowViewport(viewport->ID);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

    // setting up flags
    window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove;
    window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
    window_flags |= ImGuiWindowFlags_NoBackground;
    
    // removing padding just in case
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

    // creating dockspace
    ImGui::Begin("Dockspace", open, window_flags);

    ImGui::PopStyleVar();
    ImGui::PopStyleVar(2);
    
    // submit the dockspace
    ImGuiIO& io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), main_dockspace_flags);
    }
    else
    {
        std::cout << "ERROR: Docking is not enabled! See Demo > Configuration.\n";
        std::cout << "Set io.ConfigFlags |= ImGuiConfigFlags_DockingEnable in your code.\n";
    }

    //Show_Main_Menu_Bar();

    ImGui::End();
}

void MyGUI::Show_Main_Menu_Bar_View()
{
    if (ImGui::BeginMenu("View"))
    {
        if (ImGui::BeginMenu("Appearence"))
        {
            if (ImGui::BeginMenu("Themes"))
            {
                if (ImGui::MenuItem("Light"))   { ImGui::StyleColorsLight(); }
                if (ImGui::MenuItem("Dark"))    { ImGui::StyleColorsDark(); }
                if (ImGui::MenuItem("Classic")) { ImGui::StyleColorsClassic(); }
                ImGui::EndMenu();
            }
            ImGui::EndMenu();
        }
        
        ImGui::EndMenu();
    }
}

void MyGUI::Show_Message_Generator_Menu_Bar()
{
    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("Settings"))
        {
            if (ImGui::BeginMenu("Gui Font Sizes"))
            {
                ImGui::SetWindowFontScale(message_generator_font_scale);
                if (ImGui::MenuItem("Small"))       { message_generator_font_scale = 0.5f; }
                if (ImGui::MenuItem("Normal"))      { message_generator_font_scale = 1.0f; }
                if (ImGui::MenuItem("Large"))       { message_generator_font_scale = 2.0f; }
                if (ImGui::MenuItem("Hugeeeee"))    { message_generator_font_scale = 5.0f; }
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Message Font Sizes"))
            {
                ImGui::SetWindowFontScale(message_generator_font_scale);
                if (ImGui::MenuItem("Normal"))      { message_text_scale = 1; }
                if (ImGui::MenuItem("Big"))         { message_text_scale = 2; }
                if (ImGui::MenuItem("Bigger"))      { message_text_scale = 3; }
                if (ImGui::MenuItem("Biggerer"))    { message_text_scale = 4; }
                if (ImGui::MenuItem("Biggest"))     { message_text_scale = 6; }
                if (ImGui::MenuItem("Biggester"))   { message_text_scale = 10; }
                if (ImGui::MenuItem("Bruh"))        { message_text_scale = 15; }
                ImGui::EndMenu();
            }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("View"))
        {
            if (ImGui::BeginMenu("Appearence"))
            {
                if (ImGui::BeginMenu("Themes"))
                {
                    if (ImGui::MenuItem("Light"))   { ImGui::StyleColorsLight(); }
                    if (ImGui::MenuItem("Dark"))    { ImGui::StyleColorsDark(); }
                    if (ImGui::MenuItem("Classic")) { ImGui::StyleColorsClassic(); }
                    ImGui::EndMenu();
                }
                ImGui::EndMenu();
            }
        
            ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
    }
}

void MyGUI::Show_Message_Generator()
{
    // message generator window
    ImGui::SetNextWindowSize(ImVec2(485,217), ImGuiCond_FirstUseEver);
    ImGui::Begin("Message generator", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_AlwaysAutoResize);
    ImGui::SetWindowFontScale(message_generator_font_scale);

    // mmax message size line setup
    ImGui::Text("Current max message size: %d", max_message_size);
    ImGui::SameLine();
    ImGui::SetNextItemWidth(100 * message_generator_font_scale);
    ImGui::InputInt("##max_message_size", &max_message_size_buffer);
    ImGui::SameLine();
    if (ImGui::Button("Confirm"))   max_message_size = max_message_size_buffer;
    ImGui::SameLine();
    if (ImGui::Button("Reset"))     max_message_size_buffer = max_message_size;
    ImGui::SameLine();
    HelpMarker("This is setup as is due to tehnical limitations i didn't want to get around in this morning/afternoon coding session.\n\nJust increase it to whatever value you want, it will be fine.\n\nLike, make it over 9000 if you want!");

    // secret message input field setup
    ImGui::Text("Secret message ");
    ImGui::SameLine();
    
    char* message_cstr = new char[max_message_size + 1];
    strcpy(message_cstr, message_buffer.c_str());
    ImGui::SetNextItemWidth( 325 * message_generator_font_scale);
    ImGui::InputTextMultiline("##message", message_cstr, max_message_size + 1);
    message_buffer = message_cstr;
    delete[] message_cstr;

    if (ImGui::Button("Generate"))
    {
        message = message_buffer;
        generate_message = true;
    }
    
    Show_Message_Generator_Menu_Bar();

    ImGui::End();
}

#include "include/common/ui.h"

// Default Backgroung color
ImVec4 bg_color = ImVec4(0.0f, 0.0f, 0.0f, 1.00f);

ui::UI::UI()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGLUT_Init();
    ImGui_ImplGLUT_InstallFuncs();
    ImGui_ImplOpenGL3_Init();
}

ui::UI::~UI()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGLUT_Shutdown();
    ImGui::DestroyContext();
}

void ui::UI::newFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGLUT_NewFrame();
}

void ui::UI::render()
{
    ImGui::Render();
    glClearColor(bg_color.x * bg_color.w, bg_color.y * bg_color.w, bg_color.z * bg_color.w, bg_color.w);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ui::UI::widget()
{
    ImGui::Begin("E0 271 - GAV");

    // // Text input for file location
    // static char file_location[128] = "";
    // ImGui::InputText("File Location", file_location, IM_ARRAYSIZE(file_location));

    // input text
    static char input_text[128] = "";
    ImGui::InputText("Iso Value", input_text, IM_ARRAYSIZE(input_text));

    static float slider_value = volumeRender->getIsoValue();

    // button
    if (ImGui::Button("Button"))
    {
        slider_value = atof(input_text);
    }

    // slider
    ImGui::SliderFloat("Slider", &slider_value, volumeRender->getMinVal(), volumeRender->getMaxVal());

    // change in slider
    if (slider_value != volumeRender->getIsoValue())
    {
        volumeRender->setIsoValue(slider_value);
        if (volumeRender->getAlgo() != 2)
            volumeRender->updateVBO();
    }
    
    // drop down menu
    static int selected_item = 0;
    static const char *items[] = {"Naive technique", "Domain search technique", "GPU - Ray marching"};
    ImGui::Combo("Algorithm", &selected_item, items, IM_ARRAYSIZE(items));

    if (selected_item == 0)
    {
        volumeRender->setAlgo(0);
    }
    else if (selected_item == 1)
    {
        volumeRender->setAlgo(1);
    }
    else if (selected_item == 2)
    {
        volumeRender->setAlgo(2);
    }

    //Background Color Editor
    ImGui::ColorEdit3("Background Color", (float*)&bg_color); 


    ImGui::End();
}

void ui::UI::setVolumeRender(VolumeRender *volumeRender)
{
    this->volumeRender = volumeRender;
}

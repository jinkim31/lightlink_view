#include <immapp/immapp.h>
#include <implot/implot.h>
#include <immvision/immvision.h>
#include <opencv2/opencv.hpp>
#include <imgui_tex_inspect/imgui_tex_inspect.h>
#include <windows.h>
#include "custom_widgets.h"

class EntryPoint
{

public:
    void Gui()
    {
        Widget::setStyle();
        ImGui::ShowDemoWindow();
    }

    EntryPoint()
    {
        HelloImGui::RunnerParams runnerParams;
        //runnerParams.callbacks.SetupImGuiStyle = Widget::setStyle;
        runnerParams.callbacks.ShowGui = [&]{Gui();};
        runnerParams.imGuiWindowParams.defaultImGuiWindowType = HelloImGui::DefaultImGuiWindowType::ProvideFullScreenDockSpace;
        runnerParams.imGuiWindowParams.enableViewports = true;
        runnerParams.fpsIdling.enableIdling = false;
        ImmApp::AddOnsParams addOnsParams;
        addOnsParams.withMarkdown = true;
        addOnsParams.withImplot = true;
        addOnsParams.withTexInspect = true;
        ImmApp::Run(runnerParams, addOnsParams);
    }
};

int main(int , char *[])
{
    EntryPoint e;
    return 0;
}

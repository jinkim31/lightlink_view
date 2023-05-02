#include <immapp/immapp.h>
#include <implot/implot.h>
#include <imgui_tex_inspect/imgui_tex_inspect.h>
#include "widget/widget.h"

class EntryPoint
{

public:
    void Gui()
    {
        static bool style=false;
        if(!style)
        {
            widget::setStyle();
            style = true;
        }
        ImGui::ShowDemoWindow();
        ImGui::Begin("Master");
        ImGui::Text("Master test:");
        widget::Master("test master");
        ImGui::End();
    }

    EntryPoint()
    {
        HelloImGui::RunnerParams runnerParams;
        //runnerParams.callbacks.SetupImGuiStyle = Widget::setStyle;
        runnerParams.appWindowParams.windowTitle = "LightView";
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

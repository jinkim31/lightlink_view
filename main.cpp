#include <immapp/immapp.h>
#include <implot/implot.h>
#include "widget.h"
#include "model.h"
#include <eventThread.h>

Model model;

class EntryPoint
{
private:
    ethr::EThread mainThread;
    std::string selectedPortName;
    int selectedBaudRate, selectedID;
    bool isSelected = false;
public:
    EntryPoint()
    {
        HelloImGui::RunnerParams runnerParams;
        //runnerParams.callbacks.SetupImGuiStyle = Widget::setStyle;
        runnerParams.appWindowParams.windowTitle = "LightView";
        runnerParams.callbacks.ShowGui = [&]{Gui();};
        runnerParams.callbacks.SetupImGuiConfig = []{
            widget::loadIconFont();
        };
        runnerParams.imGuiWindowParams.defaultImGuiWindowType = HelloImGui::DefaultImGuiWindowType::ProvideFullScreenDockSpace;
        runnerParams.imGuiWindowParams.enableViewports = true;
        runnerParams.fpsIdling.enableIdling = false;
        ImmApp::AddOnsParams addOnsParams;
        addOnsParams.withMarkdown = true;
        addOnsParams.withImplot = true;
        addOnsParams.withTexInspect = true;
        ImmApp::Run(runnerParams, addOnsParams);
    }

    void Gui()
    {
        mainThread.handleQueuedEvents();
        static bool style=false;
        if(!style)
        {
            widget::setStyle();
            style = true;
        }
        ImGui::ShowDemoWindow();

        bool t = true;
        ImGui::Begin("Devices", &t, ImGuiWindowFlags_MenuBar);
        {
            bool openModal=false;
            if (ImGui::BeginMenuBar())
            {
                openModal = ImGui::MenuItem(ICON_FA_PLUS " Add port");
                ImGui::EndMenuBar();

            }


            /*
            if(ImGui::Button("Add port", {ImGui::GetContentRegionAvail().x ,30}))
                openModal = true;
            */

            if(openModal)
                ImGui::OpenPopup("Delete?");

            // Always center this window when appearing
            ImVec2 center = ImGui::GetMainViewport()->GetCenter();
            ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

            if (ImGui::BeginPopupModal("Delete?", NULL, ImGuiWindowFlags_AlwaysAutoResize))
            {
                widget::PortModal(model);
                ImGui::EndPopup();
            }

            for(const auto& [portName, master] : model.getMasters())
            {
                widget::Master(*master);

                ImGui::Indent();
                for(const auto& [baudRate, slaves] : master->getSlaves())
                {
                    for(const auto& [id, slave] : slaves)
                    {
                        if(widget::Slave(*slave))
                        {
                            selectedPortName = portName;
                            selectedBaudRate = baudRate;
                            selectedID = id;
                            isSelected = true;
                        }
                    }
                }
                ImGui::Unindent();
            }
        }ImGui::End();

        ImGui::Begin("Device Object Table", &t, ImGuiWindowFlags_MenuBar);
        {
            ImGuiTableFlags flags = ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg;
            if(isSelected && ImGui::BeginTable("Object Table", 6, flags))
            {
                ImGui::TableSetupColumn("type index");
                ImGui::TableSetupColumn("object index");
                ImGui::TableSetupColumn("name");
                ImGui::TableSetupColumn("type name");
                ImGui::TableSetupColumn("type size");
                ImGui::TableSetupColumn("access");
                ImGui::TableHeadersRow();

                LLINK_Master_Summary* summary = &model.getMasters()[selectedPortName]->getSlaves()[selectedBaudRate][selectedID]->mSummary;

                const char LLINK_ACCESS_STRING[4][13] = {"inaccessible", "read", "write", "readwrite"};

                for(int typeIndex = 0; typeIndex < summary->nObjectTypes; typeIndex++)
                {
                    LLINK_Master_TypedObjectList* typedList = summary->objectLists + typeIndex;
                    for(int objectIndex = 0; objectIndex < typedList->nObjects; objectIndex++)
                    {
                        ImGui::TableNextRow();

                        LLINK_Master_Object* object = typedList->objects+objectIndex;
                        ImGui::TableSetColumnIndex(0);
                        ImGui::Text("%d", typeIndex);
                        ImGui::TableSetColumnIndex(1);
                        ImGui::Text("%d", objectIndex);
                        ImGui::TableSetColumnIndex(2);
                        ImGui::Text("%s", object->name);
                        ImGui::TableSetColumnIndex(3);
                        ImGui::Text("%s", typedList->typeName);
                        ImGui::TableSetColumnIndex(4);
                        ImGui::Text("%d", typedList->typeSize);
                        ImGui::TableSetColumnIndex(5);
                        ImGui::Text("%s", LLINK_ACCESS_STRING[object->access]);
                    }
                }

                /*

                for (int row = 0; row < 5; row++)
                {
                    ImGui::TableNextRow();
                    for (int column = 0; column < 3; column++)
                    {
                        ImGui::TableSetColumnIndex(column);
                        char buf[32];
                        sprintf(buf, "Hello %d,%d", column, row);
                        //if (contents_type == CT_Text)
                            ImGui::TextUnformatted(buf);
                        //else if (contents_type == CT_FillButton)
                        //    ImGui::Button(buf, ImVec2(-FLT_MIN, 0.0f));
                    }
                }
                 */
                ImGui::EndTable();
            }
        }ImGui::End();

    }
};

int main(int , char *[])
{
    EntryPoint e;
    return 0;
}

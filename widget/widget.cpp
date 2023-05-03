#include "widget.h"
#include "imgui_internal.h"
#include <stack>
#include <iostream>

using namespace ImGui;

widget::ColorPalette colorPalette;
std::stack<ImVec2> layerMinStack;
std::stack<ImVec2> layerMaxStack;
std::stack<ImVec2> layerSizeStack;

void widget::LED(widget::LedState state, const std::string &text = "")
{
    ImDrawList* draw_list = ImGui::GetWindowDrawList();
    const ImVec2 p = ImGui::GetCursorScreenPos();
    static float sz = 10.0f;
    const int circle_segments = 12;
    draw_list->AddCircleFilled(ImVec2(p.x + sz*0.5f, p.y + sz*0.5f), sz*0.5f, ImColor(widget::color(0, 255, 120)), circle_segments);
    draw_list->AddCircle(ImVec2(p.x + sz*0.5f, p.y + sz*0.5f), sz*0.5f, ImColor(widget::colorPalette.borderColor), circle_segments);
    ImGuiStyle style = ImGui::GetStyle();
    ImGui::Dummy({sz, 0});
}

ImVec4 widget::color(ImU8 r, ImU8 g, ImU8 b, ImU8 a)
{
    return ImVec4{(float)r / 255.0f, (float)g / 255.0f, (float)b / 255.0f, (float)a / 255.0f};
}

void widget::setStyle()
{
    widget::colorPalette.bgColor            = color(255, 255, 255);
    widget::colorPalette.panelColor         = color(242, 242, 242);
    widget::colorPalette.borderColor        = color(209, 209, 209);
    widget::colorPalette.hoverColor         = color(213, 213, 213);
    widget::colorPalette.activeColor        = color(81, 129, 195);
    widget::colorPalette.activeLightColor   = color(169, 176, 190);
    widget::colorPalette.textColor          = color(0,0,0);
    widget::colorPalette.textDisabledColor  = color(100, 100, 100);
    widget::colorPalette.objectColor        = color(167, 167, 167);

    auto& style = ImGui::GetStyle();
    ImVec4* colors = style.Colors;

    colors[ImGuiCol_Text]                 = widget::colorPalette.textColor;
    colors[ImGuiCol_TextDisabled]         = widget::colorPalette.textDisabledColor;
    colors[ImGuiCol_TextSelectedBg]       = widget::colorPalette.activeColor;
    colors[ImGuiCol_WindowBg]             = widget::colorPalette.bgColor;
    colors[ImGuiCol_ChildBg]              = widget::colorPalette.panelColor;
    colors[ImGuiCol_PopupBg]              = widget::colorPalette.bgColor;
    colors[ImGuiCol_Border]               = widget::colorPalette.borderColor;
    colors[ImGuiCol_BorderShadow]         = widget::colorPalette.borderColor;
    colors[ImGuiCol_FrameBg]              = widget::colorPalette.panelColor;
    colors[ImGuiCol_FrameBgHovered]       = widget::colorPalette.hoverColor;
    colors[ImGuiCol_FrameBgActive]        = widget::colorPalette.activeColor;
    colors[ImGuiCol_TitleBg]              = widget::colorPalette.panelColor;
    colors[ImGuiCol_TitleBgActive]        = widget::colorPalette.panelColor;
    colors[ImGuiCol_TitleBgCollapsed]     = widget::colorPalette.panelColor;
    colors[ImGuiCol_MenuBarBg]            = widget::colorPalette.panelColor;
    colors[ImGuiCol_ScrollbarBg]          = widget::colorPalette.panelColor;
    colors[ImGuiCol_ScrollbarGrab]        = widget::colorPalette.objectColor;
    colors[ImGuiCol_ScrollbarGrabHovered] = widget::colorPalette.objectColor;
    colors[ImGuiCol_ScrollbarGrabActive]  = widget::colorPalette.objectColor;
    colors[ImGuiCol_CheckMark]            = widget::colorPalette.activeColor;
    colors[ImGuiCol_SliderGrab]           = widget::colorPalette.hoverColor;
    colors[ImGuiCol_SliderGrabActive]     = widget::colorPalette.activeColor;
    colors[ImGuiCol_Button]               = widget::colorPalette.panelColor;
    colors[ImGuiCol_ButtonHovered]        = widget::colorPalette.hoverColor;
    colors[ImGuiCol_ButtonActive]         = widget::colorPalette.activeLightColor;
    colors[ImGuiCol_Header]               = widget::colorPalette.panelColor;
    colors[ImGuiCol_HeaderHovered]        = widget::colorPalette.hoverColor;
    colors[ImGuiCol_HeaderActive]         = widget::colorPalette.activeColor;
    colors[ImGuiCol_Separator]            = widget::colorPalette.borderColor;
    colors[ImGuiCol_SeparatorHovered]     = widget::colorPalette.borderColor;
    colors[ImGuiCol_SeparatorActive]      = widget::colorPalette.borderColor;
    colors[ImGuiCol_ResizeGrip]           = widget::colorPalette.bgColor;
    colors[ImGuiCol_ResizeGripHovered]    = widget::colorPalette.panelColor;
    colors[ImGuiCol_ResizeGripActive]     = widget::colorPalette.panelColor;
    colors[ImGuiCol_PlotLines]            = widget::colorPalette.activeColor;
    colors[ImGuiCol_PlotLinesHovered]     = widget::colorPalette.hoverColor;
    colors[ImGuiCol_PlotHistogram]        = widget::colorPalette.activeColor;
    colors[ImGuiCol_PlotHistogramHovered] = widget::colorPalette.hoverColor;
    //colors[ImGuiCol_ModalWindowDarkening] = widget::colorPalette.bgColor;
    colors[ImGuiCol_DragDropTarget]       = widget::colorPalette.bgColor;
    colors[ImGuiCol_NavHighlight]         = widget::colorPalette.bgColor;
    colors[ImGuiCol_DockingPreview]       = widget::colorPalette.activeColor;
    colors[ImGuiCol_Tab]                  = widget::colorPalette.panelColor;
    colors[ImGuiCol_TabActive]            = widget::colorPalette.activeLightColor;
    colors[ImGuiCol_TabUnfocused]         = widget::colorPalette.panelColor;
    colors[ImGuiCol_TabUnfocusedActive]   = widget::colorPalette.borderColor;
    colors[ImGuiCol_TabHovered]           = widget::colorPalette.activeLightColor;

    style.WindowRounding    = 0.0f;
    style.ChildRounding     = 0.0f;
    style.FrameRounding     = 0.0f;
    style.GrabRounding      = 0.0f;
    style.PopupRounding     = 0.0f;
    style.ScrollbarRounding = 0.0f;
    style.TabRounding       = 0.0f;

    style.WindowPadding = {8, 8};
    style.FramePadding = {8, 5};
    style.ItemSpacing = {8, 8};
    style.ScrollbarRounding = 14;
    style.ScrollbarSize = 14;
    style.WindowMenuButtonPosition = ImGuiDir_None;
    style.ChildBorderSize = 0;

}


ImRect BeginLayer(ImVec2 size)
{
    ImDrawList* drawList = ImGui::GetWindowDrawList();
    ImVec2 layerMin = ImGui::GetCursorScreenPos();
    ImVec2 layerMax;

    if(size.x < 0 && size.y < 0)
        layerMax = {layerMin.x + ImGui::GetContentRegionAvail().x, layerMin.y + ImGui::GetContentRegionAvail().y};
    else if(size.x < 0 && size.y > 0)
        layerMax = {layerMin.x + ImGui::GetContentRegionAvail().x, layerMin.y + size.y};
    else if(size.x > 0 && size.y < 0)
        layerMax ={layerMin.x + size.x, layerMin.y + ImGui::GetContentRegionAvail().y};
    else
        layerMax ={layerMin.x + size.x, layerMin.y + size.y};

    if(!layerMaxStack.empty())
        layerMax = ImMin(layerMax, {layerMaxStack.top().x-ImGui::GetStyle().ItemSpacing.x, layerMaxStack.top().y-ImGui::GetStyle().ItemSpacing.x});

    drawList->AddRectFilled(layerMin, layerMax, ImColor(ImGui::GetStyleColorVec4(ImGuiCol_ChildBg)));
    //drawList->AddRect(layerMin, layerMax, ImColor(widget::color(255,0,0)));
    Dummy({0, 0});// dummy for upper spacing
    layerMinStack.push(layerMin);
    layerMaxStack.push(layerMax);
    layerSizeStack.emplace(layerMax.x - layerMin.x, layerMax.y - layerMin.y);

    BeginGroup();
    Indent(GetStyle().FramePadding.x);

    ImRect bb;
    bb.Min = layerMin;
    bb.Max = layerMax;
    return bb;
}

void EndLayer()
{
    ImVec2 childEnd = ImGui::GetCursorScreenPos();
    ImVec2 dummySize = {layerMaxStack.top().x - childEnd.x, layerMaxStack.top().y - childEnd.y};
    ImGui::Dummy(dummySize);
    Unindent(GetStyle().FramePadding.x);
    EndGroup();

    layerMinStack.pop();
    layerMaxStack.pop();
    layerSizeStack.pop();
}

ImVec2 LayerGetContentRegionAvail()
{
    return layerSizeStack.top();
}

bool TriangleToggle()
{
    ImVec2 origin = ImGui::GetCursorScreenPos();

    SetNextItemWidth(30);
    Button(" ##triangle");

    origin = {origin.x+10, origin.y + 7};
    ImDrawList* drawList = ImGui::GetWindowDrawList();
    drawList->AddTriangleFilled(
            {origin.x, origin.y},
            {origin.x+7, origin.y+7},
            {origin.x, origin.y+14},
            ImColor{ImGui::GetStyleColorVec4(ImGuiCol_Text)});

    return true;
}

void HLine()
{
    ImVec2 start = ImGui::GetCursorScreenPos();
    ImVec2 end = {start.x + LayerGetContentRegionAvail().x, start.y};
    ImDrawList* drawList = ImGui::GetWindowDrawList();
    drawList->AddLine(start, end, ImColor(255, 0, 0));
    Dummy({0,0});
}
bool widget::Master(const char *label, ImGuiTreeNodeFlags flags)
{
    BeginLayer({-1, 40});
    {
        ImGui::AlignTextToFramePadding();
        ArrowButton("arrow", ImGuiDir_Down);
        SameLine();
        Dummy({10, 0});
        SameLine();
        LED(LedState::GREEN);
        SameLine();
        Text("Master 0");
        SameLine(LayerGetContentRegionAvail().x-90);
        SetNextItemWidth(30);
        Button("S##Master 0");
        SameLine(LayerGetContentRegionAvail().x-60);
        SetNextItemWidth(30);
        Button("A##Master 0");
        SameLine(LayerGetContentRegionAvail().x-30);
        SetNextItemWidth(30);
        Button("D##Master 0");
    }EndLayer();

    return true;
}

bool widget::Collapsable(const char *label)
{

    return false;
}

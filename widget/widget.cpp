#include "widget.h"
#include "imgui_internal.h"

using namespace ImGui;

widget::ColorPalette colorPalette;
ImVec2 layerStart;
ImVec2 layerSize;

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
    colors[ImGuiCol_ButtonActive]         = widget::colorPalette.hoverColor;
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


void BeginLayer(ImVec2 size)
{
    ImDrawList* drawList = ImGui::GetWindowDrawList();
    layerSize = size;
    layerStart = ImGui::GetCursorScreenPos();

    BeginGroup();
    Indent(10);
    if(size.x < 0 && size.y < 0)
        drawList->AddRectFilled(layerStart, {layerStart.x + ImGui::GetContentRegionAvail().x, layerStart.y + ImGui::GetContentRegionAvail().y}, ImColor(ImGui::GetStyleColorVec4(ImGuiCol_ChildBg)));
    else if(size.x < 0 && size.y > 0)
        drawList->AddRectFilled(layerStart, {layerStart.x + ImGui::GetContentRegionAvail().x, layerStart.y + size.y}, ImColor(ImGui::GetStyleColorVec4(ImGuiCol_ChildBg)));
    else if(size.x > 0 && size.y < 0)
        drawList->AddRectFilled(layerStart, {layerStart.x + size.x, layerStart.y + ImGui::GetContentRegionAvail().y}, ImColor(ImGui::GetStyleColorVec4(ImGuiCol_ChildBg)));
    else
        drawList->AddRectFilled(layerStart, {layerStart.x + size.x, layerStart.y + size.y}, ImColor(ImGui::GetStyleColorVec4(ImGuiCol_ChildBg)));

    Dummy({0, 0});
}

void EndLayer()
{
    ImVec2 layerEnd = ImGui::GetCursorScreenPos();
    ImVec2 dummySize = {layerSize.x - (layerEnd.x - layerStart.x), layerSize.y - (layerEnd.y - layerStart.y)};
    ImGui::Dummy(dummySize);
    Unindent(10);
    EndGroup();

    ImDrawList* drawList = ImGui::GetWindowDrawList();
    drawList->AddRectFilled(layerEnd, {layerEnd.x + dummySize.x, layerEnd.y + dummySize.y}, ImColor(widget::color(255,0,0)));

}

bool widget::Master(const char *label, ImGuiTreeNodeFlags flags)
{
    BeginLayer({-1, 200});
    ImGui::Text("asdf1");
    ImGui::Text("asdf2");
    ImGui::Text("asdf3");
    EndLayer();

    BeginLayer({-1, 200});
    ImGui::Text("asdf1");
    ImGui::Text("asdf2");
    ImGui::Text("asdf3");
    EndLayer();

    ImGui::Text("asdf1");
    ImGui::Text("asdf2");
    ImGui::Text("asdf3");
    return true;
}

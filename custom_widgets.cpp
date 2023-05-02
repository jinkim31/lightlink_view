#include "custom_widgets.h"
#include <immvision/immvision.h>

void Widget::setStyle()
{
    constexpr auto ColorFromBytes = [](ImU8 r, ImU8 g, ImU8 b)
    {
        return ImVec4((float)r / 255.0f, (float)g / 255.0f, (float)b / 255.0f, 1.0f);
    };

    auto& style = ImGui::GetStyle();
    ImVec4* colors = style.Colors;

    const ImVec4 bgColor           = ColorFromBytes(255, 255, 255);
    const ImVec4 panelColor        = ColorFromBytes(242, 242, 242);
    const ImVec4 borderColor       = ColorFromBytes(209, 209, 209);
    const ImVec4 hoverColor   = ColorFromBytes(213, 213, 213);
    const ImVec4 activeColor  = ColorFromBytes(81, 129, 195);
    const ImVec4 activeLightColor  = ColorFromBytes(169, 176, 190);
    const ImVec4 textColor         = ColorFromBytes(0,0,0);
    const ImVec4 textDisabledColor = ColorFromBytes(100, 100, 100);
    const ImVec4 objectColor = ColorFromBytes(167, 167, 167);

    colors[ImGuiCol_Text]                 = textColor;
    colors[ImGuiCol_TextDisabled]         = textDisabledColor;
    colors[ImGuiCol_TextSelectedBg]       = activeColor;
    colors[ImGuiCol_WindowBg]             = bgColor;
    colors[ImGuiCol_ChildBg]              = bgColor;
    colors[ImGuiCol_PopupBg]              = bgColor;
    colors[ImGuiCol_Border]               = borderColor;
    colors[ImGuiCol_BorderShadow]         = borderColor;
    colors[ImGuiCol_FrameBg]              = panelColor;
    colors[ImGuiCol_FrameBgHovered]       = hoverColor;
    colors[ImGuiCol_FrameBgActive]        = activeColor;
    colors[ImGuiCol_TitleBg]              = panelColor;
    colors[ImGuiCol_TitleBgActive]        = panelColor;
    colors[ImGuiCol_TitleBgCollapsed]     = panelColor;
    colors[ImGuiCol_MenuBarBg]            = panelColor;
    colors[ImGuiCol_ScrollbarBg]          = panelColor;
    colors[ImGuiCol_ScrollbarGrab]        = objectColor;
    colors[ImGuiCol_ScrollbarGrabHovered] = objectColor;
    colors[ImGuiCol_ScrollbarGrabActive]  = objectColor;
    colors[ImGuiCol_CheckMark]            = activeColor;
    colors[ImGuiCol_SliderGrab]           = hoverColor;
    colors[ImGuiCol_SliderGrabActive]     = activeColor;
    colors[ImGuiCol_Button]               = panelColor;
    colors[ImGuiCol_ButtonHovered]        = hoverColor;
    colors[ImGuiCol_ButtonActive]         = hoverColor;
    colors[ImGuiCol_Header]               = panelColor;
    colors[ImGuiCol_HeaderHovered]        = hoverColor;
    colors[ImGuiCol_HeaderActive]         = activeColor;
    colors[ImGuiCol_Separator]            = borderColor;
    colors[ImGuiCol_SeparatorHovered]     = borderColor;
    colors[ImGuiCol_SeparatorActive]      = borderColor;
    colors[ImGuiCol_ResizeGrip]           = bgColor;
    colors[ImGuiCol_ResizeGripHovered]    = panelColor;
    colors[ImGuiCol_ResizeGripActive]     = panelColor;
    colors[ImGuiCol_PlotLines]            = activeColor;
    colors[ImGuiCol_PlotLinesHovered]     = hoverColor;
    colors[ImGuiCol_PlotHistogram]        = activeColor;
    colors[ImGuiCol_PlotHistogramHovered] = hoverColor;
    //colors[ImGuiCol_ModalWindowDarkening] = bgColor;
    colors[ImGuiCol_DragDropTarget]       = bgColor;
    colors[ImGuiCol_NavHighlight]         = bgColor;
    colors[ImGuiCol_DockingPreview]       = activeColor;
    colors[ImGuiCol_Tab]                  = panelColor;
    colors[ImGuiCol_TabActive]            = activeLightColor;
    colors[ImGuiCol_TabUnfocused]         = panelColor;
    colors[ImGuiCol_TabUnfocusedActive]   = borderColor;
    colors[ImGuiCol_TabHovered]           = activeLightColor;

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
    style.ScrollbarRounding = 12;
    style.WindowMenuButtonPosition = ImGuiDir_None;
}

void Widget::ImageView(const std::string label, cv::Mat image)
{
    ImGui::Begin(label.c_str());
    {
        static ImmVision::ImageParams p;
        p.RefreshImage = true;
        p.ImageDisplaySize = {(int) ImGui::GetContentRegionAvail().x,
                              std::max(0, (int) ImGui::GetContentRegionAvail().y - 50)};
        p.ShowSchoolPaperBackground = false;
        p.ShowOptionsInTooltip = true;
        p.ShowOptionsButton = false;
        p.ShowImageInfo = false;
        p.ShowPixelInfo = false;
        p.ShowGrid = false;
        p.ShowPixelInfo = false;
        p.ShowAlphaChannelCheckerboard = true;
        ImmVision::Image("", image, &p);
    }
    ImGui::End();
}
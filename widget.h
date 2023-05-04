#ifndef WIDGET_H
#define WIDGET_H

#include "imgui.h"
#include "implot/implot.h"
#include "model.h"

namespace widget
{

struct ColorPalette
{
     ImVec4 bgColor;
     ImVec4 panelColor;
     ImVec4 borderColor;
     ImVec4 hoverColor;
     ImVec4 activeColor;
     ImVec4 activeLightColor;
     ImVec4 textColor;
     ImVec4 textDisabledColor;
     ImVec4 objectColor;
};

ImVec4 color(ImU8 r, ImU8 g, ImU8 b, ImU8 a=255);
void setStyle();
enum class LedState
{
    RED,
    GREEN,
    YELLOW,
    OFF,
};
void LED(widget::LedState state, const std::string &text);
bool Collapsable(const char* label);
bool Master(Model::MasterModel &masterModel);
bool Slave(Model::SlaveModel& slaveModel);
void loadIconFont();
void BeginLayer(ImVec2 size);
void EndLayer();
bool TriangleToggle();
void HLine();
void PortModal(Model &model);
bool widget::Master(Model::MasterModel &masterModel);
// global variables
static ColorPalette colorPalette;
}

#endif
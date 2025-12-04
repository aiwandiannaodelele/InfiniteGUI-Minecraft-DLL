#pragma once

#include "imgui\imgui.h"
#include "ImGuiStd.h"
#include <nlohmann/json.hpp>
struct ItemStyle {
    float windowRounding;
    float fontSize;
    ImVec4 fontColor;
    ImVec4 bgColor;
    ImVec4 borderColor;
    bool rainbowFont;
};

class WindowStyleModule {
public:
    WindowStyleModule()
    {
        InitStyle();
    }
    void DrawStyleSettings()
    {
        ImGui::SliderFloat(u8"窗口圆角", &itemStyle.windowRounding, 0.0f, 10.0f, "%.1f");
        //字体大小设置
        ImGui::InputFloat(u8"字体大小", &itemStyle.fontSize, 1.0f, 1.0f, "%.1f");
        //颜色设置
        ImVec4* colors = ImGui::GetStyle().Colors;
        ImGuiStd::EditColor(u8"字体颜色", itemStyle.fontColor, colors[ImGuiCol_Text]);
        ImGui::SameLine();
        ImGui::Checkbox(u8"彩虹", &itemStyle.rainbowFont);
        ImGuiStd::EditColor(u8"背景颜色", itemStyle.bgColor, colors[ImGuiCol_WindowBg]);
        ImGuiStd::EditColor(u8"边框颜色", itemStyle.borderColor, colors[ImGuiCol_Border]);
    }

protected:
    void LoadStyle(const nlohmann::json& j)
    {
        if (j.contains("windowRounding")) itemStyle.windowRounding = j["windowRounding"];
        if (j.contains("fontSize")) itemStyle.fontSize = j["fontSize"];
        if (j.contains("rainbowFont")) itemStyle.rainbowFont = j["rainbowFont"];
        ImGuiStd::LoadImVec4(j, "fontColor", itemStyle.fontColor);
        ImGuiStd::LoadImVec4(j, "bgColor", itemStyle.bgColor);
        ImGuiStd::LoadImVec4(j, "borderColor", itemStyle.borderColor);

    }

    void SaveStyle(nlohmann::json& j) const
    {
        j["windowRounding"] = itemStyle.windowRounding;
        j["fontSize"] = itemStyle.fontSize;
        j["rainbowFont"] = itemStyle.rainbowFont;
        ImGuiStd::SaveImVec4(j, "fontColor", itemStyle.fontColor);
        ImGuiStd::SaveImVec4(j, "bgColor", itemStyle.bgColor);
        ImGuiStd::SaveImVec4(j, "borderColor", itemStyle.borderColor);
    }
    void InitStyle()
    {
        //初始化默认样式
        ImGuiStyle& defaultStyle = ImGui::GetStyle();
        itemStyle.windowRounding = defaultStyle.WindowRounding;
        itemStyle.fontSize = defaultStyle.FontSizeBase;
        itemStyle.fontColor = defaultStyle.Colors[ImGuiCol_Text];
        itemStyle.bgColor = defaultStyle.Colors[ImGuiCol_WindowBg];
        itemStyle.borderColor = defaultStyle.Colors[ImGuiCol_Border];
    }
    void processRainbowFont()
    {
        ImVec4 col = ImColor::HSV((float)fmod(ImGui::GetTime() * 0.2f, 1.0f), 1, 1);
        ImGui::PushStyleColor(ImGuiCol_Text, col);
    }
    ItemStyle itemStyle;
    //ImVec4 rainbowFontColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
};


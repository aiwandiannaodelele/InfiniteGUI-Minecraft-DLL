#pragma once

#include "imgui\imgui.h"

void SetStyleGray(float roundCornerRadius)
{
    //https://github.com/ocornut/imgui/issues/707#issuecomment-2393152123
    // Setup style
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4* colors = style.Colors;
    //添加边框
    style.FrameBorderSize = 1.0f;
    style.WindowBorderSize = 1.0f;
    style.PopupBorderSize = 1.0f;
    style.ChildBorderSize = 1.0f;
    style.TabBorderSize = 1.0f;
    colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
    colors[ImGuiCol_TextDisabled] = ImVec4(0.48f, 0.48f, 0.48f, 1.00f);
    colors[ImGuiCol_WindowBg] = ImVec4(0.14f, 0.14f, 0.14f, 0.80f);
    colors[ImGuiCol_ChildBg] = ImVec4(0.14f, 0.14f, 0.14f, 0.50f);
    colors[ImGuiCol_PopupBg] = ImVec4(0.14f, 0.14f, 0.14f, 0.80f);
    colors[ImGuiCol_Border] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
    colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
    colors[ImGuiCol_FrameBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.24f, 0.24f, 1.00f);
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.30f, 0.30f, 0.30f, 1.00f);
    colors[ImGuiCol_TitleBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    colors[ImGuiCol_MenuBarBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.24f, 0.24f, 0.24f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.24f, 0.24f, 0.24f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.24f, 0.24f, 0.24f, 1.00f);
    colors[ImGuiCol_CheckMark] = ImVec4(0.86f, 0.93f, 0.89f, 1.00f);
    //colors[ImGuiCol_SliderGrab] = ImVec4(0.24f, 0.24f, 0.24f, 1.00f);
    //colors[ImGuiCol_SliderGrabActive] = ImVec4(0.24f, 0.24f, 0.24f, 1.00f);
    colors[ImGuiCol_SliderGrab] = ImVec4(0.35f, 0.35f, 0.35f, 1.00f);
    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
    colors[ImGuiCol_Button] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.24f, 0.24f, 1.00f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.30f, 0.30f, 0.30f, 1.00f);
    colors[ImGuiCol_Header] = ImVec4(0.24f, 0.24f, 0.24f, 0.00f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.24f, 0.24f, 0.24f, 1.00f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.30f, 0.30f, 0.30f, 1.00f);
    colors[ImGuiCol_Separator] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
    colors[ImGuiCol_SeparatorHovered] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
    colors[ImGuiCol_SeparatorActive] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
    colors[ImGuiCol_ResizeGrip] = ImVec4(0.24f, 0.24f, 0.24f, 1.00f);
    colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.24f, 0.24f, 0.24f, 1.00f);
    colors[ImGuiCol_ResizeGripActive] = ImVec4(0.24f, 0.24f, 0.24f, 1.00f);
    colors[ImGuiCol_Tab] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    colors[ImGuiCol_TabHovered] = ImVec4(0.24f, 0.24f, 0.24f, 1.00f);
    colors[ImGuiCol_TabActive] = ImVec4(0.24f, 0.24f, 0.24f, 1.00f);
    colors[ImGuiCol_TabUnfocused] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.24f, 0.24f, 0.24f, 1.00f);
    colors[ImGuiCol_PlotLines] = ImVec4(0.86f, 0.93f, 0.89f, 1.00f);
    colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.86f, 0.93f, 0.89f, 1.00f);
    colors[ImGuiCol_PlotHistogram] = ImVec4(0.86f, 0.93f, 0.89f, 1.00f);
    colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.86f, 0.93f, 0.89f, 1.00f);
    colors[ImGuiCol_TextSelectedBg] = ImVec4(0.24f, 0.24f, 0.24f, 1.00f);
    colors[ImGuiCol_DragDropTarget] = ImVec4(0.86f, 0.93f, 0.89f, 1.00f);
    colors[ImGuiCol_NavHighlight] = ImVec4(0.86f, 0.93f, 0.89f, 1.00f);
    colors[ImGuiCol_NavWindowingHighlight] = ImVec4(0.86f, 0.93f, 0.89f, 1.00f);
    colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
    colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.14f, 0.14f, 0.14f, 0.3f);

    style.WindowRounding = roundCornerRadius;
    style.FrameRounding = roundCornerRadius;
    style.GrabRounding = roundCornerRadius;
    style.ScrollbarRounding = roundCornerRadius;
    style.TabRounding = roundCornerRadius;
    style.ChildRounding = roundCornerRadius;
    style.PopupRounding = roundCornerRadius;

}

//void SetStylePurple()
//{
//    auto& colors = ImGui::GetStyle().Colors;
//    colors[ImGuiCol_WindowBg] = ImVec4{ 0.1f, 0.1f, 0.13f, 1.0f };
//    colors[ImGuiCol_MenuBarBg] = ImVec4{ 0.16f, 0.16f, 0.21f, 1.0f };
//
//    // Border
//    colors[ImGuiCol_Border] = ImVec4{ 0.44f, 0.37f, 0.61f, 0.29f };
//    colors[ImGuiCol_BorderShadow] = ImVec4{ 0.0f, 0.0f, 0.0f, 0.24f };
//
//    // Text
//    colors[ImGuiCol_Text] = ImVec4{ 1.0f, 1.0f, 1.0f, 1.0f };
//    colors[ImGuiCol_TextDisabled] = ImVec4{ 0.5f, 0.5f, 0.5f, 1.0f };
//
//    // Headers
//    colors[ImGuiCol_Header] = ImVec4{ 0.13f, 0.13f, 0.17f, 1.0f };
//    colors[ImGuiCol_HeaderHovered] = ImVec4{ 0.19f, 0.2f, 0.25f, 1.0f };
//    colors[ImGuiCol_HeaderActive] = ImVec4{ 0.16f, 0.16f, 0.21f, 1.0f };
//
//    // Buttons
//    colors[ImGuiCol_Button] = ImVec4{ 0.13f, 0.13f, 0.17, 1.0f };
//    colors[ImGuiCol_ButtonHovered] = ImVec4{ 0.19f, 0.2f, 0.25f, 1.0f };
//    colors[ImGuiCol_ButtonActive] = ImVec4{ 0.16f, 0.16f, 0.21f, 1.0f };
//    colors[ImGuiCol_CheckMark] = ImVec4{ 0.74f, 0.58f, 0.98f, 1.0f };
//
//    // Popups
//    colors[ImGuiCol_PopupBg] = ImVec4{ 0.1f, 0.1f, 0.13f, 0.92f };
//
//    // Slider
//    colors[ImGuiCol_SliderGrab] = ImVec4{ 0.44f, 0.37f, 0.61f, 0.54f };
//    colors[ImGuiCol_SliderGrabActive] = ImVec4{ 0.74f, 0.58f, 0.98f, 0.54f };
//
//    // Frame BG
//    colors[ImGuiCol_FrameBg] = ImVec4{ 0.13f, 0.13, 0.17, 1.0f };
//    colors[ImGuiCol_FrameBgHovered] = ImVec4{ 0.19f, 0.2f, 0.25f, 1.0f };
//    colors[ImGuiCol_FrameBgActive] = ImVec4{ 0.16f, 0.16f, 0.21f, 1.0f };
//
//    // Tabs
//    colors[ImGuiCol_Tab] = ImVec4{ 0.16f, 0.16f, 0.21f, 1.0f };
//    colors[ImGuiCol_TabHovered] = ImVec4{ 0.24, 0.24f, 0.32f, 1.0f };
//    colors[ImGuiCol_TabActive] = ImVec4{ 0.2f, 0.22f, 0.27f, 1.0f };
//    colors[ImGuiCol_TabUnfocused] = ImVec4{ 0.16f, 0.16f, 0.21f, 1.0f };
//    colors[ImGuiCol_TabUnfocusedActive] = ImVec4{ 0.16f, 0.16f, 0.21f, 1.0f };
//
//    // Title
//    colors[ImGuiCol_TitleBg] = ImVec4{ 0.16f, 0.16f, 0.21f, 1.0f };
//    colors[ImGuiCol_TitleBgActive] = ImVec4{ 0.16f, 0.16f, 0.21f, 1.0f };
//    colors[ImGuiCol_TitleBgCollapsed] = ImVec4{ 0.16f, 0.16f, 0.21f, 1.0f };
//
//    // Scrollbar
//    colors[ImGuiCol_ScrollbarBg] = ImVec4{ 0.1f, 0.1f, 0.13f, 1.0f };
//    colors[ImGuiCol_ScrollbarGrab] = ImVec4{ 0.16f, 0.16f, 0.21f, 1.0f };
//    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4{ 0.19f, 0.2f, 0.25f, 1.0f };
//    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4{ 0.24f, 0.24f, 0.32f, 1.0f };
//
//    // Seperator
//    colors[ImGuiCol_Separator] = ImVec4{ 0.44f, 0.37f, 0.61f, 1.0f };
//    colors[ImGuiCol_SeparatorHovered] = ImVec4{ 0.74f, 0.58f, 0.98f, 1.0f };
//    colors[ImGuiCol_SeparatorActive] = ImVec4{ 0.84f, 0.58f, 1.0f, 1.0f };
//
//    // Resize Grip
//    colors[ImGuiCol_ResizeGrip] = ImVec4{ 0.44f, 0.37f, 0.61f, 0.29f };
//    colors[ImGuiCol_ResizeGripHovered] = ImVec4{ 0.74f, 0.58f, 0.98f, 0.29f };
//    colors[ImGuiCol_ResizeGripActive] = ImVec4{ 0.84f, 0.58f, 1.0f, 0.29f };
//
//    auto& style = ImGui::GetStyle();
//    style.TabRounding = 4;
//    style.ScrollbarRounding = 9;
//    style.WindowRounding = 7;
//    style.GrabRounding = 3;
//    style.FrameRounding = 3;
//    style.PopupRounding = 4;
//    style.ChildRounding = 4;
//}
//
//void SetStyleViolet()
//{
//    // Violet Glow Theme (Semi-Transparent Overlay Friendly)
//    ImGuiStyle& style = ImGui::GetStyle();
//    ImVec4* colors = style.Colors;
//
//    // —— 背景类 —— //
//    colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.08f, 0.15f, 0.55f); // 深紫透明背景
//    colors[ImGuiCol_ChildBg] = ImVec4(0.10f, 0.08f, 0.15f, 0.50f);
//    colors[ImGuiCol_PopupBg] = ImVec4(0.12f, 0.10f, 0.18f, 0.70f);
//
//    // —— 文本 —— //
//    colors[ImGuiCol_Text] = ImVec4(0.95f, 0.95f, 1.00f, 1.00f);
//    colors[ImGuiCol_TextDisabled] = ImVec4(0.55f, 0.55f, 0.65f, 1.00f);
//
//    // —— 边框 —— //
//    colors[ImGuiCol_Border] = ImVec4(0.60f, 0.50f, 0.80f, 0.35f); // 微紫色
//    colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
//
//    // —— 框体 —— //
//    colors[ImGuiCol_FrameBg] = ImVec4(0.20f, 0.16f, 0.30f, 0.55f);
//    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.32f, 0.28f, 0.45f, 0.80f);
//    colors[ImGuiCol_FrameBgActive] = ImVec4(0.40f, 0.35f, 0.55f, 0.90f);
//
//    // —— 标题 —— //
//    colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.08f, 0.15f, 0.55f);
//    colors[ImGuiCol_TitleBgActive] = ImVec4(0.15f, 0.12f, 0.25f, 0.75f);
//    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.10f, 0.08f, 0.15f, 0.55f);
//
//    // —— 菜单 & 滚动条 —— //
//    colors[ImGuiCol_MenuBarBg] = ImVec4(0.12f, 0.10f, 0.18f, 0.60f);
//
//    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.08f, 0.15f, 0.40f);
//    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.48f, 0.38f, 0.80f, 0.70f);
//    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.62f, 0.50f, 1.00f, 0.85f);
//    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.72f, 0.55f, 1.00f, 0.90f);
//
//    // —— 选中 & Check —— //
//    colors[ImGuiCol_CheckMark] = ImVec4(0.75f, 0.65f, 1.00f, 1.00f);
//
//    // —— Slider —— //
//    colors[ImGuiCol_SliderGrab] = ImVec4(0.60f, 0.50f, 0.90f, 0.90f);
//    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.80f, 0.70f, 1.00f, 1.00f);
//
//    // —— 按钮 —— //
//    colors[ImGuiCol_Button] = ImVec4(0.20f, 0.16f, 0.30f, 0.60f);
//    colors[ImGuiCol_ButtonHovered] = ImVec4(0.32f, 0.28f, 0.45f, 0.80f);
//    colors[ImGuiCol_ButtonActive] = ImVec4(0.40f, 0.35f, 0.55f, 1.00f);
//
//    // —— Header（TreeNode / CollapsingHeader） —— //
//    colors[ImGuiCol_Header] = ImVec4(0.24f, 0.20f, 0.38f, 0.60f);
//    colors[ImGuiCol_HeaderHovered] = ImVec4(0.32f, 0.28f, 0.50f, 0.80f);
//    colors[ImGuiCol_HeaderActive] = ImVec4(0.40f, 0.35f, 0.55f, 1.00f);
//
//    // —— 分隔线 —— //
//    colors[ImGuiCol_Separator] = ImVec4(0.60f, 0.50f, 0.80f, 0.35f);
//    colors[ImGuiCol_SeparatorHovered] = ImVec4(0.70f, 0.60f, 0.95f, 0.60f);
//    colors[ImGuiCol_SeparatorActive] = ImVec4(0.80f, 0.70f, 1.00f, 0.80f);
//
//    // —— 调整大小 —— //
//    colors[ImGuiCol_ResizeGrip] = ImVec4(0.48f, 0.38f, 0.80f, 0.40f);
//    colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.62f, 0.50f, 1.00f, 0.70f);
//    colors[ImGuiCol_ResizeGripActive] = ImVec4(0.80f, 0.70f, 1.00f, 0.90f);
//
//    // —— Tab —— //
//    colors[ImGuiCol_Tab] = ImVec4(0.18f, 0.15f, 0.25f, 0.70f);
//    colors[ImGuiCol_TabHovered] = ImVec4(0.40f, 0.35f, 0.55f, 0.90f);
//    colors[ImGuiCol_TabActive] = ImVec4(0.35f, 0.30f, 0.50f, 0.95f);
//    colors[ImGuiCol_TabUnfocused] = ImVec4(0.12f, 0.10f, 0.18f, 0.55f);
//    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.25f, 0.22f, 0.38f, 0.75f);
//
//    // —— Plot —— //
//    colors[ImGuiCol_PlotLines] = ImVec4(0.85f, 0.80f, 1.00f, 1.00f);
//    colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.95f, 0.90f, 1.00f, 1.00f);
//    colors[ImGuiCol_PlotHistogram] = ImVec4(0.85f, 0.80f, 1.00f, 1.00f);
//    colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.95f, 0.90f, 1.00f, 1.00f);
//
//    // —— 文本选中 —— //
//    colors[ImGuiCol_TextSelectedBg] = ImVec4(0.60f, 0.50f, 0.85f, 0.50f);
//
//    // —— 其他 —— //
//    colors[ImGuiCol_DragDropTarget] = ImVec4(0.80f, 0.70f, 1.00f, 0.90f);
//    colors[ImGuiCol_NavHighlight] = ImVec4(0.80f, 0.70f, 1.00f, 1.00f);
//    colors[ImGuiCol_NavWindowingHighlight] = ImVec4(0.80f, 0.70f, 1.00f, 0.70f);
//
//    colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.10f, 0.08f, 0.15f, 0.60f);
//    colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.10f, 0.08f, 0.15f, 0.40f);
//
//    style.TabRounding = 4;
//    style.ScrollbarRounding = 9;
//    style.WindowRounding = 7;
//    style.GrabRounding = 3;
//    style.FrameRounding = 3;
//    style.PopupRounding = 4;
//    style.ChildRounding = 4;
//}
//
//void SetStyleVioletBlue()
//{
//    ImGuiStyle& style = ImGui::GetStyle();
//    ImVec4* colors = style.Colors;
//
//    // ----- 基础文字 -----
//    colors[ImGuiCol_Text] = ImVec4(0.90f, 0.95f, 1.00f, 1.00f);
//    colors[ImGuiCol_TextDisabled] = ImVec4(0.55f, 0.60f, 0.70f, 0.60f);
//
//    // ----- 半透明背景（蓝紫玻璃感）-----
//    colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.08f, 0.16f, 0.70f);
//    colors[ImGuiCol_ChildBg] = ImVec4(0.10f, 0.08f, 0.16f, 0.40f);
//    colors[ImGuiCol_PopupBg] = ImVec4(0.12f, 0.10f, 0.20f, 0.85f);
//
//    // ----- 边框（霓虹蓝紫）-----
//    colors[ImGuiCol_Border] = ImVec4(0.50f, 0.55f, 1.00f, 0.35f);
//    colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
//
//    // ----- 输入框背景 -----
//    colors[ImGuiCol_FrameBg] = ImVec4(0.15f, 0.12f, 0.25f, 0.65f);
//    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.35f, 0.30f, 0.60f, 0.75f);
//    colors[ImGuiCol_FrameBgActive] = ImVec4(0.45f, 0.40f, 0.80f, 0.90f);
//
//    // ----- 标题栏 -----
//    colors[ImGuiCol_TitleBg] = ImVec4(0.08f, 0.06f, 0.14f, 0.90f);
//    colors[ImGuiCol_TitleBgActive] = ImVec4(0.12f, 0.10f, 0.22f, 1.00f);
//    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.08f, 0.06f, 0.14f, 0.90f);
//
//    // ----- 菜单栏 -----
//    colors[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.08f, 0.18f, 0.65f);
//
//    // ----- 滚动条 -----
//    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.08f, 0.06f, 0.14f, 0.35f);
//    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.40f, 0.45f, 1.00f, 0.35f);
//    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.55f, 0.60f, 1.00f, 0.55f);
//    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.70f, 0.75f, 1.00f, 0.75f);
//
//    // ----- 选中勾（亮青蓝）-----
//    colors[ImGuiCol_CheckMark] = ImVec4(0.55f, 0.90f, 1.00f, 1.00f);
//
//    // ----- 滑条 -----
//    colors[ImGuiCol_SliderGrab] = ImVec4(0.45f, 0.45f, 1.00f, 0.70f);
//    colors[ImGuiCol_SliderGrabActive] = ImVec4(0.65f, 0.70f, 1.00f, 1.00f);
//
//    // ----- 按钮 -----
//    colors[ImGuiCol_Button] = ImVec4(0.20f, 0.18f, 0.35f, 0.60f);
//    colors[ImGuiCol_ButtonHovered] = ImVec4(0.35f, 0.32f, 0.70f, 0.78f);
//    colors[ImGuiCol_ButtonActive] = ImVec4(0.50f, 0.48f, 0.85f, 1.00f);
//
//    // ----- 列表头 -----
//    colors[ImGuiCol_Header] = ImVec4(0.30f, 0.28f, 0.55f, 0.40f);
//    colors[ImGuiCol_HeaderHovered] = ImVec4(0.40f, 0.38f, 0.70f, 0.70f);
//    colors[ImGuiCol_HeaderActive] = ImVec4(0.55f, 0.52f, 0.90f, 0.85f);
//
//    // ----- 分割线（淡霓虹）-----
//    colors[ImGuiCol_Separator] = ImVec4(0.50f, 0.55f, 1.00f, 0.30f);
//    colors[ImGuiCol_SeparatorHovered] = ImVec4(0.60f, 0.65f, 1.00f, 0.60f);
//    colors[ImGuiCol_SeparatorActive] = ImVec4(0.80f, 0.85f, 1.00f, 0.90f);
//
//    // ----- 调整握把 -----
//    colors[ImGuiCol_ResizeGrip] = ImVec4(0.40f, 0.45f, 1.00f, 0.30f);
//    colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.55f, 0.60f, 1.00f, 0.60f);
//    colors[ImGuiCol_ResizeGripActive] = ImVec4(0.75f, 0.80f, 1.00f, 1.00f);
//
//    // ----- 标签页 -----
//    colors[ImGuiCol_Tab] = ImVec4(0.10f, 0.08f, 0.18f, 0.80f);
//    colors[ImGuiCol_TabHovered] = ImVec4(0.40f, 0.38f, 0.70f, 0.90f);
//    colors[ImGuiCol_TabActive] = ImVec4(0.32f, 0.30f, 0.60f, 1.00f);
//    colors[ImGuiCol_TabUnfocused] = ImVec4(0.12f, 0.10f, 0.20f, 0.80f);
//    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.28f, 0.26f, 0.50f, 1.00f);
//
//    // ----- 高亮 / 拖放 -----
//    colors[ImGuiCol_DragDropTarget] = ImVec4(0.55f, 0.90f, 1.00f, 1.00f);
//    colors[ImGuiCol_TextSelectedBg] = ImVec4(0.40f, 0.38f, 0.70f, 0.50f);
//
//    // ----- 导航 -----
//    colors[ImGuiCol_NavHighlight] = ImVec4(0.60f, 0.80f, 1.00f, 0.70f);
//    colors[ImGuiCol_NavWindowingHighlight] = ImVec4(0.70f, 0.85f, 1.00f, 0.90f);
//    colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.05f, 0.05f, 0.10f, 0.60f);
//
//    // ----- 弹窗背景遮罩 -----
//    colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.05f, 0.04f, 0.10f, 0.70f);
//
//    style.TabRounding = 4;
//    style.ScrollbarRounding = 9;
//    style.WindowRounding = 7;
//    style.GrabRounding = 3;
//    style.FrameRounding = 3;
//    style.PopupRounding = 4;
//    style.ChildRounding = 4;
//}
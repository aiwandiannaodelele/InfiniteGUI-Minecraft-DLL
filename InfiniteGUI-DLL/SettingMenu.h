#pragma once
#include "LeftPanel.h"
#include "MainPanel.h"

constexpr ImVec2 settingMenuSize = ImVec2(900, 556);
class SettingMenu
{
public:
	SettingMenu()
	{
		leftPanel = new LeftPanel();
		mainPanel = new MainPanel();
	}
	~SettingMenu()
	{
		delete leftPanel;
		delete mainPanel;
	}
	void Init() const
	{
		mainPanel->Init();
	}
	void Draw() const
	{

		ImGui::BeginChild(u8"主控制面板Inner", settingMenuSize, true, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

		ImGui::SetCursorPos(ImVec2(0.0f, 0.0f));
		ImVec2 screenPos = ImGui::GetCursorScreenPos();

		leftPanel->Draw();
		int index = leftPanel->GetSelectedIndex();
		ImDrawList* draw = ImGui::GetWindowDrawList();
		ImVec2 pos1 = ImVec2(padding * 2 + 150.0f + screenPos.x, padding * 0.5f + screenPos.y);
		ImVec2 pos2 = ImVec2(padding * 2 + 150.0f + screenPos.x, settingMenuSize.y - padding * 0.5f + screenPos.y);
		draw->AddLine(pos1, pos2, ImGui::GetColorU32(ImGuiCol_Separator), 1.0f);
		ImGui::SetCursorPos(ImVec2(padding * 2 + 150.0f, 0.0f));
		mainPanel->SetPanelType(index);
		mainPanel->Draw();
		ImGui::EndChild();
	}

private:
	LeftPanel * leftPanel;
	MainPanel * mainPanel;
};

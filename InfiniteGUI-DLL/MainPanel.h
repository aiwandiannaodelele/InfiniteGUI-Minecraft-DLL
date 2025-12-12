#pragma once

enum PanelType
{
	ModulePanel,
	SettingsPanel,
	MorePanel,
	AboutPanel,
};

constexpr ImVec2 mainPanelSize = ImVec2(900.0f - 190.0f, 556.0f);
constexpr float padding = 20.0f;
class MainPanel
{
public:
	void Draw()
	{

		ImVec2 screenPos = ImGui::GetCursorScreenPos();

		ImDrawList* draw = ImGui::GetWindowDrawList();

		ImVec2 pos1 = ImVec2(screenPos.x + padding * 0.5f, screenPos.y + 60);
		ImVec2 pos2 = ImVec2(screenPos.x + mainPanelSize.x - padding * 0.5f, screenPos.y + 60);

		draw->AddLine(pos1, pos2, ImGui::GetColorU32(ImGuiCol_Separator), 1.0f);

		ImGui::SetCursorScreenPos(ImVec2(screenPos.x + padding, screenPos.y + 60 + padding));
		ImGui::Dummy(ImVec2(150.0f, 0.0f));
		ImGui::PushFont(NULL, ImGui::GetFontSize() * 1.5f);
		ImVec2 titleSize = ImGui::CalcTextSize(u8"模组");
		ImGui::SetCursorScreenPos(ImVec2(screenPos.x + padding, screenPos.y + 60 - titleSize.y - padding * 0.5f));
		switch (m_panelType)
		{
		case ModulePanel:

			ImGuiStd::TextShadow(u8"模组");
			ImGui::PopFont();
			// Draw Module Panel
			break;
		case SettingsPanel:
			ImGuiStd::TextShadow(u8"设置");
			ImGui::PopFont();
			// Draw Settings Panel
			break;
		case MorePanel:
			ImGuiStd::TextShadow(u8"更多");
			ImGui::PopFont();
			// Draw More Panel
			break;
		case AboutPanel:
			ImGuiStd::TextShadow(u8"关于");
			ImGui::PopFont();
			// Draw About Panel
			break;
		}
	}

	void SetPanelType(const int& index)
	{
		switch (index)
		{
		case 0:
			m_panelType = ModulePanel;
			break;
		case 1:
			m_panelType = SettingsPanel;
			break;
		case 2:
			m_panelType = MorePanel;
			break;
		case 3:
			m_panelType = AboutPanel;
			break;
		}
	}
	PanelType GetPanelType() const { return m_panelType; }

private:
	PanelType m_panelType;
};

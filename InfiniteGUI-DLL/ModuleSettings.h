#pragma once
#include "CategoryBar.h"
#include "ItemManager.h"
#include "menuRule.h"

class ModuleSettings
{
	public:
		ModuleSettings();
		~ModuleSettings();
		static bool Draw(Item *item)
		{
			ImGuiWindowFlags flags = 0;
			ImGui::BeginChild("Settings", ImVec2(-padding + ImGui::GetStyle().WindowPadding.x, -padding + ImGui::GetStyle().WindowPadding.y), true, flags);
			item->DrawSettings();
			ImGui::EndChild();
			return false;
		}//返回true退出设置界面，返回false继续运行
	private:

};

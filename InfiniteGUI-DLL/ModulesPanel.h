#pragma once
#include "CategoryBar.h"
#include "ItemManager.h"
#include "ModuleButton.h"
#include "ModuleCard.h"
class ModulesPanel
{
public:
	ModulesPanel()
	{
		m_categoryBar = new CategoryBar();
		//m_moduleButton = new ModuleButton("1", "TestModule", "TestModuleDesc", ImVec2(548, 60));
	}
	~ModulesPanel()
	{
		delete m_categoryBar;
		for (auto moduleCard : m_moduleCard)
		{
			delete moduleCard;
		}
		for (auto moduleButton : m_moduleButtons)
		{
			delete moduleButton;
		}
		//delete m_moduleButton;
	}

	void Init()
	{
		for (auto moduleCard : m_moduleCard)
		{
			delete moduleCard;
		}
		for (auto item : ItemManager::Instance().GetAllItems())
		{
			if (item->IsMultiInstance())
			{

			}
			else
				if (item->type != Hidden)
					m_moduleCard.push_back(new ModuleCard(item));
		}
	}
	void Draw() const
	{
		//获取窗口是否在scroll
		ImVec2 startPos = ImGui::GetCursorPos();
		int typeIndex = m_categoryBar->Draw();
		startPos.y += m_categoryBar->GetButtonHeight() + 13;
		ImGui::SetCursorPos(startPos);
		ImGuiWindowFlags flags = ImGuiWindowFlags_NoScrollbar;
		ImGui::BeginChild("ModuleList", ImVec2(-padding + ImGui::GetStyle().WindowPadding.x, -padding + ImGui::GetStyle().WindowPadding.y), true, flags);
		ImGui::SetCursorPos(ImVec2(padding, padding));
		for (auto moduleCard : m_moduleCard)
		{
			moduleCard->Draw();
		}
		ImGui::Dummy(ImVec2(0, 10));
		ImGui::EndChild();
	}

private:
	static bool IsWindowScrollingY()
	{
		ImGuiWindow* window = ImGui::GetCurrentWindow();
		if (!window)
			return false;

		static float lastScrollY = 0.0f;
		float curScrollY = window->Scroll.y;

		bool scrolling = (curScrollY != lastScrollY);
		lastScrollY = curScrollY;
		return scrolling;
	}
	static bool UsingMouseWheel()
	{
		return ImGui::GetIO().MouseWheel != 0.0f;
	}
	CategoryBar* m_categoryBar;
	std::vector<ModuleCard*> m_moduleCard;
	//ModuleButton* m_moduleButton;
	std::vector<ModuleButton*> m_moduleButtons;
};

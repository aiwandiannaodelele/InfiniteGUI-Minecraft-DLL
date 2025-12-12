#pragma once
#include <vector>
#include "Item.h"
#include "RenderModule.h"
#include "UpdateModule.h"
#include "ClickCircle.h"
#include "KeyState.h"

class ClickEffect : public Item, public RenderModule, public UpdateModule
{
public:
    ClickEffect() {
        type = Visual; // 信息项类型
        multiType = Singleton;    // 信息项是否可以多开
        name = u8"点击特效";
        description = u8"点点鼠标，看看会发生什么？";
		updateIntervalMs = 5;
		lastUpdateTime = std::chrono::steady_clock::now();
        Reset();
    }
    ~ClickEffect() {
		ClearClickEffects();
	}

    static ClickEffect& Instance()
    {
        static ClickEffect instance;
        return instance;
    }

    void Toggle() override;
    void Reset() override
    {
        isEnabled = true;
        enableRightClick = false;
        enableLeftClick = true;
        clickCircleSettings.Reset();
    }
    void Update() override;
    void Render() override;
    void Load(const nlohmann::json& j) override;
    void Save(nlohmann::json& j) const override;
    void DrawSettings() override;
private:
    void ClearClickEffects()
	{
		for (auto effect : clickEffects)
		{
			delete effect;
		}
		clickEffects.clear();
	}
	void AddClickEffect(ClickEffectBase* clickEffect)
	{
		clickEffects.push_back(clickEffect);
	}
	void Draw()
	{
		ImGuiIO& io = ImGui::GetIO();
		ImDrawList* drawList = ImGui::GetForegroundDrawList();
		// 倒序遍历，安全删除
		for (int i = (int)clickEffects.size() - 1; i >= 0; --i)
		{
			ClickEffectBase* effect = clickEffects[i];

			if (!effect->Draw(drawList, io.DeltaTime))
			{
				delete effect;
				clickEffects.erase(clickEffects.begin() + i);
			}
		}
	}
	KeyState keyStateHelper;
	std::vector<ClickEffectBase*> clickEffects;
	ClickCircleSettings clickCircleSettings;

	bool enabledInGame = false;
	bool enabledInGameMenu = true;
	bool enabledInMenu = true;
    bool enableRightClick = false;
    bool enableLeftClick = true;
};

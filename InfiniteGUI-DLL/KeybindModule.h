#pragma once

#include <Windows.h>
#include <vector>
#include <string>
#include <map>
#include <nlohmann/json.hpp>
#include "ImguiStd.h"
class KeybindModule
{
public:
	virtual void OnKeyEvent(bool state, bool isRepeat, WPARAM key) = 0;
    void DrawKeybindSettings()
    {
        ImGui::PushFont(NULL, ImGui::GetFontSize() * 0.8f);
        ImGui::BeginDisabled();
        ImGuiStd::TextShadow(u8"∞¥º¸∞Û∂®…Ë÷√");
        ImGui::EndDisabled();
        ImGui::PopFont();
        for (auto& [name, key] : keybinds)
        {
            ImGuiStd::Keybind(name.c_str(), key);
        }

    }
protected:
    void LoadKeybind(const nlohmann::json& j)
    {
        for (auto& [name, key] : keybinds)
        {
            if (j.contains(name))
            {
                key = j[name];
            }
        }
    }
    void SaveKeybind(nlohmann::json& j) const
    {
        for (auto& [name, key] : keybinds)
        {
            j[name] = key;
        }
    }

    void ResetKeybind()
    {
        keybinds.clear();
    }

	std::map<std::string, int> keybinds; //name, key
};
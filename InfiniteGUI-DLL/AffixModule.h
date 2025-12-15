#pragma once

#include <string>
#include <nlohmann/json.hpp>
#include "ImGuiStd.h"
class AffixModule
{
public:

    void DrawAffixSettings()
    {
        ImGui::PushFont(NULL, ImGui::GetFontSize() * 0.8f);
        ImGui::BeginDisabled();
        ImGuiStd::TextShadow(u8"前后缀设置");
        ImGui::EndDisabled();
        ImGui::PopFont();
        ImGuiStd::InputTextStd(u8"前缀", prefix);
        ImGuiStd::InputTextStd(u8"后缀", suffix);
    }
protected:
    void LoadAffix(const nlohmann::json& j)
    {
        if (j.contains("prefix")) prefix = j["prefix"];
        if (j.contains("suffix")) suffix = j["suffix"];
    }
    void SaveAffix(nlohmann::json& j) const
    {
        j["prefix"] = prefix;
        j["suffix"] = suffix;
    }

    void ResetAffix()
    {
        prefix = "[";
        suffix = "]";
    }

	std::string prefix = "[";
	std::string suffix = "]";
};
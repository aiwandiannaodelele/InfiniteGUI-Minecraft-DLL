#include "TextItem.h"
#include "ImGuiStd.h"

void TextItem::Toggle()
{
}

void TextItem::DrawContent()
{
    ImVec4 targetTextColor = ImGui::GetStyleColorVec4(ImGuiCol_Text);
    //获取io
    ImGuiIO& io = ImGui::GetIO();
    //计算速度
    float speed = 3.0f * io.DeltaTime;
    color.color = ImLerp(color.color, targetTextColor, speed);
    ImGuiStd::TextColoredShadow(color.color, (prefix + text + suffix).c_str());
}

void TextItem::DrawSettings()
{
    //DrawItemSettings();
    ImGuiStd::InputTextStd(u8"文本内容", text);
    if (ImGui::CollapsingHeader(u8"通用设置"))
    {
        DrawAffixSettings();
        DrawWindowSettings();
    }
}

void TextItem::Load(const nlohmann::json& j)
{
    LoadItem(j);
    LoadAffix(j);
    LoadWindow(j);
    if (j.contains("text")) text = j["text"];
}

void TextItem::Save(nlohmann::json& j) const
{
    SaveItem(j);
    SaveWindow(j);
    SaveAffix(j);
    j["text"] = text;
}
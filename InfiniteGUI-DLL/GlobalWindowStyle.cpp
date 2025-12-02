#include "GlobalWindowStyle.h"

void GlobalWindowStyle::Toggle()
{
}

void GlobalWindowStyle::Load(const nlohmann::json& j)
{
	LoadStyle(j);
}

void GlobalWindowStyle::Save(nlohmann::json& j) const
{
	SaveStyle(j);
}

void GlobalWindowStyle::DrawSettings()
{
	DrawStyleSettings();
}

ItemStyle& GlobalWindowStyle::GetGlobeStyle()
{
	return itemStyle;
}
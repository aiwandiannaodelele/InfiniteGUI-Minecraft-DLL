#include "GlobalConfig.h"

void GlobalConfig::Load(const nlohmann::json& j)
{
    if (j.contains("roundCornerRadius")) roundCornerRadius = j["roundCornerRadius"];
    if (j.contains("menuKey")) menuKey = j["menuKey"];
    if (j.contains("fontPath")) fontPath = j["fontPath"];
}

void GlobalConfig::Save(nlohmann::json& j) const
{
    j["roundCornerRadius"] = roundCornerRadius;
    j["menuKey"] = menuKey;
    j["fontPath"] = fontPath;
}
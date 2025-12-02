#pragma once
#include <string>
#include "GlobalConfig.h"
#include "ItemManager.h"

class ConfigManager {
public:

    static ConfigManager& Instance() {
        static ConfigManager instance;
        return instance;
    }

    static bool Save(const std::string& filePath);

    static bool Load(const std::string& filePath);
};
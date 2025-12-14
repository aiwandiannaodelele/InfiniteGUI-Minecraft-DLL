#pragma once
#include <Windows.h>
#include "imgui\imgui.h"
#include "Item.h"
#include "WindowModule.h"
#include "AffixModule.h"
#include <string>
#include <chrono>

struct cps_element {
    ImVec4 color;

};
class CPSItem : public Item, public WindowModule, public AffixModule
{
public:
    CPSItem() {
        type = Hud; // 信息项类型
        multiType = Singleton;    // 信息项是否可以多开
        name = u8"CPS显示";
        description = u8"显示左右键CPS";
        icon = "!";
        Reset();
    }
    ~CPSItem() {}

    static CPSItem& Instance() {
        static CPSItem instance;
        return instance;
    }

    void Toggle() override;
    void Reset() override
    {
        ResetAffix();
        ResetWindow();
        isEnabled = false;
        prefix = "[CPS: ";
        suffix = "]";
        showLeft = true;
        showRight = true;
    }
    void DrawContent() override;
    void DrawSettings() override;
    void Load(const nlohmann::json& j) override;
    void Save(nlohmann::json& j) const override;
private:

    bool showLeft = true;
    bool showRight = true;
    cps_element color;

};
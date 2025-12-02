#pragma once
#include "Item.h"
#include "WindowStyleModule.h"

class GlobalWindowStyle : public WindowStyleModule, public Item {
public:
    GlobalWindowStyle() {
        type = Hidden; // 信息项类型
        multiType = Singleton;    // 信息项是否可以多开
        name = u8"全局窗口样式";
        description = u8"设置全局窗口样式";
        isEnabled = true;
    }
    ~GlobalWindowStyle() {}

    static GlobalWindowStyle& Instance()
    {
        static GlobalWindowStyle instance;
        return instance;
    }

    void Toggle() override;
    void Load(const nlohmann::json& j) override;
    void Save(nlohmann::json& j) const override;
    void DrawSettings() override;
    ItemStyle& GetGlobeStyle();
private:
};
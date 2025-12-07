#pragma once
#include "Item.h"
#include "RenderModule.h"
#include "WindowStyleModule.h"
#include "KeybindModule.h"

enum MenuState {
    MENU_STATE_MAIN,
    MENU_STATE_SETTINGS,
};

enum SETTING_STATE {
    SETTING_STATE_MODULES,
    SETTING_STATE_GENERAL,
    SETTING_STATE_ABOUT,
};

struct panel_element {
    float state = 0.0f;
    float blurriness = 0;
};

class Menu : public RenderModule, public WindowStyleModule , public Item, public KeybindModule {
public:

    Menu() {
        type = Hud; // 信息项类型
        multiType = Singleton;    // 信息项是否可以多开
        name = u8"菜单";
        description = u8"显示菜单";
        isEnabled = false;

        keybinds.insert(std::make_pair(u8"菜单快捷键：", VK_OEM_5));
        itemStyle.fontSize = 20.0f;
        itemStyle.bgColor = ImVec4(0.0f, 0.0f, 0.0f, 0.1f);
    }
    panel_element panelAnim;

    MenuState state = MENU_STATE_MAIN;
    SETTING_STATE setting_state = SETTING_STATE_MODULES;

    static Menu& Instance()
    {
        static Menu instance;
        return instance;
    }

    void Render() override;
    void Toggle() override;
    void DrawSettings() override;
    void Load(const nlohmann::json& j) override;
    void Save(nlohmann::json& j) const override;
    void OnKeyEvent(bool state, bool isRepeat, WPARAM key) override;
    int GetKeyBind();
private:
    void ShowMain();
    void ShowSettings(bool* done);
    void ShowSidePanels();
    void DrawItemList();
    void DrawItemEditor(Item* item);

    void RenderMenuBlur();
    void apply_blur(int iterations) const;
    void draw_final_texture() const;
    void initialize_pingpong(const int width, const int height);
    void initialize_texture(const int width, const int height);
    void initialize_quad();
    void initialize_shader();

    void resize_texture(int width, int height);
    void draw_texture() const;
    void copy_to_current() const;

    uint32_t shader_program_;

    uint32_t current_texture_;

    uint32_t quad_vao_;
    uint32_t quad_vbo_;

    int32_t texture_width_;
    int32_t texture_height_;

    GLuint pingpongFBO[2];
    GLuint pingpongColorBuffers[2];

    bool menu_blur = true;
    int blurriness_value = 5;

};
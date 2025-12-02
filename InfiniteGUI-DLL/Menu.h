#pragma once
#include "Item.h"

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
};

class Menu {
public:

    bool open = false;
    panel_element panelAnim;

    MenuState state = MENU_STATE_MAIN;
    SETTING_STATE setting_state = SETTING_STATE_MODULES;

    static Menu& Instance()
    {
        static Menu instance;
        return instance;
    }
    Menu();

    void Render(bool* done);

    void ShowMain();
    void ShowSettings(bool* done);
    void ShowSidePanels();
    void Toggle(bool open);

    void Toggle();

private:

    void DrawItemList();
    void DrawItemEditor(Item* item);

};
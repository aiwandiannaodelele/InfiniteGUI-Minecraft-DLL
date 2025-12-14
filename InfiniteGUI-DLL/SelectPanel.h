#pragma once
#include <vector>

#include "PanelButton.h"

class SelectPanel {
public:
    SelectPanel()
    {
        buttons.emplace_back("R", u8"模组");
        buttons.emplace_back("~", u8"设置");
        buttons.emplace_back("}", u8"更多");
        buttons.emplace_back(u8"\uE009", u8"关于");
        buttons.emplace_back("=", u8"退出", true);
    }

    int Draw()
    {
        ImVec2 startPos = ImGui::GetCursorScreenPos();
        bool moving = ImGui::IsMouseDragging(0, 1.f);
        int clickedIndex = -1;
        for (int i = 0; i < buttons.size(); i++)
        {
            PanelButton& btn = buttons[i];

            // 设置按钮的“是否选中”
            btn.SetSelected(i == selectedButtonIndex);

            // 绘制按钮

            ImGui::PushFont(NULL, ImGui::GetFontSize() * 1.20f);
            bool clicked = btn.Draw(moving);
            ImGui::PopFont();
            if (clicked)
            {
                selectedButtonIndex = i;
                clickedIndex = i;
            }
        }

        return clickedIndex;   // -1 表示没有点击
    }

    int GetSelectedIndex() const { return selectedButtonIndex; }

private:
    std::vector<PanelButton> buttons;
    int selectedButtonIndex = 0;
};
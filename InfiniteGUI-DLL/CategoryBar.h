#pragma once
#include <vector>

#include "MyButton.h"
class CategoryBar {
public:
    CategoryBar()
    {
        buttons.emplace_back(u8"全部", buttonSize);
        buttons.emplace_back(u8"窗口", buttonSize);
        buttons.emplace_back(u8"视觉", buttonSize);
        buttons.emplace_back(u8"工具", buttonSize);
        buttons.emplace_back(u8"服务器", buttonSize);
    }

    int Draw()
    {
        ImVec2 curPos = ImGui::GetCursorPos();
        int clickedIndex = -1;
        for (int i = 0; i < buttons.size(); i++)
        {
            MyButton& btn = buttons[i];

            // 设置按钮的“是否选中”
            btn.SetSelected(i == selectedButtonIndex);

            // 绘制按钮

            ImGui::SetCursorPos(curPos);
            bool clicked = btn.Draw();
            if (clicked)
            {
                selectedButtonIndex = i;
                clickedIndex = i;
            }
            curPos.x += buttonSize.x + padding * 0.625f;
        }

        return clickedIndex;   // -1 表示没有点击
    }

    int GetSelectedIndex() const { return selectedButtonIndex; }
    float GetButtonHeight() const { return buttonSize.y; }

private:
    std::vector<MyButton> buttons;
    ImVec2 buttonSize = ImVec2(80, 30);
    int selectedButtonIndex = 0;
};
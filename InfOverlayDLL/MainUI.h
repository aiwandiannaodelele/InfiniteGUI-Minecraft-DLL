#pragma once
#include "InfoManager.h"
#include "TextItem.h"
#include "TimeItem.h"
#include "FileCountItem.h"
#include "BilibiliFansItem.h"
#include "CounterItem.h"
#include "DanmakuItem.h"
#include "FpsItem.h"


class MainUI {
public:

    MainUI(InfoManager* manager);

    void Render(GlobalConfig* global, bool* p_open);

private:
    InfoManager* manager;

    void DrawItemList();
    void DrawItemEditor(InfoItem* item);
    void Draw_TextItemSettings(TextItem* item);
    void Draw_TimeItemSettings(TimeItem* item);
    void Draw_FpsItemSettings(FpsItem* item);
    void Draw_FileCountItemSettings(FileCountItem* item);
    void Draw_CounterItemSettings(CounterItem* item);
    void Draw_BilibiliItemSettings(BilibiliFansItem* item);
    void Draw_DanmakuItemSettings(DanmakuItem* item);
};
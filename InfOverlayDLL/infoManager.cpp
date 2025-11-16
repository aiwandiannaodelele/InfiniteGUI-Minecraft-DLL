#include "InfoManager.h"
#include "TimeItem.h"
#include "FpsItem.h"
#include "BilibiliFansItem.h"
#include "FileCountItem.h"
#include "CounterItem.h"
#include "DanmakuItem.h"
#include "TextItem.h"
#include "GlobalConfig.h"

#include <chrono>


InfoManager::InfoManager()
{
}

void InfoManager::AddItem(std::shared_ptr<InfoItem> item)
{
    items.push_back(std::move(item));
}


// ---------------------------------------------
// 删除信息项（简单版）
// ---------------------------------------------
void InfoManager::RemoveItem(int index)
{
    if (index >= 0 && index < items.size()) {
        items.erase(items.begin() + index);

    }

}

void InfoManager::UpdateAll()
{
    auto now = std::chrono::steady_clock::now();

    for (auto& item : items) {
        if (item->ShouldUpdate() && item->isEnabled) {
            item->Update();      // 执行item的更新操作
            item->MarkUpdated(); // 更新最后更新时间
        }
    }
}


// ---------------------------------------------
// 渲染所有信息项（每帧调用）
// ---------------------------------------------
void InfoManager::RenderAll(GlobalConfig* globalConfig, HWND hwnd)
{

    for (auto& item : items) {

        item->RenderWindow(globalConfig, hwnd);
    }
}

// ---------------------------------------------
// 从 JSON 加载全部信息项
// ---------------------------------------------
void InfoManager::Load(const nlohmann::json& j)
{
    if (!j.contains("infoItems")) return;
    for (auto& v : j["infoItems"])
    {
        std::string type = v["type"].get<std::string>();
        std::unique_ptr<InfoItem> item;

        if (type == "text")
        {
            item = std::make_unique<TextItem>();
        }
        else if (type == "time") {
            item = std::make_unique<TimeItem>();
        }
        else if (type == "fps") {
            item = std::make_unique<FpsItem>();
        }
        else if (type == "bilibili_fans") {
            item = std::make_unique<BilibiliFansItem>();
        }
        else if (type == "file_count") {
            item = std::make_unique<FileCountItem>();
        }
        else if (type == "counter") {
            item = std::make_unique<CounterItem>();
        }
        else if (type == "danmaku") {
            item = std::make_unique<DanmakuItem>();
        }
        else {
            continue;
        }

        item->Load(v);
        AddItem(std::move(item));
    }
}

// ---------------------------------------------
// 保存所有信息项
// ---------------------------------------------
void InfoManager::Save(nlohmann::json& j) const
{
    j["infoItems"] = nlohmann::json::array();

    for (auto& item : items)
    {
        nlohmann::json v;
        item->Save(v);
        j["infoItems"].push_back(v);
    }
}
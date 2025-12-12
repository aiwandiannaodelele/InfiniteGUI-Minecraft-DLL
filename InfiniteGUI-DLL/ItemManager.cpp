#include <Windows.h>
#include "ItemManager.h"
#include "TimeItem.h"
#include "FpsItem.h"
#include "DanmakuItem.h"
#include "KeystrokesItem.h"
#include "CPSItem.h"
#include "BilibiliFansItem.h"
#include "FileCountItem.h"
#include "CounterItem.h"
#include "TextItem.h"

#include "Sprint.h"

#include "Motionblur.h"
#include "ClickEffect.h"

#include "CPSDetector.h"
#include "GameStateDetector.h"
#include "GlobalWindowStyle.h"

#include "Menu.h"
#include <algorithm>
#include <chrono>

// ------------------------------------------------
ItemManager::ItemManager()
{
    Init();
}

void ItemManager::Init()
{
    // 注册默认 Singleton
    AddSingleton(&Menu::Instance());

    AddSingleton(&Sprint::Instance());

    AddSingleton(&Motionblur::Instance());
    AddSingleton(&ClickEffect::Instance());

    AddSingleton(&TimeItem::Instance());
    AddSingleton(&FpsItem::Instance());
    AddSingleton(&DanmakuItem::Instance());
    AddSingleton(&KeystrokesItem::Instance());
    AddSingleton(&CPSItem::Instance());

    AddSingleton(&GlobalWindowStyle::Instance());
    AddSingleton(&GameStateDetector::Instance());
    AddSingleton(&CPSDetector::Instance());
}

// ------------------------------------------------
void ItemManager::AddSingleton(Item* item)
{
    singletonItems.push_back(item);
    allItems.push_back(item);
}

void ItemManager::AddMulti(std::unique_ptr<Item> item)
{
    allItems.push_back(item.get());
    multiItems.push_back(std::move(item));
}

void ItemManager::RemoveMulti(Item* target)
{
    if (!target) return;
    if (!target->IsMultiInstance()) {
        return; // 禁止删除 Singleton
    }
    // 1. 在 multiItems 中查找 unique_ptr 所拥有的对象
    for (auto it = multiItems.begin(); it != multiItems.end(); ++it)
    {
        if (it->get() == target)
        {
            // 2. 从 allItems 中移除
            allItems.erase(
                std::remove(allItems.begin(), allItems.end(), target),
                allItems.end()
            );

            // 3. 从 multiItems 中删除（自动 delete）
            multiItems.erase(it);
            return; // 删除完立刻返回
        }
    }
}

// ------------------------------------------------
void ItemManager::UpdateAll() const
{
    for (auto item : allItems)
    {
        if (!item->isEnabled) continue;
        if (auto upd = dynamic_cast<UpdateModule*>(item))
        {
            if (upd->ShouldUpdate())
            {
                upd->Update();
                upd->MarkUpdated();
            }
        }
    }
}

// ------------------------------------------------
void ItemManager::RenderAll() const
{
    bool isWindowNeedHide = false;
    if (GameStateDetector::Instance().IsNeedHide())
        isWindowNeedHide = true; // 隐藏所有窗口
    for (auto item : allItems)
    {
        if (!item->isEnabled) continue;
        if (auto ren = dynamic_cast<RenderModule*>(item))
        {
            if (auto motionblur = dynamic_cast<Motionblur*>(ren))
                if (motionblur->applayOnMenu && Menu::Instance().isEnabled) continue;

            if (auto win = dynamic_cast<WindowModule*>(ren) && isWindowNeedHide)
                continue;

            ren->Render();
        }
    }
}

// ------------------------------------------------
void ItemManager::ProcessKeyEvents(bool state, bool isRepeat, WPARAM key) const
{
    for (auto item : allItems)
    {
        if (auto kbd = dynamic_cast<KeybindModule*>(item))
        {
            if (auto menu = dynamic_cast<Menu*>(kbd))
                menu->OnKeyEvent(state, isRepeat, key);
            if (!item->isEnabled) continue;
            kbd->OnKeyEvent(state, isRepeat, key);
        }
    }
}

// ------------------------------------------------
// JSON Load / Save
// ------------------------------------------------
void ItemManager::Load(const nlohmann::json& j)
{
    // ---- 加载单例 ----
    if (j.contains("SingletonItems"))
    {
        for (auto& node : j["SingletonItems"])
        {
            std::string type = node["type"];
            for (auto item : singletonItems)
            {
                if (item->name == type)
                {
                    item->Load(node);
                    break;
                }
            }
        }
    }
    // ---- 清空多例并重建 ----
    multiItems.clear();
    allItems.erase(
        std::remove_if(allItems.begin(), allItems.end(),
            [&](Item* it) { return it->IsMultiInstance(); }),
        allItems.end()
    );

    if (j.contains("MultiInstanceItems"))
    {
        for (auto& node : j["MultiInstanceItems"])
        {
            std::unique_ptr<Item> item;
            std::string type = node["type"];

            if (type == u8"粉丝数显示") item = std::make_unique<BilibiliFansItem>();
            if (type == u8"文件数量显示") item = std::make_unique<FileCountItem>();
            if (type == u8"计数器")     item = std::make_unique<CounterItem>();
            if (type == u8"文本显示")   item = std::make_unique<TextItem>();

            if (!item) continue;

            item->Load(node);
            AddMulti(std::move(item));
        }
    }
}

// ------------------------------------------------
void ItemManager::Save(nlohmann::json& j) const
{
    j["SingletonItems"] = nlohmann::json::array();
    j["MultiInstanceItems"] = nlohmann::json::array();

    for (auto item : singletonItems)
    {
        nlohmann::json node;
        item->Save(node);
        j["SingletonItems"].push_back(node);
    }

    for (auto& up : multiItems)
    {
        nlohmann::json node;
        up->Save(node);
        j["MultiInstanceItems"].push_back(node);
    }
}

void ItemManager::Clear(bool resetSingletons)
{
    // ---- 1. 删除多例 Items ----
    multiItems.clear(); // unique_ptr 自动释放对象内存

    // ---- 2. 清理 allItems 中剩余的多例条目 ----
    allItems.erase(
        std::remove_if(allItems.begin(), allItems.end(),
            [&](Item* it) { return it->IsMultiInstance(); }),
        allItems.end()
    );

    // ---- 3. 重置所有 SingletonItems（可选，根据需求） ----
    if (resetSingletons)
    {
        for (auto* item : singletonItems)
        {
            item->Reset();   //  要求 Item 提供 Reset() 或默认状态
        }
    }
}
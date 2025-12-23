#pragma once

#include "NotificationItem.h"

void NotificationItem::AddNotification(NotificationType type, const std::string& message)
{
	int index = (int)notifications.size();
	Notification notification(type, message, index, itemStyle);
	notifications.push_back(notification);
	dirtyState.animating = true;
}

void NotificationItem::PopNotification()
{
	notifications.pop_front();
	for (int i = 0; i < notifications.size(); i++)
	{
		notifications[i].SetPlaceIndex(i);
	}
}

void NotificationItem::Update()
{
	if (notifications.empty())
	{
		dirtyState.animating = false;
		return;
	}
	if (notifications.front().Done())
	{
		PopNotification();
	}
	for (auto& notification : notifications)
	{
		notification.ShouldLeave();
	}
}

void NotificationItem::Toggle()
{
}

void NotificationItem::RenderGui()
{
	for (auto& notification : notifications)
	{
		notification.RenderGui();
	}
}

void NotificationItem::RenderBeforeGui()
{
}

void NotificationItem::RenderAfterGui()
{
}

void NotificationItem::DrawSettings(const float& bigPadding, const float& centerX, const float& itemWidth)
{
	float bigItemWidth = centerX * 2.0f - bigPadding * 4.0f;

	ImGui::SetCursorPosX(bigPadding);

	if (ImGui::Button(u8"点我测试",ImVec2(bigItemWidth, 0.0f)))
	{
		AddNotification(NotificationType_Info, u8"这是一条测试弹窗~");
	}
	DrawStyleSettings(bigPadding, centerX, itemWidth);
}

void NotificationItem::Load(const nlohmann::json& j)
{
	LoadItem(j);
	LoadStyle(j);
}

void NotificationItem::Save(nlohmann::json& j) const
{
	SaveItem(j);
	SaveStyle(j);
}

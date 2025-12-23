#include "GameStateDetector.h"
#include "App.h"
#include "KeyState.h"
#include "Menu.h"
void GameStateDetector::Toggle()
{
}
void GameStateDetector::Update()
{
	
	if (Menu::Instance().isEnabled)
		currentState = InMenu;
	else if (IsMouseCursorVisible())
		currentState = InGameMenu;
	else
		currentState = InGame;

	isInGameWindow = opengl_hook::handle_window == GetForegroundWindow();

	if (currentState != lastState)
	{
		dirtyState.contentDirty = true;
		lastState = currentState;
	}

}

void GameStateDetector::Load(const nlohmann::json& j)
{
	LoadItem(j);
	if (j.contains("hideItemInGui")) hideItemInGui = j["hideItemInGui"].get<bool>();
}

void GameStateDetector::Save(nlohmann::json& j) const
{
	SaveItem(j);
	j["hideItemInGui"] = hideItemInGui;
}

void GameStateDetector::DrawSettings(const float& bigPadding, const float& centerX, const float& itemWidth)
{
	ImGui::PushFont(NULL, ImGui::GetFontSize() * 0.8f);
	ImGui::BeginDisabled();
	ImGuiStd::TextShadow(u8"游戏状态检测设置");
	ImGui::EndDisabled();
	ImGui::PopFont();
	ImGui::SetCursorPosX(bigPadding);
	ImGui::PushItemWidth(itemWidth);
	ImGui::Checkbox(u8"仅在游戏内显示Gui", &hideItemInGui);
	ImGui::SameLine(); ImGuiStd::HelpMarker(u8"对于mc1.12及以下版本全屏时此功能将失效，请关闭，否则Gui无法正常显示。");
}

bool GameStateDetector::IsNeedHide() const 
{
	return currentState == InGameMenu && hideItemInGui;
}

GameState GameStateDetector::GetCurrentState() const
{
	return currentState;
}

bool GameStateDetector::IsInGameWindow() const
{
	return isInGameWindow;
}

bool GameStateDetector::IsInGame() const
{
	return (currentState == InGame);
}

bool IsClipCursorSmallerThanScreen(int margin = 8)
{
	RECT clip;
	if (!GetClipCursor(&clip))
		return true;

	const int screenW = GetSystemMetrics(SM_CXSCREEN);
	const int screenH = GetSystemMetrics(SM_CYSCREEN);

	const int clipW = clip.right - clip.left;
	const int clipH = clip.bottom - clip.top;

	// 1. 尺寸明显小于屏幕
	if (clipW < screenW - margin * 2 ||
		clipH < screenH - margin * 2)
	{
		return true;
	}

	// 2. 边界有明显内缩
	if (clip.left > margin ||
		clip.top > margin ||
		clip.right < screenW - margin ||
		clip.bottom < screenH - margin)
	{
		return true;
	}

	return false;
}


bool GameStateDetector::IsMouseCursorVisible()
{
	CURSORINFO ci;
	ci.cbSize = sizeof(ci);

	if (GetCursorInfo(&ci))
	{
		if (!(ci.flags & CURSOR_SHOWING)) return false;
	}
	return !IsClipCursorSmallerThanScreen(0);
}

void GameStateDetector::ProcessMouseMovement(int dx, int dy)
{
	// 鼠标移动速度 = 模长
	cameraSpeed = sqrtf((float)dx * (float)dx + (float)dy * (float)dy);

	// 视角是否移动（为了给你逻辑判断）
	if (cameraSpeed > movementThreshold)
		cameraMoving = true;
	else
		cameraMoving = false;
	if(Menu::Instance().isEnabled || !IsInGame())
	{
		cameraMoving = false;
		cameraSpeed = 1.0f;
	}
}

bool GameStateDetector::IsCameraMoving() const
{
	return cameraMoving;
}

float GameStateDetector::GetCameraSpeed() const
{
	return cameraSpeed;
}

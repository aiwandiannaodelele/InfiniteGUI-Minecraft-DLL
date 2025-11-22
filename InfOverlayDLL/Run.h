#pragma once
#include <Windows.h>

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND, UINT, WPARAM, LPARAM);

// È«¾Ö×´Ì¬
static bool g_isInit = false;
static WNDPROC g_oldWndProc = NULL;

BOOL WINAPI MySwapBuffers(HDC hdc);

DWORD WINAPI InitThread(LPVOID);

void Uninit();
#include "Run.h"
#include "ItemManager.h"
#include "ConfigManager.h"
#include "Menu.h"
#include "GlobalConfig.h"
#include "StringConverter.h"
#include "FileUtils.h"
#include "AudioManager.h"
#include "App.h"
#include "fonts\Uranus_Pixel_11Px.h"
#include "fonts\IconFont.h"
#include "pics\MCInjector-small.h"
#include "pch.h"
#include "ImguiSty.h"
#include <thread>
#include "GameStateDetector.h"
#include "ImageLoader.h"
typedef BOOL(WINAPI* OldSwapBuffers)(HDC);
OldSwapBuffers fpSwapBuffers = NULL;
static bool done = false;

static std::atomic<bool> g_running{ true };
// 仅当 uiActive=true 时，让 ImGui 处理 Win32 消息
LRESULT CALLBACK HookedWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    bool isRepeat = (lParam & (1 << 30)) != 0;
    bool state;
    if (message == WM_KEYDOWN || message == WM_LBUTTONDOWN || message == WM_RBUTTONDOWN ||
        message == WM_MBUTTONDOWN || message == WM_XBUTTONDOWN)
        state = true;
    else if (message == WM_KEYUP || message == WM_LBUTTONUP || message == WM_RBUTTONUP ||
        message == WM_MBUTTONUP || message == WM_XBUTTONUP)
        state = false;
    else
        state = true;

    ItemManager::Instance().ProcessKeyEvents(state, isRepeat, wParam);
    // 1. 按键检测
    if (state)
    {
        if (wParam == GlobalConfig::Instance().menuKey &&!isRepeat)
            Menu::Instance().Toggle();

        if (wParam == VK_ESCAPE && Menu::Instance().open)
            Menu::Instance().Toggle();

    }

    if (Menu::Instance().open)
    {
        // 只有 UI 激活时才把消息交给 ImGui 处理
        ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam);
        switch (message)
        {
        case WM_IME_STARTCOMPOSITION:
        case WM_IME_ENDCOMPOSITION:
        case WM_IME_COMPOSITION:

        case WM_IME_SETCONTEXT:
        case WM_IME_NOTIFY:
        case WM_IME_CONTROL:
        case WM_IME_COMPOSITIONFULL:
        case WM_IME_SELECT:
        case WM_IME_CHAR:
        case WM_IME_REQUEST:
        case WM_IME_KEYDOWN:
        case WM_IME_KEYUP:

        case WM_INPUTLANGCHANGEREQUEST:
        case WM_INPUTLANGCHANGE:

        case WM_DESTROY:
        case WM_QUIT:
        case WM_CLOSE:
            goto end;
        default:
            return TRUE;
        }

    }
end:
    // 始终把消息交回原来的窗口过程（不管 UI 是否激活）
    return CallWindowProc(g_oldWndProc, hWnd, message, wParam, lParam);
}

// 线程函数：更新所有 item 状态
void UpdateThread() {
    App::Instance().GetAnnouncement();
    while (g_running.load()) {
        ItemManager::Instance().UpdateAll();  // 调用UpdateAll()来更新所有item
        std::this_thread::sleep_for(std::chrono::milliseconds(1));  // 休眠100ms，可以根据实际需求调整
    }
}

// 启动更新线程
void StartUpdateThread() {
    std::thread updateThread(UpdateThread);
    updateThread.detach();  // 将线程设为后台线程
}



// 在找到有效 HDC/窗口后初始化 ImGui（只初始化一次）
void InitImGuiForContext()
{
    if (!wglGetCurrentContext())
    {
        return;
    }
    if (g_isInit) return;
    if (!App::Instance().clientHwnd) return;

    g_oldWndProc = (WNDPROC)SetWindowLongPtr(App::Instance().clientHwnd, GWLP_WNDPROC, (LONG_PTR)HookedWndProc);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // 可选
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // 可选

    // 默认关闭 ImGui 捕获鼠标（只有激活 UI 时允许）
    io.MouseDrawCursor = false;
    io.ConfigFlags |= ImGuiConfigFlags_NoMouse; // 禁止 ImGui 捕获鼠标输入（我们在切换时会调整）
    io.IniFilename = nullptr; // 禁止生成 imgui.ini
    //ImGui::StyleColorsDark();
    SetStyleGray(GlobalConfig::Instance().roundCornerRadius);
    //SetStylePurple();
    //SetStyleViolet();
    //SetStyleVioletBlue();

    // 初始化平台/渲染绑定。GLSL 版本根据 MC 的 GL context 版本可调整
    ImGui_ImplWin32_Init(App::Instance().clientHwnd);

    //ImGui_ImplOpenGL3_Init("#version 130"); // 如果你的 MC 是较新 GL，可改为 "#version 330 core"
     // 尝试获取当前 OpenGL 上下文信息
    const GLubyte* glVersionStr = glGetString(GL_VERSION);
    const GLubyte* glRendererStr = glGetString(GL_RENDERER);

    if (!glVersionStr)
    {
        MessageBoxA(App::Instance().clientHwnd, "OpenGL context not ready! Please call after SwapBuffers hook is active.", "Error", MB_ICONERROR);
        return;
    }

    std::string glVersion(reinterpret_cast<const char*>(glVersionStr));
    std::string glRenderer(reinterpret_cast<const char*>(glRendererStr ? glRendererStr : (const GLubyte*)"Unknown"));

    int major = 0, minor = 0;
    sscanf(glVersion.c_str(), "%d.%d", &major, &minor);

    const char* glsl_version = "#version 130"; // fallback default

    if (major >= 4) glsl_version = "#version 410 core";
    else if (major == 3 && minor >= 3) glsl_version = "#version 330 core";
    else if (major == 3 && minor >= 2) glsl_version = "#version 150 core";

    // 输出检测结果到控制台（或日志）
    std::string msg = "Detected OpenGL version: " + glVersion +
        "\nRenderer: " + glRenderer +
        "\nUsing GLSL: " + glsl_version + "\n";
    OutputDebugStringA(msg.c_str());
    ImGui_ImplOpenGL3_Init(glsl_version);
    ImFontConfig font_cfg;
    font_cfg.FontDataOwnedByAtlas = false;
    font_cfg.OversampleH = 1;
    font_cfg.OversampleV = 1;
    font_cfg.PixelSnapH = true;


    ImFont* font;
    if (GlobalConfig::Instance().fontPath == "default")
        font = io.Fonts->AddFontFromMemoryCompressedTTF(Ur_data, Ur_size, 20.0f, &font_cfg, io.Fonts->GetGlyphRangesChineseFull());
    else
        font = io.Fonts->AddFontFromFileTTF(GlobalConfig::Instance().fontPath.c_str(), 20.0f, &font_cfg, io.Fonts->GetGlyphRangesChineseFull());
    if (font == nullptr) {
        font = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\msyh.ttc", 20.0f, &font_cfg, io.Fonts->GetGlyphRangesChineseFull());
    }
    App::Instance().iconFont = io.Fonts->AddFontFromMemoryTTF(iconfont, iconfontsize, 20.0f, &font_cfg);


    io.FontDefault = font;

    g_isInit = true;

    App::Instance().logoTexture.id = LoadTextureFromMemory(logo, logoSize, &App::Instance().logoTexture.width, &App::Instance().logoTexture.height);

    //加载配置文件
    ConfigManager::Load(FileUtils::GetConfigPath());
    //初始化音频管理器
    AudioManager::Instance().Init();
    StartUpdateThread();  // 启动更新线程
}


//struct GLStateBackup {
//    GLint last_program, last_active_texture, last_texture;
//    GLint last_array_buffer, last_vertex_array;
//    GLint last_blend_src_rgb, last_blend_dst_rgb, last_blend_src_alpha, last_blend_dst_alpha;
//    GLboolean last_enable_blend, last_enable_scissor, last_enable_cull, last_enable_depth_test;
//    GLint last_viewport[4];
//    GLint last_scissor_box[4];
//};
//
//static void BackupGLState(GLStateBackup& s) {
//    glGetIntegerv(GL_CURRENT_PROGRAM, &s.last_program);
//    glGetIntegerv(GL_ACTIVE_TEXTURE, &s.last_active_texture);
//    glActiveTexture(GL_TEXTURE0);
//    glGetIntegerv(GL_TEXTURE_BINDING_2D, &s.last_texture);
//    glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &s.last_array_buffer);
//    // VAO may not be supported in very old GL; guard if needed.
//    glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &s.last_vertex_array);
//    glGetIntegerv(GL_VIEWPORT, s.last_viewport);
//    glGetIntegerv(GL_SCISSOR_BOX, s.last_scissor_box);
//    s.last_enable_blend = glIsEnabled(GL_BLEND);
//    s.last_enable_scissor = glIsEnabled(GL_SCISSOR_TEST);
//    s.last_enable_cull = glIsEnabled(GL_CULL_FACE);
//    s.last_enable_depth_test = glIsEnabled(GL_DEPTH_TEST);
//    glGetIntegerv(GL_BLEND_SRC_RGB, &s.last_blend_src_rgb);
//    glGetIntegerv(GL_BLEND_DST_RGB, &s.last_blend_dst_rgb);
//    glGetIntegerv(GL_BLEND_SRC_ALPHA, &s.last_blend_src_alpha);
//    glGetIntegerv(GL_BLEND_DST_ALPHA, &s.last_blend_dst_alpha);
//}
//
//static void RestoreGLState(const GLStateBackup& s) {
//    glUseProgram(s.last_program);
//    glActiveTexture(s.last_active_texture);
//    glBindTexture(GL_TEXTURE_2D, s.last_texture);
//    glBindBuffer(GL_ARRAY_BUFFER, s.last_array_buffer);
//    glBindVertexArray(s.last_vertex_array);
//    if (s.last_enable_blend) glEnable(GL_BLEND); else glDisable(GL_BLEND);
//    if (s.last_enable_scissor) glEnable(GL_SCISSOR_TEST); else glDisable(GL_SCISSOR_TEST);
//    if (s.last_enable_cull) glEnable(GL_CULL_FACE); else glDisable(GL_CULL_FACE);
//    if (s.last_enable_depth_test) glEnable(GL_DEPTH_TEST); else glDisable(GL_DEPTH_TEST);
//    glBlendFuncSeparate(s.last_blend_src_rgb, s.last_blend_dst_rgb, s.last_blend_src_alpha, s.last_blend_dst_alpha);
//    glViewport(s.last_viewport[0], s.last_viewport[1], s.last_viewport[2], s.last_viewport[3]);
//    glScissor(s.last_scissor_box[0], s.last_scissor_box[1], s.last_scissor_box[2], s.last_scissor_box[3]);
//}

// Hooked SwapBuffers - 每次换帧都会被调用
BOOL WINAPI MySwapBuffers(HDC hdc)
{
    if (done)
    {
        static bool once = true;
        if (once) {
            CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Uninit, g_hModule, 0, NULL);
            once = false;
        }
        return fpSwapBuffers(hdc);
    }
    // 获取与当前 HDC 关联的顶层窗口（只在首次时用于初始化）
    if (!App::Instance().clientHwnd)
    {
        HWND possible = WindowFromDC(hdc);
        if (possible) App::Instance().clientHwnd = possible;
    }

    // 在首次有有效窗口时初始化 ImGui（安全）
    if (!g_isInit && App::Instance().clientHwnd)
    {
        InitImGuiForContext();
        //MyGuiBloom = new BloomImGui::FxBloomSystem(1000, 618);//这个为窗口大小
    }

    // 如果 ImGui 未初始化，直接调用原 SwapBuffers
    if (!g_isInit)
        return fpSwapBuffers(hdc);

    // 切换 ImGui 鼠标捕获设置
    ImGuiIO& io = ImGui::GetIO();
    if (Menu::Instance().open)
    {
        io.ConfigFlags &= ~ImGuiConfigFlags_NoMouse; // 允许 ImGui 处理鼠标
    }
    else
    {
        io.ConfigFlags |= ImGuiConfigFlags_NoMouse;  // 禁止 ImGui 捕获鼠标
    }
    // --- 新帧 ---
    ImGui_ImplOpenGL3_NewFrame(); // 如果不可用，可省略（一些版本没有此函数，但通常有）
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    {
        ItemManager::Instance().RenderAll();
        Menu::Instance().Render(&done);
    }

    // 渲染 ImGui
    ImGui::Render();


    //GLStateBackup backup;
    //BackupGLState(backup);

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    //RestoreGLState(backup);
    // 如果多视口 (通常注入到 MC 时不使用多视口) -- 跳过

    // 调用原始 SwapBuffers
    return fpSwapBuffers(hdc);
}

// 为安全：避免重复初始化/卸载
static bool g_hookInitialized = false;
static bool g_mhInitialized = false;
// 初始化 Hook（在单独线程里执行）
DWORD WINAPI InitThread(LPVOID)
{
    do
    {
        GameStateDetector::Instance().Update();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    } while (!GameStateDetector::Instance().IsInGame());

    if (g_mhInitialized) return 0;

    if (MH_Initialize() != MH_OK)
    {
        return 0;
    }
    g_mhInitialized = true;

    // 创建 Hook（对 wglSwapBuffers）
    // 注意：直接使用 &SwapBuffers 也可（GDI SwapBuffers），这里 hook opengl 的 SwapBuffers（用户提供的代码用 SwapBuffers）
    if (MH_CreateHookApi(L"opengl32", "wglSwapBuffers", &MySwapBuffers, reinterpret_cast<void**>(&fpSwapBuffers)) != MH_OK)
    {
        // fallback: try hooking SwapBuffers from GDI32 (less likely)
        if (MH_CreateHook(&::SwapBuffers, &MySwapBuffers, reinterpret_cast<void**>(&fpSwapBuffers)) != MH_OK)
        {
            // failed to create hook
            MH_Uninitialize();
            g_mhInitialized = false;
            return 0;
        }
    }

    // 启用所有 hook
    if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK)
    {
        MH_DisableHook(MH_ALL_HOOKS);
        MH_Uninitialize();
        g_mhInitialized = false;
        return 0;
    }

    g_hookInitialized = true;
    return 0;
}

void Uninit(HMODULE hModule)
{
    // 先停止后台循环
    g_running.store(false);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    // 卸载 ImGui
    if (g_isInit)
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplWin32_Shutdown();
        ImGui::DestroyContext();
        g_isInit = false;
    }

    // 恢复窗口过程
    if (App::Instance().clientHwnd && g_oldWndProc)
    {
        SetWindowLongPtr(App::Instance().clientHwnd, GWLP_WNDPROC, (LONG_PTR)g_oldWndProc);
        g_oldWndProc = NULL;
    }

    AudioManager::Instance().Shutdown();// 卸载音频管理器
    ItemManager::Instance().Shutdown(); // 卸载 ItemManager
    // 卸载 MinHook
    if (g_mhInitialized)
    {
        MH_DisableHook(MH_ALL_HOOKS);
        MH_RemoveHook(MH_ALL_HOOKS);
        MH_Uninitialize();
        g_mhInitialized = false;
        g_hookInitialized = false;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    if (hModule) {
        // 注意： FreeLibraryAndExitThread 会立即结束当前线程。确保调用点是合适的。
        FreeLibrary(hModule);
    }
}

#pragma once
#include "imgui/imgui.h"
#include <GL/glew.h>
#include <GL/GL.h>
struct Texture
{
	GLuint id;
	int width;
	int height;
};

class Gui
{
public:
	bool isInit = false;
	bool done = false;
	void init();
	static void clean();
	static void render();
	ImFont* font;
	ImFont* iconFont;
	ImFont* titleFont;
	Texture logoTexture;
};


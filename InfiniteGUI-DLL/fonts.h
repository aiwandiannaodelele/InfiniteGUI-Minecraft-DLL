#pragma once

struct FontData
{
	unsigned char* data;
	int size;
};

namespace Fonts
{
	void init();
	inline FontData harmony = { nullptr, 0 };
	inline FontData ur = { nullptr, 0 };
	inline FontData icons = { nullptr, 0 };
};


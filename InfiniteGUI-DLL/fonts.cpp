#include "fonts.h"
#include "fonts\AlibabaPuHuiTi-3-85-Bold.h"
#include "fonts\IconFont.h"
#include "fonts\Uranus_Pixel_11Px.h"

void Fonts::init()
{
	alibaba = { alibaba_data , alibaba_size };
	icons = { iconFont, iconFontsize };
	ur = { Ur_data, Ur_size };
}

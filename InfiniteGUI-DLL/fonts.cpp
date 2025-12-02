#include "fonts.h"
#include "fonts\harmony_sc_regular.h"
#include "fonts\IconFont.h"
#include "fonts\Uranus_Pixel_11Px.h"

void Fonts::init()
{
	harmony = { harmony_sc_regular , harmony_sc_regular_size };
	icons = { iconfont, iconfontsize };
	ur = { Ur_data, Ur_size };
}

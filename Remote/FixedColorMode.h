#ifndef FIXED_COLOR_MODE_H
#define FIXED_COLOR_MODE_H
#include "Mode.h"
using namespace std;
class FixedColorMode : public Mode {
private:
	int mColor;
public:
	FixedColorMode(LedDisplay& display, Radio &radio, int color, String name, int x, int y) 
		: Mode(name, display, radio, x, y) , mColor(color) {}
};
#endif


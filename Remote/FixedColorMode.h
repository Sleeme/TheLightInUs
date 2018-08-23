#ifndef FIXED_COLOR_MODE_H
#define FIXED_COLOR_MODE_H
#include "Mode.h"
using namespace std;
class FixedColorMode : public Mode {
private:
	int mColor;
public:
	FixedColorMode(LedDisplay& display, int color, String name, int x, int y) : Mode(name, display, x, y) , mColor(color) {}
};
#endif


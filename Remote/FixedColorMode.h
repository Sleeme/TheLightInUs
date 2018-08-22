#ifndef FIXED_COLOR_MODE_H
#define FIXED_COLOR_MODE_H
#include "Mode.h"
using namespace std;
class FixedColorMode : public Mode {
private:
	int mColor;
public:
	FixedColorMode(LedDisplay& display, int color, String name) : Mode(name, display) , mColor(color) {}
	void onModeSelected();
};
#endif


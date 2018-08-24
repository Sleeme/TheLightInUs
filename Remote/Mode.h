#ifndef MODE_H
#define MODE_H
#include "WString.h"
#include "LedDisplay.h"

using namespace std;
class Mode {
private:
	String mName;
	LedDisplay& mDisplay;
	int mX, mY;
public:
	Mode(String name, LedDisplay& display, int x, int y) : mName(name), mDisplay(display), mX(x), mY(y) {}
	void onModeSelected();
	int getLightId();
};
#endif

#ifndef MODE_H
#define MODE_H
#include "WString.h"
#include "LedDisplay.h"

using namespace std;
class Mode {
private:
	String mName;
	LedDisplay& mDisplay;
public:
	Mode(String name, LedDisplay& display) : mName(name), mDisplay(display) {}
	void onModeSelected();
	void onDraw();
};
#endif

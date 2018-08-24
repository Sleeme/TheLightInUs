#ifndef MODE_H
#define MODE_H
#include "WString.h"
#include "LedDisplay.h"

class Radio;

using namespace std;
class Mode {
private:
	String mName;
	LedDisplay& mDisplay;
	int mX, mY;
	Radio &mRadio;
public:
	Mode(String name, LedDisplay& display, Radio &radio, int x, int y) : mName(name), mDisplay(display), 
		mX(x), mY(y), mRadio(radio) {}
	void onModeSelected();
	int getLightId();
	String getChangeMessage();
};
#endif

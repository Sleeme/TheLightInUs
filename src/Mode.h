#ifndef MODE_H
#define MODE_H
#include "WString.h"
#include "LedDisplay.h"
#include "LightingState.h"

using namespace std;
class Mode {
private:
	String mName;
	int mX, mY;
public:
	Mode(String name, int x, int y) : mName(name), 
		mX(x), mY(y) {}
	int getLightId();
	String getChangeMessage();
	String getName();
	virtual void applyMode(LightingState *state);
};
#endif

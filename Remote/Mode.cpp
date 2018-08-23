#include "Mode.h"
using namespace std;

void Mode::onModeSelected() {
	mDisplay.setText(mName);
}

int Mode::getX()
{
	return mX;
}

int Mode::getY()
{
	return mY;
}





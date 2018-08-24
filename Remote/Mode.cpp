#include "Mode.h"
using namespace std;

void Mode::onModeSelected() {
	mDisplay.setText(mName);
}

int Mode::getLightId()
{
	return mX + mY * 4;
}





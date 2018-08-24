#include "Mode.h"
#include "Radio.h"

using namespace std;

void Mode::onModeSelected() {
	mDisplay.setText(mName);
	mRadio.sendModeChange(this);
}

int Mode::getLightId()
{
	return mX + mY * 4;
}

String Mode::getChangeMessage()
{
	return "M" + getLightId();
}





#include "Mode.h"
#include "Radio.h"

using namespace std;

int Mode::getLightId()
{
	return mX + mY * 4;
}

String Mode::getChangeMessage()
{
	String result = "M";
	result += getLightId();
	return result;
}

String Mode::getName()
{
	return mName;
}





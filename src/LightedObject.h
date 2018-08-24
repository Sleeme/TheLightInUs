#pragma once
#include "Radio.h"
class LightedObject
{
private:
	RH_RF69 *mRf69;
	Radio *mRadio;
	int mUniqueId;
	char *mBuffer;
public:
	LightedObject(int uniqueId);
	void onSetup();
	void onLoop();
};


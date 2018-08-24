#pragma once
#include "Radio.h"
class LightedObject
{
private:
	RH_RF69 *mRf69;
	Radio *mRadio;
public:
	LightedObject();
	void onSetup();
	void onLoop();
};


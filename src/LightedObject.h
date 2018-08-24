#pragma once
#include "Radio.h"
#include "ModeRegistry.h"
class LightedObject
{
private:
	RH_RF69 *mRf69;
	Radio *mRadio;
	int mUniqueId;
	char *mBuffer;
	ModeRegistry mModeRegistry;
	int mSelectedModeId;
public:
	LightedObject(int uniqueId);
	void onSetup();
	void onLoop();
};


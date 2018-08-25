#pragma once
#include "Radio.h"
#include "ModeRegistry.h"
#include "LightedPart.h"
#undef min
#undef max
#include <vector>

class LightedObject
{
private:
	RH_RF69 *mRf69;
	Radio *mRadio;
	int mUniqueId;
	char *mBuffer;
	ModeRegistry mModeRegistry;
	int mSelectedModeId;
	vector<LightedPart*> mLightedParts;
public:
	LightedObject(int uniqueId);
	void onSetup();
	void onLoop();
	void nextMode();
	void addLightedPart(LightedPart *part);
};


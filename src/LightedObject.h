#pragma once
#include "Radio.h"
#include "ModeRegistry.h"
#include "LightedPart.h"
#include <Adafruit_NeoPXL8.h>
#include "LightingState.h"
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
	int8_t *mPins;
	Adafruit_NeoPXL8 *mLights;
	LightingState *mLightState;
	boolean mOn = true;
public:
	LightedObject(int uniqueId, int defaultMode);
	void onSetup();
	void onLoop();
	void nextMode();
	void addLightedPart(LightedPart *part);
	void onLongPress();
};


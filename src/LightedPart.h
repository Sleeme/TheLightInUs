#pragma once
#include "LightingState.h"

class LightedPart
{
private:
	int mLedLength;
	int mLightDistanceFromOrigin;
public:
	LightedPart(int ledLength, int lightDistanceFromOrigin);
	void applyState(LightingState state);
};


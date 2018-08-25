#pragma once
class LightingState;

class LightedPart
{
private:
	int mLedLength;
	int mLightDistanceFromOrigin;
	int mLightStartId;
public:
	LightedPart(int ledLength, int lightDistanceFromOrigin);
	void applyState(LightingState* state);
	int getLedLength();
	int getLightDistanceFromOrigin();
	void setLightStartId(int startId);
};


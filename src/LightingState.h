#pragma once
#include <Adafruit_NeoPXL8.h>
#undef min
#undef max
#include <vector>
using namespace std;

class LightedPart;

class LightingState
{
private:
	uint32_t *mLightBuffer;
	Adafruit_NeoPXL8 *mLights;
	vector<LightedPart*> *mParts;
	int mMaxLightDistance;
public:
	LightingState(Adafruit_NeoPXL8 *lights, vector<LightedPart*> *lightParts,
		int maxLightDistance);
	uint32_t *getLightBuffer();
	Adafruit_NeoPXL8 *getLights();
	void apply();
	int getBufferLength();
};


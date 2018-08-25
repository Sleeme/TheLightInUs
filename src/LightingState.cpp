#include "LightingState.h"
#include "LightedPart.h"

LightingState::LightingState(Adafruit_NeoPXL8 *lights, vector<LightedPart*> *lightParts,
	int maxLightDistance) : mLights(lights), mParts(lightParts),
	mMaxLightDistance(maxLightDistance)
{
	mLightBuffer = new uint32_t[maxLightDistance];
}

uint32_t * LightingState::getLightBuffer()
{
	return mLightBuffer;
}

Adafruit_NeoPXL8* LightingState::getLights()
{
	return mLights;
}

void LightingState::apply()
{
	Serial.println("apply");
	for (int i = 0; i < mParts->size(); i++) {
		mParts->at(i)->applyState(this);
	}
}

int LightingState::getBufferLength()
{
	return mMaxLightDistance;
}

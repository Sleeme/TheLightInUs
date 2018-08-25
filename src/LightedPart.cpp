#include "LightedPart.h"
#include "LightingState.h"
#include <Adafruit_NeoPXL8.h>

LightedPart::LightedPart(int ledLength, int lightDistanceFromOrigin) 
	: mLedLength(ledLength), mLightDistanceFromOrigin(lightDistanceFromOrigin)
{
}

void LightedPart::applyState(LightingState* state)
{
	uint32_t *lightBuffer = state->getLightBuffer();
	int end = mLightStartId + mLedLength;
	Adafruit_NeoPXL8* lights = state->getLights();
	for (int lightIndex = 0; lightIndex < mLedLength; lightIndex++) {
		uint32_t color = lightBuffer[mLightDistanceFromOrigin + lightIndex];
		lights->setPixelColor(mLightStartId + lightIndex, color);
	}
}

int LightedPart::getLightDistanceFromOrigin()
{
	return mLightDistanceFromOrigin;
}

void LightedPart::setLightStartId(int startId)
{
	mLightStartId = startId;
}

int LightedPart::getLedLength()
{
	return mLedLength;
}

#include "LightedPart.h"

LightedPart::LightedPart(int ledLength, int lightDistanceFromOrigin) 
	: mLedLength(ledLength), mLightDistanceFromOrigin(lightDistanceFromOrigin)
{
}

void LightedPart::applyState(LightingState state)
{
}

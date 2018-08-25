#include "FixedColorMode.h"

void FixedColorMode::applyMode(LightingState * state)
{
	uint32_t *lightBuffer = state->getLightBuffer();
	int length = state->getBufferLength();
	for (int i = 0; i < length; i++) {
		lightBuffer[i] = mColor;
	}
	state->apply();
}

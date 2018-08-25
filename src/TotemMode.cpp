#include "TotemMode.h"

void TotemMode::applyMode(LightingState * state)
{
	uint32_t *lightBuffer = state->getLightBuffer();
	int length = state->getBufferLength();
	for (int i = 0; i < length; i++) {
		lightBuffer[i] = 255;
	}
	state->apply();
}

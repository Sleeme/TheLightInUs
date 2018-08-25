#include "TotemMode.h"

void TotemMode::applyMode(LightingState * state)
{
	uint32_t *lightBuffer = state->getLightBuffer();
	int length = state->getBufferLength();
	Adafruit_NeoPXL8 *lights = state->getLights();
	int duration = 8000;
	int color = 0xff00ff;
	int r = (color >> 16) & 0x0000ff;
	int g = (color >> 8) & 0x0000ff;
	int b = color & 0x0000ff;
	float timeFraction = (millis() % duration) / (float) duration;
	float waveLength = length;
	int highLightIndex = (int) (-waveLength * (1.0f - timeFraction) + (length + waveLength) * timeFraction);
	for (int i = 0; i < length; i++) {
		float fraction = min(1.0f, abs(i - highLightIndex) / waveLength);
		lightBuffer[i] =  lights->Color(r*fraction, g * fraction, b*fraction);
	}
	state->apply();
}

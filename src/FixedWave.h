#ifndef FIXED_WAVE_H
#define FIXED_WAVE_H
#include "Mode.h"
#include "Radio.h"

using namespace std;
class FixedWave : public Mode {
private:
	int mColor;
public:
	FixedWave(int color, int x, int y) : Mode("Sara", x, y), mColor(color) {}
	virtual void applyMode(LightingState *state);
};
#endif

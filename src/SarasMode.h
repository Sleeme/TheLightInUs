#ifndef SARAS_MODE_H
#define SARAS_MODE_H
#include "Mode.h"
#include "Radio.h"

using namespace std;
class SarasMode : public Mode {
private:
	int mColor;
public:
	SarasMode(int color, int x, int y) : Mode("Sara", x, y), mColor(color) {}
	virtual void applyMode(LightingState *state);
};
#endif

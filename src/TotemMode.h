#ifndef TOTEM_MODE_H
#define TOTEM_MODE_H
#include "Mode.h"
#include "Radio.h"

using namespace std;
class TotemMode : public Mode {
public:
	TotemMode(int x, int y) : Mode("Totem", x, y) {}
	virtual void applyMode(LightingState *state);
};
#endif

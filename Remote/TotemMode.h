#ifndef TOTEM_MODE_H
#define TOTEM_MODE_H
#include "Mode.h"
#include "Radio.h"

using namespace std;
class TotemMode : public Mode {
public:
	TotemMode(LedDisplay& display, Radio &radio, int x, int y) : Mode("Totem", display, radio, x, y) {}
};
#endif

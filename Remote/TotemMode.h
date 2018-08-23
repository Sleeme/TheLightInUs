#ifndef TOTEM_MODE_H
#define TOTEM_MODE_H
#include "Mode.h"

using namespace std;
class TotemMode : public Mode {
public:
	TotemMode(LedDisplay& display, int x, int y) : Mode("Totem", display, x, y) {}
};
#endif

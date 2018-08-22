#ifndef TOTEM_MODE_H
#define TOTEM_MODE_H
#include "Mode.h"

using namespace std;
class TotemMode : public Mode {
public:
	TotemMode(LedDisplay& display) : Mode("Totem", display) {}
	void onModeSelected();
};
#endif

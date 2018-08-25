#pragma once
#include "Mode.h"
#undef min
#undef max
#include <vector>

class ModeRegistry
{
private:
	vector<Mode*> mModes;
public:
	ModeRegistry();
	Mode* getMode(int id);
	int nextModeId(int currentModeId);
};


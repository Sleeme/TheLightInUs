#include "ModeRegistry.h"
#include "TotemMode.h"
#include "FixedColorMode.h"

ModeRegistry::ModeRegistry()
{
	mModes = vector<Mode*>(16);
	Mode *mode = new TotemMode(0, 0);
	mModes[mode->getLightId()] = mode;
	mode = new FixedColorMode(0xffffff, "White", 0, 1);
	mModes[mode->getLightId()] = mode;
	mode = new FixedColorMode(0x0000ff, "Blue", 1, 1);
	mModes[mode->getLightId()] = mode;
	mode = new FixedColorMode(0xff778f, "Pink", 2, 1);
	mModes[mode->getLightId()] = mode;
	mode = new FixedColorMode(0xff0000, "Red", 3, 1);
	mModes[mode->getLightId()] = mode;
}

Mode * ModeRegistry::getMode(int id)
{
	return mModes[id];
}

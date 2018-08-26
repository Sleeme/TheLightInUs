#include "ModeRegistry.h"
#include "TotemMode.h"
#include "FixedColorMode.h"
#include "SarasMode.h"

ModeRegistry::ModeRegistry()
{
	mModes = vector<Mode*>(16);
	Mode *mode = new TotemMode(0, 0);
	mModes[mode->getLightId()] = mode;
	mode = new SarasMode(0xff00ff, 1, 0);
	mModes[mode->getLightId()] = mode;
	mode = new SarasMode(0xffffff, 2, 0);
	mModes[mode->getLightId()] = mode;
	mode = new SarasMode(0x0000ff, 3, 0);
	mModes[mode->getLightId()] = mode;
	mode = new SarasMode(0x8800ff, 0, 1);
	mModes[mode->getLightId()] = mode;
	mode = new FixedColorMode(0xffffff, "White", 1, 1);
	mModes[mode->getLightId()] = mode;
	mode = new FixedColorMode(0x0000ff, "Blue", 2, 1);
	mModes[mode->getLightId()] = mode;
	mode = new FixedColorMode(0xff778f, "Pink", 3, 1);
	mModes[mode->getLightId()] = mode;
	mode = new FixedColorMode(0xff0000, "Red", 0, 2);
	mModes[mode->getLightId()] = mode;
}

Mode * ModeRegistry::getMode(int id)
{
	return mModes[id];
}

int ModeRegistry::nextModeId(int currentModeId)
{
	currentModeId = (currentModeId + 1) % mModes.size();
	while(getMode(currentModeId) == NULL) {
		currentModeId = (currentModeId + 1) % mModes.size();
	}
	return currentModeId;
}

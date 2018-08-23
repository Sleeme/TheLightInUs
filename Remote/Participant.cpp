#include "Participant.h"

void Participant::setSelectedMode(Mode* selectedMode)
{
	mSelectedMode = selectedMode;
}

Mode * Participant::getSelectedMode()
{
	return mSelectedMode;
}

String Participant::getName()
{
	return mName;
}

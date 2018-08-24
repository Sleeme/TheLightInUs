#include "Participant.h"

void Participant::setSelectedMode(Mode* selectedMode)
{
	mSelectedMode = selectedMode;
}

Mode * Participant::getSelectedMode()
{
	return mSelectedMode;
}

String Participant::getChangeMessage()
{
	String result = "";
	result += mUniqueId + mSelectedMode->getChangeMessage();
	return result;
}

String Participant::getName()
{
	return mName;
}

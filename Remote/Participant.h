#pragma once
#include "WString.h"
#include "Participant.h"
#include "Mode.h"

class Participant
{
private:
	String mName;
	int mUniqueId;
	Mode* mSelectedMode;
public:
	Participant(String name, int uniqueId, Mode* startMode) : mName(name), mUniqueId(uniqueId), mSelectedMode(startMode) {};
	void setSelectedMode(Mode* selectedMode);
	Mode* getSelectedMode();
	String getName();
};
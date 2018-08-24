#pragma once
#include "Participant.h"

using namespace std;
class Everyone : public Participant
{
public:
	Everyone(Mode* startMode) : Participant("All", 0, startMode) {};
	void setSelectedMode(Mode * selectedMode);
};


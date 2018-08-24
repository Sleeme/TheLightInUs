#pragma once
#include "Participant.h"

using namespace std;
class Everyone : public Participant
{
public:
	Everyone(Mode* startMode) : Participant("All", 1, startMode) {};
	void setSelectedMode(Mode * selectedMode);
};


#pragma once
#include <SPI.h>
#include <RH_RF69.h>
#include "Participant.h"

class Radio
{
private:
	RH_RF69 *mRadio;
	int mOwnId;
	uint8_t mBuf[RH_RF69_MAX_MESSAGE_LEN];
public:
	Radio(RH_RF69 *radio, int ownId) : mRadio(radio), mOwnId(ownId) {};
	void onLoop();
	void sendModeChange(Participant *participant);
	boolean receiveMessage(char * buf);
};


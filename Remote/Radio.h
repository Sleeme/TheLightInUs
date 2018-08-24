#pragma once
#include <SPI.h>
#include <RH_RF69.h>

class Mode;

class Radio
{
private:
	RH_RF69& mRadio;
public:
	Radio(RH_RF69 &radio) : mRadio(radio) {};
	void onLoop();
	void sendModeChange(Mode *newMode);
};


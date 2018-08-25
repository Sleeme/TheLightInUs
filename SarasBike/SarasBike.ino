
// rf69_server.pde
// -*- mode: C++ -*-
// Example sketch showing how to create a simple messageing server
// with the RH_RF69 class. RH_RF69 class does not provide for addressing or
// reliability, so you should only use RH_RF69  if you do not need the higher
// level messaging abilities.
// It is designed to work with the other example rf69_client
// Demonstrates the use of AES encryption, setting the frequency and modem
// configuration.
// Tested on Moteino with RFM69 http://lowpowerlab.com/moteino/
// Tested on miniWireless with RFM69 www.anarduino.com/miniwireless
// Tested on Teensy 3.1 with RF69 on PJRC breakout board

#include <Adafruit_NeoMatrix_ZeroDMA.h>
#include <Adafruit_NeoPXL8.h>
#include "src/LightedObject.h"

LightedObject mBike(3);
void setup()
{
	// Front wheel
	mBike.addLightedPart(new LightedPart(39, 0));
	// Middle and Back
	mBike.addLightedPart(new LightedPart(108, 10));
	// Top + Handle
	mBike.addLightedPart(new LightedPart(62, 0));
	// Ring + LED
	mBike.addLightedPart(new LightedPart(20, 0));
	mBike.onSetup();
}

void loop()
{
	mBike.onLoop();
}

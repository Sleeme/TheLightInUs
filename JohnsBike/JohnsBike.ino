
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
#include <MD_UISwitch.h>

LightedObject mBike(3, 1);
const uint8_t DIGITAL_SWITCH_ACTIVE = LOW;  // digital signal when switch is pressed 'on'

MD_UISwitch_Digital S(6, DIGITAL_SWITCH_ACTIVE);
void setup()
{
	// Front wheel
	mBike.addLightedPart(new LightedPart(39, 0));
	// Middle and Back
	mBike.addLightedPart(new LightedPart(108, 10));
	// Top 
	mBike.addLightedPart(new LightedPart(62, 0));
	// Ring + LED + Handle
	mBike.addLightedPart(new LightedPart(108, 0));
	mBike.onSetup();
}

void loop()
{
	MD_UISwitch::keyResult_t k = S.read();

	switch (k)
	{
	case MD_UISwitch::KEY_NULL:      /* Serial.println("NULL"); */  break;
	case MD_UISwitch::KEY_PRESS: {
		Serial.print("\nKEY_PRESS ");
		mBike.nextMode();
		break;
	}
	case MD_UISwitch::KEY_DPRESS:    Serial.print("\nKEY_DOUBLE "); break;
	case MD_UISwitch::KEY_LONGPRESS: {
		Serial.print("\nKEY_LONG   "); 
		mBike.onLongPress();
		break;
	}
	case MD_UISwitch::KEY_RPTPRESS:  Serial.print("\nKEY_REPEAT "); break;
	default:                         Serial.print("\nKEY_UNKNWN "); break;
	}
	mBike.onLoop();
}

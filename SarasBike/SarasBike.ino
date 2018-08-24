
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

#include <SPI.h>
#include <RH_RF69.h>
#include "src/Radio.h"

#if defined(ARDUINO_SAMD_FEATHER_M0) // Feather M0 w/Radio
#define RFM69_CS      8
#define RFM69_INT     3
#define RFM69_RST     4
#endif

// Singleton instance of the radio driver
RH_RF69 rf69(RFM69_CS, RFM69_INT);
Radio mRadio(rf69);

void setup()
{
	Serial.begin(9600);
	while (!Serial)
		;
	if (!rf69.init())
		Serial.println("init failed");
	// Defaults after init are 434.0MHz, modulation GFSK_Rb250Fd250, +13dbM (for low power module)
	// No encryption
	if (!rf69.setFrequency(915.0))
		Serial.println("setFrequency failed");

	// If you are using a high power RF69 eg RFM69HW, you *must* set a Tx power with the
	// ishighpowermodule flag set like this:
	rf69.setTxPower(14, true);

	// The encryption key has to be the same as the one in the client
	uint8_t key[] = { 0x33, 0x91, 0x3a, 0e8, 0x25, 0x01, 0x21, 0x08,
					0x11, 0x29, 0xd0, 0xaa, 0x65, 0x06, 0x07, 0x5c };
	rf69.setEncryptionKey(key);

#if 0
	// For compat with RFM69 Struct_send
	rf69.setModemConfig(RH_RF69::GFSK_Rb250Fd250);
	rf69.setPreambleLength(3);
	uint8_t syncwords[] = { 0x2d, 0x64 };
	rf69.setSyncWords(syncwords, sizeof(syncwords));
	rf69.setEncryptionKey((uint8_t*)"thisIsEncryptKey");
#endif
}

void loop()
{
	mRadio.receiveMessage();
}

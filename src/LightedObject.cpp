#include "LightedObject.h"
#include <SPI.h>
#include <RH_RF69.h>

#define RFM69_CS      8
#define RFM69_INT     3
#define RFM69_RST     4

LightedObject::LightedObject(int uniqueID) : mUniqueId(uniqueID)
{
	// Singleton instance of the radio driver
	mRf69 = new RH_RF69(RFM69_CS, RFM69_INT);
	mRadio = new Radio(mRf69, mUniqueId);
	mBuffer = new char[2];
}

void LightedObject::onSetup()
{
	Serial.begin(9600);
	while (!Serial);
	if (mRf69->init())
		Serial.println("init failed");
	// Defaults after init are 434.0MHz, modulation GFSK_Rb250Fd250, +13dbM (for low power module)
	// No encryption
	if (mRf69->setFrequency(915.0))
		Serial.println("setFrequency failed");

	// If you are using a high power RF69 eg RFM69HW, you *must* set a Tx power with the
	// ishighpowermodule flag set like this:
	mRf69->setTxPower(14, true);

	// The encryption key has to be the same as the one in the client
	uint8_t key[] = { 0x33, 0x91, 0x3a, 0e8, 0x25, 0x01, 0x21, 0x08,
					0x11, 0x29, 0xd0, 0xaa, 0x65, 0x06, 0x07, 0x5c };
	mRf69->setEncryptionKey(key);
}

void LightedObject::onLoop()
{
	// Let's see if we got any messages
	if (mRadio->receiveMessage(mBuffer)) {
		if (mBuffer[0] == 'M') {
			Serial.println("Received Mode change! ");
			int modeId = 0;
			for (int i = 1; mBuffer[i] != 'E'; i++) {
				int number = mBuffer[i] - '0';
				modeId = modeId * 10 + number;
			}
			mSelectedModeId = modeId;
		}
	}
	Mode *selectedMode = mModeRegistry.getMode(mSelectedModeId);
	if (selectedMode != NULL) {
		selectedMode->applyMode();
	}
}

void LightedObject::nextMode()
{
	mSelectedModeId = mModeRegistry.nextModeId(mSelectedModeId);
}

void LightedObject::addLightedPart(LightedPart * part)
{
	mLightedParts.push_back(part);
}

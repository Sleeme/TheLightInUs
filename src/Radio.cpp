#include "Radio.h"
#include "Mode.h"
#include "WString.h"

void Radio::onLoop()
{
	if (mRadio.available())
	{
		// Should be a message for us now   
		uint8_t buf[RH_RF69_MAX_MESSAGE_LEN];
		uint8_t len = sizeof(buf);
		if (mRadio.recv(buf, &len))
		{
			//      RH_RF69::printBuffer("request: ", buf, len);
			Serial.print("got request: ");
			Serial.println((char*)buf);
			//      Serial.print("RSSI: ");
			//      Serial.println(rf69.lastRssi(), DEC);

				  // Send a reply
			uint8_t data[] = "And hello back to you";
			mRadio.send(data, sizeof(data));
			mRadio.waitPacketSent();
			Serial.println("Sent a reply");
		}
		else
		{
			Serial.println("recv failed");
			uint8_t data[] = "Hello";
			mRadio.send(data, sizeof(data));
		}
	}
}

void Radio::sendModeChange(Participant *participant)
{
	String message = participant->getChangeMessage();
	const char *cmsg = message.c_str();
	mRadio.send((const uint8_t*) cmsg, sizeof(cmsg));
	Serial.println(cmsg);
}

char* Radio::receiveMessage() {
	if (mRadio.available()) {
		// Should be a message for us now   
		uint8_t buf[RH_RF69_MAX_MESSAGE_LEN];
		uint8_t len = sizeof(buf);
		if (mRadio.recv(buf, &len))
		{
			//      RH_RF69::printBuffer("request: ", buf, len);
			Serial.print("received: ");
			Serial.println(String((char *)buf).substring(0, len));
			return (char*)buf;
		}
	}
	return NULL;
}

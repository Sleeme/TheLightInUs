#include "Radio.h"
#include "Mode.h"
#include "WString.h"
using namespace std;

void Radio::onLoop()
{
	
}

void Radio::sendModeChange(Participant *participant)
{
	String message = participant->getChangeMessage();
	const char *cmsg = message.c_str();
	mRadio->send((const uint8_t*) cmsg, sizeof(cmsg));
	Serial.println(cmsg);
}

boolean Radio::receiveMessage(char * buf) {
	return false;
	if (mRadio->available()) {
		// Should be a message for us now   
		uint8_t len = sizeof(mBuf);
		if (mRadio->recv((uint8_t*) mBuf, &len))
		{
			//      RH_RF69::printBuffer("request: ", buf, len);
			Serial.print("received: ");
			char *message = (char *)mBuf;
			Serial.println(String(message).substring(0, len));
			int participantId = message[0] - '0';
			if (participantId == mOwnId || participantId == 1) {
				memcpy(buf, message+1, (len - 1 * sizeof(char)));
				return true;
			}
		}
	}
	return false;
}

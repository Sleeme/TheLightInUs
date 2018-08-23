// TargetSelector.h

#ifndef PARTICIPANT_SELECTOR_H
#define PARTICIPANT_SELECTOR_H
#define PIN_ENCODER_SWITCH 11
#include "WString.h"
#include "LedDisplay.h"
#include "Participant.h"
#include <Encoder.h>
#include "Adafruit_Trellis.h"
#undef min
#undef max
#include <vector>

using namespace std;
class ParticipantManager {
private:
	int mSelectedParticipantId = 0;
	long mSelectionTime;
	int mActiveParticipant = 0;
	uint8_t mActiveRow = 0;
	long mRotaryPosition = -999;
	long mNewpos;
	int mPrevButtonState = HIGH;
	unsigned long mActivationTime;
	int mSelectedTargetId = -1;
	LedDisplay& mDisplay;
	vector<Participant> mParticipants;
	Adafruit_TrellisSet& mTrellis;
	Encoder& mEncoder;

public:
	ParticipantManager(LedDisplay& display, Encoder& encoder, Adafruit_TrellisSet& trellis, Mode* defaultMode) : mDisplay(display)
		, mEncoder(encoder), mTrellis(trellis) {
		mParticipants.push_back(Participant("All", -1, defaultMode));
		mParticipants.push_back(Participant("Selim", 0, defaultMode));
		mParticipants.push_back(Participant("Sara", 1, defaultMode));
		mParticipants.push_back(Participant("John", 2, defaultMode));
		mParticipants.push_back(Participant("Board", 3, defaultMode));
		mParticipants.push_back(Participant("Totem", 4, defaultMode));
	}
	void onModeSelected(Mode* mode);
	boolean onLoop();
	void handleRotary();
};
#endif


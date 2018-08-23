#include "ParticipantManager.h"

void ParticipantManager::onModeSelected(Mode* mode)
{
	Participant selected = mParticipants[mSelectedParticipantId];
	Mode * previousMode = selected.getSelectedMode();
	if (mode != previousMode) {
		selected.setSelectedMode(mode);
		int prevId = previousMode->getX() + previousMode->getY() * 4;
		mTrellis.clrLED(prevId);
	}
}


boolean ParticipantManager::onLoop()
{
	handleRotary();
}

void ParticipantManager::handleRotary()
{
	/*************Rotary Encoder Menu***********/

	//check the encoder knob, set the current position as origin
	int numParticipants = mParticipants.size();
	long newpos = mEncoder.read() / 4;//divide for encoder detents
	if (newpos != mRotaryPosition) {
		if (mRotaryPosition != -999) {
			int diff = newpos - mRotaryPosition;//check the different between old and new position
			if (diff >= 1) {
				mSelectedParticipantId++;
				mSelectedParticipantId = (mSelectedParticipantId + numParticipants) % numParticipants;//modulo to roll over the m variable through the list size
			}
			else { //rotating backwards
				mSelectedParticipantId--;
				mSelectedParticipantId = (mSelectedParticipantId + numParticipants) % numParticipants;
			}
		}
		mRotaryPosition = newpos;
		Participant selected = mParticipants[mSelectedParticipantId];
		Mode *activeMode = selected.getSelectedMode();
		mDisplay.setText(selected.getName());
		int lightId = activeMode->getX() + activeMode->getY() * 4;

		//clear Trellis lights 
		for (int t = 0;t <= 16;t++) {
			if (t != lightId) {
				mTrellis.clrLED(t);
			} else {
				mTrellis.setLED(16);
			}
		}
		mTrellis.writeDisplay();
	}

	// remember that the switch is active low
	unsigned long now = millis();
	int buttonState = digitalRead(PIN_ENCODER_SWITCH);
	if (buttonState == LOW) {
		if (mPrevButtonState == HIGH && mActiveParticipant != mSelectedParticipantId) {
			mPrevButtonState = buttonState;
			mActivationTime = now;
			mSelectionTime = 0;
			mActiveParticipant = mSelectedParticipantId;
			//set this above the physical range so 
												//next button press works properly
		}
	}
	else if (buttonState == HIGH && mPrevButtonState == LOW) {
		//Serial.println("button released!");
		mPrevButtonState = buttonState;
	}
	int timeSinceSelection = now - mSelectionTime;
}

#include "LedDisplay.h"
using namespace std;

void LedDisplay::draw() {
	int totalLength = mCurrentText.length() * 6;
	long current = millis();
	long offset = ((current - mDrawStart));
	int position;
	if (offset < START_DELAY) {
		position = 0;
	}
	else {
		offset = (offset - START_DELAY) / 60;
		if (offset < totalLength) {
			position = -offset;
		}
		else {
			offset -= totalLength;
			position = (-offset) % (totalLength + LED_WIDTH) + LED_WIDTH;
			int numIteration = offset / (totalLength + LED_WIDTH);
			if (numIteration == 1) {
				position = max(position, 0);
			}
			else if (numIteration > 1) {
				position = 0;
			}
		}
	}
	if (position != mLastPosition) {
		mMatrix.clear();
		mMatrix.setCursor(position, 0);
		mMatrix.print(mCurrentText);
		mLastPosition = position;
	}
}

void LedDisplay::setText(String text)
{
	if (text.compareTo(mCurrentText) != 0) {
		mCurrentText = text;
		mLastPosition = -10000;
		mDrawStart = millis();
	}
}

#include "LedDisplay.h"
using namespace std;

void LedDisplay::drawText(String text) {
	if (text.compareTo(mLastText) != 0) {
		mLastText = text;
		mLastPosition = -10000;
		mDrawStart = millis();
	}
	mMatrix.setTextSize(1);
	mMatrix.setTextWrap(false);  // we dont want text to wrap so it scrolls nicely
	mMatrix.setTextColor(10);
	int totalLength = text.length() * 6;
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
		mMatrix.print(text);
		mLastPosition = position;
	}
}

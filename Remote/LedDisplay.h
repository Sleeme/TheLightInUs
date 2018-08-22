#pragma once
#include "WString.h"
#include <Adafruit_GFX.h>
#include <Adafruit_IS31FL3731.h>
#define LED_HEIGHT 7
#define LED_WIDTH 15
#define START_DELAY 300

class LedDisplay
{
private:
	Adafruit_IS31FL3731_Wing& mMatrix;
	int mLastPosition = -10000;
	String mLastText = "";
	long mDrawStart;
public:
	LedDisplay(Adafruit_IS31FL3731_Wing& matrix) : mMatrix(matrix) {
	}
	void drawText(String text);
};


// Selim Cinek and John Javscovski
//  Burning man Art Project
//
// The Light In Us.
//
// MIT License

#include "ParticipantManager.h"
#include "TotemMode.h"
#include "FixedColorMode.h"
#include <SPI.h>
#include <RH_RF69.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_IS31FL3731.h>
#include "Adafruit_Trellis.h"
#include <Encoder.h>
#include "Radio.h"
using namespace std;

/********* Encoder Setup ***************/
#define PIN_ENCODER_SWITCH 11
Encoder knob(10, 12);

/********* Trellis Setup ***************/
Adafruit_Trellis matrix0 = Adafruit_Trellis();
Adafruit_TrellisSet trellis = Adafruit_TrellisSet(&matrix0);
#define NUMTRELLIS 1
#define numKeys (NUMTRELLIS * 16)
#define INTPIN A2

/************ OLED Setup ***************/
Adafruit_IS31FL3731_Wing matrix = Adafruit_IS31FL3731_Wing();
LedDisplay display = LedDisplay(matrix);
#if defined(ESP8266)
  #define BUTTON_A 0
  #define BUTTON_B 16
  #define BUTTON_C 2
  #define LED      0
#elif defined(ESP32)
  #define BUTTON_A 15
  #define BUTTON_B 32
  #define BUTTON_C 14
  #define LED      13
#elif defined(ARDUINO_STM32F2_FEATHER)
  #define BUTTON_A PA15
  #define BUTTON_B PC7
  #define BUTTON_C PC5
  #define LED PB5
#elif defined(TEENSYDUINO)
  #define BUTTON_A 4
  #define BUTTON_B 3
  #define BUTTON_C 8
  #define LED 13
#elif defined(ARDUINO_FEATHER52)
  #define BUTTON_A 31
  #define BUTTON_B 30
  #define BUTTON_C 27
  #define LED 17
#else // 32u4, M0, and 328p
  #define BUTTON_A 9
  #define BUTTON_B 6
  #define BUTTON_C 5
  #define LED      13
#endif


/************ Radio Setup ***************/
// Can be changed to 434.0 or other frequency, must match RX's freq!
#define RF69_FREQ 915.0

#if defined (__AVR_ATmega32U4__) // Feather 32u4 w/Radio
  #define RFM69_CS      8
  #define RFM69_INT     7
  #define RFM69_RST     4
#endif

#if defined(ARDUINO_SAMD_FEATHER_M0) // Feather M0 w/Radio
  #define RFM69_CS      8
  #define RFM69_INT     3
  #define RFM69_RST     4
#endif

#if defined (__AVR_ATmega328P__)  // Feather 328P w/wing
  #define RFM69_INT     3  // 
  #define RFM69_CS      4  //
  #define RFM69_RST     2  // "A"
#endif

#if defined(ESP32)    // ESP32 feather w/wing
  #define RFM69_RST     13   // same as LED
  #define RFM69_CS      33   // "B"
  #define RFM69_INT     27   // "A"
#endif


// Singleton instance of the radio driver
RH_RF69 rf69(RFM69_CS, RFM69_INT);
Radio mRadio(rf69);

int lastButton=17; //last button pressed for Trellis logic

TotemMode totemMode = TotemMode(0, 0);
FixedColorMode fixedWhite = FixedColorMode(0xffffff, "White", 0, 1);
FixedColorMode fixedBlue = FixedColorMode(0x0000ff, "Blue", 1, 1);
FixedColorMode fixedPink = FixedColorMode(0xff778f, "Pink", 2, 1);
FixedColorMode fixedRed = FixedColorMode(0xff0000, "Red", 3, 1);

Mode* mModes[16] = {
	&totemMode, 
	0,
	0,
	0,

	&fixedWhite,
	&fixedBlue,
	&fixedPink,
	&fixedRed,

	0,
	0,
	0,
	0,

	0,
	0,
	0,
	0
};
ParticipantManager mParticipantManager(display, mRadio, knob, trellis, mModes[0]);
int lastTB[8] = {16, 16, 16, 16, 16, 16, 16, 16}; //array to store per-menu Trellis button

/*******************SETUP************/
void setup() {
  delay(500);
  Serial.begin(115200);
  //while (!Serial) { delay(1); } // wait until serial console is open, 
  //remove if not tethered to computer


  // INT pin on Trellis requires a pullup
  pinMode(INTPIN, INPUT);
  digitalWrite(INTPIN, HIGH);
  trellis.begin(0x70);  

  pinMode(PIN_ENCODER_SWITCH, INPUT_PULLUP);//set encoder push switch pin to input pullup
  
  digitalPinToInterrupt(10); //on M0, Encoder library doesn't auto set these as interrupts
  digitalPinToInterrupt(12);
  
  // Initialize OLED display
  Serial.begin(9600);
  Serial.println("ISSI manual animation test");
  if (! matrix.begin()) {
    Serial.println("IS31 not found");
    while (1);
  }
  Serial.println("IS31 Found!");
  pinMode(BUTTON_A, INPUT_PULLUP);
  pinMode(BUTTON_B, INPUT_PULLUP);
  pinMode(BUTTON_C, INPUT_PULLUP);
  pinMode(LED, OUTPUT);     
  pinMode(RFM69_RST, OUTPUT);
  digitalWrite(RFM69_RST, LOW);

  // manual reset
  digitalWrite(RFM69_RST, HIGH);
  delay(10);
  digitalWrite(RFM69_RST, LOW);
  delay(10);
  
  if (!rf69.init()) {
    Serial.println("RFM69 radio init failed");
    while (1);
  }
  Serial.println("RFM69 radio init OK!");
  
  // Defaults after init are 434.0MHz, modulation GFSK_Rb250Fd250, +13dbM (for low power module)
  // No encryption
  if (!rf69.setFrequency(RF69_FREQ)) {
    Serial.println("setFrequency failed");
  }

  // If you are using a high power RF69 eg RFM69HW, you *must* set a Tx power with the
  // ishighpowermodule flag set like this:
  rf69.setTxPower(14, true);

  // The encryption key has to be the same as the one in the server
  uint8_t key[] = { 0x33, 0x91, 0x3a, 0e8, 0x25, 0x01, 0x21, 0x08,
                    0x11, 0x29, 0xd0, 0xaa, 0x65, 0x06, 0x07, 0x5c};
  rf69.setEncryptionKey(key);
  
  pinMode(LED, OUTPUT);

  Serial.print("RFM69 radio @");  Serial.print((int)RF69_FREQ);  Serial.println(" MHz");

  //oled.setCursor(0,0);
  //oled.println("RFM69 @ ");
  //oled.print((int)RF69_FREQ);
  //oled.println(" MHz");
  //oled.display();
  //delay(1200); //pause to let freq message be read by a human

  //oled.clearDisplay();
  //oled.setCursor(0,0);
  //oled.println("REMOTE FX");
  //oled.setCursor(0,16);
  //oled.println("TRIGGER");  
  //oled.display();

  // light up all the LEDs in order
  for (uint8_t i=0; i<numKeys; i++) {
    trellis.setLED(i);
    trellis.writeDisplay();    
    delay(30);
  }
  // then turn them off
  for (uint8_t i=0; i<numKeys; i++) {
    trellis.clrLED(i);
    trellis.writeDisplay();    
    delay(30);
  }
}
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////


  
void loop() {
	delay(30); // 30ms delay is required, dont remove me! (Trellis)

	mRadio.onLoop();
	mParticipantManager.onLoop();
	display.draw();

	/*************Trellis Button Presses***********/
	if (trellis.readSwitches()) { // If a button was just pressed or released...
		for (uint8_t i=0; i<numKeys; i++) { // go through every button
			if (trellis.justPressed(i)) { // if it was pressed, turn it on
				//Serial.print("v"); Serial.println(i);
				Mode* pressedMode = mModes[i];
				if (pressedMode != 0) {
					trellis.setLED(i);
					mParticipantManager.onModeSelected(pressedMode);
					trellis.writeDisplay(); // tell the trellis to set the LEDs we requested
				}
				else {
					display.setText(":(");
				}
			} 
		}
	}
}


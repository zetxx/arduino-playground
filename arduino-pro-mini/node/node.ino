#define MY_DEBUG
#define MY_DEBUG_VERBOSE
#define MY_DEBUG_VERBOSE_SIGNING

#define MY_RADIO_RF24
#define MY_RF24_PA_LEVEL RF24_PA_HIGH

#define MY_NODE_ID 105
//#define MY_PARENT_NODE_ID 200

#define MY_SIGNING_SOFT
#define MY_SIGNING_REQUEST_SIGNATURES

#include <MySensors.h>

#define SKETCH_NAME "Binary Sensor"
#define SKETCH_MAJOR_VER "1"
#define SKETCH_MINOR_VER "0"

#define PRIMARY_CHILD_ID 3
#define SECONDARY_CHILD_ID 4

#define PRIMARY_BUTTON_PIN 2   // Arduino Digital I/O pin for button/reed switch
#define SECONDARY_BUTTON_PIN 3 // Arduino Digital I/O pin for button/reed switch

#if (PRIMARY_BUTTON_PIN < 2 || PRIMARY_BUTTON_PIN > 3)
#error PRIMARY_BUTTON_PIN must be either 2 or 3 for interrupts to work
#endif
#if (SECONDARY_BUTTON_PIN < 2 || SECONDARY_BUTTON_PIN > 3)
#error SECONDARY_BUTTON_PIN must be either 2 or 3 for interrupts to work
#endif
#if (PRIMARY_BUTTON_PIN == SECONDARY_BUTTON_PIN)
#error PRIMARY_BUTTON_PIN and BUTTON_PIN2 cannot be the same
#endif
#if (PRIMARY_CHILD_ID == SECONDARY_CHILD_ID)
#error PRIMARY_CHILD_ID and SECONDARY_CHILD_ID cannot be the same
#endif


// Change to V_LIGHT if you use S_LIGHT in presentation below
MyMessage msg(PRIMARY_CHILD_ID, V_TRIPPED);
MyMessage msg2(SECONDARY_CHILD_ID, V_TRIPPED);

bool btnState [2] = {false, false};
int loopCount = 1;

void setup() {
	// Setup the buttons
	pinMode(PRIMARY_BUTTON_PIN, INPUT_PULLUP);
	pinMode(SECONDARY_BUTTON_PIN, INPUT_PULLUP);
}

void presentation() {
	// Send the sketch version information to the gateway and Controller
	sendSketchInfo(SKETCH_NAME, SKETCH_MAJOR_VER "." SKETCH_MINOR_VER);

	// Register binary input sensor to sensor_node (they will be created as child devices)
	// You can use S_DOOR, S_MOTION or S_LIGHT here depending on your usage.
	// If S_LIGHT is used, remember to update variable type you send in. See "msg" above.
	present(PRIMARY_CHILD_ID, S_DOOR);
	present(SECONDARY_CHILD_ID, S_DOOR);
}

bool buttonInfo(int btn) {
  if (btnState[btn] == false) {
    btnState[btn] = true;
  } else {
    btnState[btn] = false;
  }
  return btnState[btn];
}

// Loop will iterate on changes on the BUTTON_PINs
void loop() {
	uint8_t value;
	static uint8_t sentValue=2;
	static uint8_t sentValue2=2;

	// Short delay to allow buttons to properly settle
	sleep(5);

	value = buttonInfo(0);

	if (value != sentValue) {
		// Value has changed from last transmission, send the updated value
		send(msg.set(value==HIGH));
		sentValue = value;
	}

	value = buttonInfo(1);

	if (value != sentValue2) {
		// Value has changed from last transmission, send the updated value
		send(msg2.set(value==HIGH));
		sentValue2 = value;
	}

	// Sleep until something happens with the sensor
	sleep(1000);
  Serial.println(loopCount);
}
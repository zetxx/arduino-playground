#include "Keyboard.h"
#include "InputDebounce.h"
#define BUTTON_DEBOUNCE_DELAY   20   // [ms]
const int up = 16;
const int down = 7;
const int enter = 10;

static InputDebounce debouncingUp;
static InputDebounce debouncingDown;
static InputDebounce debouncingEnter;

void pressed(uint8_t pinIn) {}

void released(uint8_t pinIn) {}

void pressedDuration(uint8_t pinIn, unsigned long duration) {}

void releasedDuration(uint8_t pinIn, unsigned long duration) {
  if(up == pinIn) {
    Keyboard.write(218);
  } else if(down == pinIn) {
    Keyboard.write(217);
  } else if(enter == pinIn) {
    Keyboard.write(176);
  }
}

void setup() {
  pinMode(up, INPUT);
  pinMode(down, INPUT);
  pinMode(enter, INPUT);
  debouncingUp.registerCallbacks(pressed, released, pressedDuration, releasedDuration);
  debouncingDown.registerCallbacks(pressed, released, pressedDuration, releasedDuration);
  debouncingEnter.registerCallbacks(pressed, released, pressedDuration, releasedDuration);

  debouncingUp.setup(up, BUTTON_DEBOUNCE_DELAY, InputDebounce::PIM_EXT_PULL_DOWN_RES);
  debouncingDown.setup(down, BUTTON_DEBOUNCE_DELAY, InputDebounce::PIM_EXT_PULL_DOWN_RES);
  debouncingEnter.setup(enter, BUTTON_DEBOUNCE_DELAY, InputDebounce::PIM_EXT_PULL_DOWN_RES);
  Keyboard.begin();
}

void loop() {
  unsigned long now = millis();
  debouncingUp.process(now);
  debouncingDown.process(now);
  debouncingEnter.process(now);
  delay(1);
}

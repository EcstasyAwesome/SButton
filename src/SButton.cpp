#include "SButton.h"

/*
 * Use this constructor if a button is connected to an analog pin
 * Using min/max values can be useful because sometimes the real button value can be different than value was declared by the user
 *
 * @param pin
 *        pin number that a buttom is connected
 * @param min
 *        button min value that a button is pressed
 * @param max
 *        button max value that a button is pressed
 * @param tm1
 *        long pushing time (ms), if 0 - disable
 * @param tm2
 *        debounce time (ms)
 */

SButton::SButton(const uint8_t pin, const uint16_t min, const uint16_t max, const uint16_t tm1, const uint8_t tm2) {
  _pin = pin;
  _min = min;
  _max = max;
  _long = tm1;
  _debounce = tm2;
  _digital = false;
}

/*
 * Use this constructor if a button is connected to a digital pin
 *
 * @param pin
 *        pin number that a buttom is connected
 * @param state
 *        pin state when the button is pressed (HIGH/true or LOW/false)
 * @param tm1
 *        long pushing time (ms), if 0 - disable
 * @param tm2
 *        debounce time (ms)
 */

SButton::SButton(const uint8_t pin, const bool state, const uint16_t tm1, const uint8_t tm2) {
  _pin = pin;
  _long = tm1;
  _debounce = tm2;
  _digital = true;
  _state = state;
  pinMode(_pin, INPUT);
}

/*
 * Use this constructor if a button is connected to a digital pin, using an inner pull-up resistor
 *
 * @param pin
 *        pin number that a buttom is connected
 * @param tm1
 *        long pushing time (ms), if 0 - disable
 * @param tm2
 *        debounce time (ms)
 */

SButton::SButton(const uint8_t pin, const uint16_t tm1, const uint8_t tm2) {
  _pin = pin;
  _long = tm1;
  _debounce = tm2;
  _digital = true;
  _state = false;
  pinMode(_pin, INPUT_PULLUP);
}

/*
 * The method runs in the main loop()
 * @return BUTTON_NONE, if a button is not pressed
 * @return BUTTON_SHORT only one time at the moment of pushing
 * @return BUTTON_LONG, if a button is pressed longer than tm1
*/

SBUTTON_STATUS SButton::getStatus() {
  bool physicallyPressed;
  if (_digital) physicallyPressed = _state ? digitalRead(_pin) : !digitalRead(_pin);
  else {
  	uint16_t value = analogRead(_pin);
	physicallyPressed = value <= _max && value >= _min;
  }
  if (physicallyPressed) {
    if (!_pressed) {
      if (millis() - _time >= _debounce) {
        _pressed = true;
        _time = millis();
        return SBUTTON_SHORT;
      }
    }
    else if (_long != 0 && (millis() - _time) >= _long) return SBUTTON_LONG;
  }
  else if (_pressed && (millis() - _time) >= _debounce) {
    _pressed = false;
    _time = millis();
  }
  return SBUTTON_NONE;
}
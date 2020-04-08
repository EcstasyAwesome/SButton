#include "SButton.h"

/*
 * @param pin
 *        pin number that a buttom is connected
 * @param value
 *        button value that a button is pressed
 * @param tm1
 *        long pushing time (ms), if 0 - disable (default is 0)
 * @param tm2
 *        debounce time (ms) (default is 100)
 */

SButton::SButton(const uint8_t pin, const uint16_t value, const uint16_t tm1, const uint8_t tm2) {
  _pin = pin;
  _min = (value <= 50) ? 0 : (value - 50);
  _max = (value >= 973) ? 1023 : (value + 50);
  _long = tm1;
  _debounce = tm2;
}

/*
 * The method runs in the main loop()
 * @return BUTTON_NONE, if a button is not pressed
 * @return BUTTON_SHORT only one time at the moment of pushing
 * @return BUTTON_LONG, if a button is pressed longer than tm1
*/

SBUTTON_STATUS SButton::getStatus() {
  uint16_t value = analogRead(_pin);
  if (value < _max && value >= _min) {
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
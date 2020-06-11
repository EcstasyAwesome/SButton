#ifndef SButton_h
#define SButton_h
#include "Arduino.h"

typedef enum {
  SBUTTON_NONE = 0,
  SBUTTON_SHORT,
  SBUTTON_LONG,
} SBUTTON_STATUS;

class SButton {
  private:
    bool _state;
    bool _digital;
    bool _pressed;
    uint8_t _pin;
	uint8_t _debounce;
    uint16_t _min;
    uint16_t _max;
	uint16_t _long;
    uint32_t _time;
  public:
    SButton(const uint8_t pin, const uint16_t min, const uint16_t max, const uint16_t tm1, const uint8_t tm2);
	SButton(const uint8_t pin, const bool state, const uint16_t tm1, const uint8_t tm2);
	SButton(const uint8_t pin, const uint16_t tm1, const uint8_t tm2);
    SBUTTON_STATUS getStatus();
};

#endif
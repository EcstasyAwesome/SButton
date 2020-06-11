#include <SButton.h>

// analog button
SButton button(A0, 0, 10, 1000, 100);

// digital button
//SButton button(2, HIGH, 1000, 100);

// digital button with inner pull-up resistor
//SButton button(2, 1000, 100);

void setup() {
  Serial.begin(9600);
}

void loop() {
  switch (button.getStatus()) {
    case SBUTTON_SHORT: Serial.println("short"); break;
    case SBUTTON_LONG: Serial.println("long"); break;
    //case SBUTTON_NONE: Serial.println("none"); break;
  }
}
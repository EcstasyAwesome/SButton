#include <SButton.h>

SButton button(A0, 0, 1000);

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
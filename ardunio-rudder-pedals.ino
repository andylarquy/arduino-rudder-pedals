#include <Joystick.h>

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_MULTI_AXIS, 0, 0, true, true, false, false, false, false, true, false, false, false, false);

int rightPedalPin = A1;
int leftPedalPin = A0;
int CONSTANT_5V = 4;
int MIDDLE_RUDDER_RANGE = 512;
int DEAD_ZONE_BRAKING_DETECTION = 100;

void setup() {
  // Debug
  Serial.begin(9600);

  // Initialize constant 5V output
  pinMode(CONSTANT_5V, OUTPUT);

  Joystick.begin();
}

void loop() {
  //Output 5V
  digitalWrite(CONSTANT_5V, HIGH);

  int leftPedal = min(analogRead(leftPedalPin) * 2, MIDDLE_RUDDER_RANGE);
  int rightPedal = min(analogRead(rightPedalPin) * 1.55, MIDDLE_RUDDER_RANGE);
  int brakePedal = min(leftPedal, rightPedal) * 2;
  int finalRudderPosition;
  if (leftPedal >= DEAD_ZONE_BRAKING_DETECTION && rightPedal >= DEAD_ZONE_BRAKING_DETECTION) {
    finalRudderPosition = MIDDLE_RUDDER_RANGE;
  } else {
    finalRudderPosition = MIDDLE_RUDDER_RANGE + rightPedal - leftPedal;
  }

  // Debug
  Serial.print("Final rudder position: ");
  Serial.println(finalRudderPosition);

  Joystick.setRudder(finalRudderPosition);
  Joystick.setXAxis(brakePedal);
  Joystick.setYAxis(brakePedal);

  Joystick.sendState();

  // Debug
  Serial.print("Left pedal: ");
  Serial.println(leftPedal);

  Serial.print("Right pedal: ");
  Serial.println(rightPedal);

  Serial.print("Brake pedal: ");
  Serial.println(brakePedal);
}

#include <Joystick.h>

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_MULTI_AXIS, 0, 0, false, false, false, false, false, false, true, false, false, true, false);

int rightPedalPin = A1;
int leftPedalPin = A0;
int CONSTANT_5V = 4;
int MAX_RUDDER_RANGE = 1024;

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

  int leftPedal = min(analogRead(leftPedalPin) * 1.2, MAX_RUDDER_RANGE / 2);
  int rightPedal = min(analogRead(rightPedalPin) * 1.55, MAX_RUDDER_RANGE / 2);
  int brakePedal = min(leftPedal, rightPedal) * 2;

  int neutralRudderPosition = MAX_RUDDER_RANGE / 2;
  int finalRudderPosition = neutralRudderPosition + rightPedal - leftPedal;

// Debug
  Serial.print("Final rudder position: ");
  Serial.println(finalRudderPosition);

  Joystick.setRudder(finalRudderPosition);
  Joystick.setBrake(brakePedal);

  Joystick.sendState();
 
  // Debug
  Serial.print("Left pedal: ");
  Serial.println(leftPedal);
  
  Serial.print("Right pedal: ");
  Serial.println(rightPedal);

  Serial.print("Brake pedal: ");
  Serial.println(brakePedal);
}

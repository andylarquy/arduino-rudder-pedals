int rightPedalPin = A1;
int leftPedalPin = A0;
int CONSTANT_5V = 4;

void setup() {
  pinMode(CONSTANT_5V, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  //Output 5V
  digitalWrite(CONSTANT_5V, HIGH);

  int leftPedal = analogRead(leftPedalPin);
  int rightPedal = analogRead(rightPedalPin);
  int brakePedal = min(leftPedal, rightPedal);
 
  // Debug
  Serial.print("Left pedal: ");
  Serial.println(leftPedal);
  
  Serial.print("Right pedal: ");
  Serial.println(rightPedal);

  Serial.print("Brake pedal: ");
  Serial.println(brakePedal);

  delay(500);
}

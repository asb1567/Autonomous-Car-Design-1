//difine SONIC_TRIG 2
//define SONIC_ECHO 3

void setup() {
  Serial.begin(9600);

  pinMode(2, OUTPUT);
  pinMode(3, INPUT);
}

void loop() {
  digitalWrite(2, HIGH);
  delayMicroseconds(10);
  digitalWrite(2, LOW);

  unsigned long duration = pulseIn(3, HIGH);
  unsigned long distance = duration / 58;
  
  Serial.print(duration);
  Serial.print(",");
  Serial.print(distance);
  Serial.println("cm");

delay(25);
}

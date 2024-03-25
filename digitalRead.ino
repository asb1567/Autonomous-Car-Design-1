#define ledpin 13
#define lnpin  7
int val = 0;

void setup()
{
  pinMode(ledpin, OUTPUT);
  pinMode(lnpin, INPUT);
  Serial.begin(9600);
}

void loop() 
{
  val = digitalRead(lnpin);

  Serial.print("Input data =");
  Serial.println(val);
  digitalWrite(ledpin, val);
}

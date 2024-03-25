#define ledPin 13
int linesensor_data[5] = {0,0,0,0,0};
int linesensor_pin[5]  = {2,3,4,5,6};

void setup()
{
  int i;
  pinMode(ledPin, OUTPUT);

  for( i=0; i<5; i++ )
  {
    pinMode(linesensor_pin[i], INPUT);
  }
 
  Serial.begin(9600);
}

void loop() 
{
  int i;
  for( i=0; i<5; i++ )
  {
    linesensor_data[i] = digitalRead(linesensor_pin[i]);
  }
  
  Serial.print("Input data =");

  for( i=0; i<5; i++ )
  {
    Serial.print(linesensor_data[i]);
    Serial.print("  ");
  }
  
  Serial.println("  ");
}

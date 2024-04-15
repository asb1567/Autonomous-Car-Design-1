#include <NewPing.h>

#define SONAR_NUM 4 
#define MAX_DISTANCE 150
float UltrasonicSensorData[SONAR_NUM];

#define ledPin 13  
#define LINE_DETECT_WHITE  1

NewPing sonar[SONAR_NUM] =
{
  NewPing(8,8,MAX_DISTANCE),
  NewPing(9,9,MAX_DISTANCE),
  NewPing(10,10,MAX_DISTANCE),
  NewPing(11,11,MAX_DISTANCE)
};

void read_ultransonic_sensor(void)
{
  UltrasonicSensorData[0] = sonar[0].ping_cm();
  UltrasonicSensorData[1] = sonar[1].ping_cm();
  UltrasonicSensorData[2] = sonar[2].ping_cm();
  UltrasonicSensorData[3] = sonar[3].ping_cm();
}

void Sonar_data_display(int flag)
{
  char Sonar_data_display[40];
  if(flag==0) return;
  else
  {
    sprintf(Sonar_data_display,"F:");
    Serial.print(Sonar_data_display);
    Serial.print(UltrasonicSensorData[0]);
    Serial.print(" B:");
    Serial.print(UltrasonicSensorData[1]);
    Serial.print(" R:");
    Serial.print(UltrasonicSensorData[2]);
    Serial.print(" L:");
    Serial.println(UltrasonicSensorData[3]);
  }
}

int Robot_Mode_Define(void)
{
  int i;
  int mode = -1;
  read_ultransonic_sensor();
  Sonar_data_display(1);
  for(i=0;i<4;i++)
  {
    if(UltrasonicSensorData[i] ==0) UltrasonicSensorData[i] = MAX_DISTANCE;
  }
  Sonar_data_display(1);
  if( (UltrasonicSensorData[2] >= 15) && (UltrasonicSensorData[3] >= 15) )
  {
    mode =0;
  }
  Sonar_data_display(1);
  if( (UltrasonicSensorData[2] <= 15) && (UltrasonicSensorData[3] <= 15) )
  {
    mode =1;
  }
  Sonar_data_display(1);
  if( (UltrasonicSensorData[3] <= 35) && (UltrasonicSensorData[2] >= 40) )
  {
    mode =2;
  }
  Sonar_data_display(1);
  if( (UltrasonicSensorData[2] <= 35) && (UltrasonicSensorData[3] >= 40) )
  {
    mode =3;
  }
}

int linesensor_data[5] = {0,0,0,0,0};  
int linesensor_pin[5] = {2,3,4,5,6};   

int read_digital_line_sensor(void)
{
  int i;
  int sum = 0;
  for(i=0;i<5;i++)
  {
    if(LINE_DETECT_WHITE == 0)
    {
      linesensor_data[i] = 1 - digitalRead(linesensor_pin[i]);
    }
    else
    {
      linesensor_data[i] = digitalRead(linesensor_pin[i]);
    }
    sum += linesensor_data[i];
  }
   
  if(sum == 5)
  {
    return sum;
  }
  else if(sum == 2)
  {
    if( (linesensor_data[3] == 1) && (linesensor_data[4] == 1) ) return 3;
    if( (linesensor_data[2] == 1) && (linesensor_data[3] == 1) ) return 1;
    if( (linesensor_data[1] == 1) && (linesensor_data[2] == 1) ) return -1;
    if( (linesensor_data[0] == 1) && (linesensor_data[1] == 1) ) return -3;
  }
  else if(sum == 1)
  {
    if((linesensor_data[0] == 1)) return -4;
    if((linesensor_data[1] == 1)) return -2;
    if((linesensor_data[2] == 1)) return 0;
    if((linesensor_data[3] == 1)) return 2;
    if((linesensor_data[4] == 1)) return 4;
  }
  else if(sum == 3)
  {
    return -10;
  }
  else
  {
    return -5;
  }
}

void setup() {
  int i;
  pinMode(ledPin, OUTPUT);    

  for(i=0;i<5;i++)
  {
      pinMode(linesensor_pin[i], INPUT);      
  }
  
  Serial.begin(9600);
}

void loop() {
  int i;
  int sum = 0;
  sum = read_digital_line_sensor();  

  Serial.print("Input data = ");
  for(i=0;i<5;i++)
  {
    Serial.print(linesensor_data[i]);
    Serial.print(" ");
  }
  Serial.print(sum);  
  Serial.println(" ");  

  delay(50);
  
  int mode = Robot_Mode_Define();
  Serial.print(mode);
}

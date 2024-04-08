#define LINE_DETECT_WHITE 1
#define ledPin 13

#define SONAR_NUM 4
#define MAX_DISTANCE 150 

#include <NewPing.h>

int mode = -1;

float ultrasonicsensor_data[SONAR_NUM];

NewPing sonar[SONAR_NUM] = 
{
  NewPing(8, 8, MAX_DISTANCE),
  NewPing(9, 9, MAX_DISTANCE),
  NewPing(10, 10, MAX_DISTANCE),
  NewPing(11, 11, MAX_DISTANCE),
};
void read_ultrasonic_sensor(void)
{
  ultrasonicsensor_data[0] = sonar[0].ping_cm();
  ultrasonicsensor_data[1] = sonar[1].ping_cm();
  ultrasonicsensor_data[2] = sonar[2].ping_cm();
  ultrasonicsensor_data[3] = sonar[3].ping_cm();
}

void Sonar_Data_Display(int flag)
{
  char Sonar_data_display[40];
  if(flag == 0) return;
  else
  {
    sprintf(Sonar_data_display, "F: ");
    Serial.print(Sonar_data_display);
    Serial.print(ultrasonicsensor_data[0]);
    Serial.print(" B: ");
    Serial.print(ultrasonicsensor_data[1]);
    Serial.print(" R: ");
    Serial.print(ultrasonicsensor_data[2]);
    Serial.print(" L: ");
    Serial.print(ultrasonicsensor_data[3]);
  }
}

void Robot_Mode_Define(void)
{
  int i;
  mode = -1;
  read_ultrasonic_sensor();
  for(i=0;i<4;i++)
  {
    if(ultrasonicsensor_data[i] ==0) ultrasonicsensor_data[i] = MAX_DISTANCE;
  }
  Sonar_Data_Display(1);

  if( (ultrasonicsensor_data[2] >= 15) && (ultrasonicsensor_data[3] >= 15) )
  {
    mode = 0;
  }
  if( (ultrasonicsensor_data[2] <= 15) && (ultrasonicsensor_data[3] <= 15) )
  {
    mode = 1;
  }
  if( (ultrasonicsensor_data[3] <= 35) && (ultrasonicsensor_data[2] >= 40) )
  {
    mode = 2;
  }
  if( (ultrasonicsensor_data[2] <= 35) && (ultrasonicsensor_data[3] >= 40) )
  {
    mode = 3;
  }
}

int linesensor_data[5] = {0, 0, 0, 0, 0};
int linesensor_pin[5] = {2, 3, 4, 5, 6};

int read_digital_line_sensor(void){
  
  int i;
  int sum = 0;
  
  for(i=0;i<5;i++){
    if(LINE_DETECT_WHITE == 0){
      linesensor_data[i] = 1 - digitalRead(linesensor_pin[i]);
      }
      else{
        linesensor_data[i] = digitalRead(linesensor_pin[i]);
      }
      sum += linesensor_data[i];
    }
    return sum;
  }



void setup() {
  
  int i;
  
  pinMode(ledPin, OUTPUT);
  
  for(i=0;i<5;i++){
      pinMode(linesensor_pin[i], INPUT);
    }
  Serial.begin(9600);
}

void loop() {

  delay(50);                  
  
  int i;
  int sum;

  sum = read_digital_line_sensor();

  Serial.print("Input data =");
  
  Robot_Mode_Define();
  Serial.println(mode);
  
  for(i=0;i<5;i++){
      Serial.print(linesensor_data[i]);
      Serial.print("  ");
    }
    Serial.println(sum);
    Serial.println("  ");
    Serial.print("Ping: ");
    Serial.print(ultrasonicsensor_data[i]);
    Serial.println("cm");
}

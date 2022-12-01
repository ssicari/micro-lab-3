//code modified from Elegoo website
#include <Wire.h>
#include <DS3231.h>
#include <LiquidCrystal.h>

DS3231 clock;
RTCDateTime dt;
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

#define ENABLE 5
#define DIR1 3
#define DIR2 4
uint8_t fan_speeds[] = {255, 180, 128, 50, 0};

bool motor_dir1 = HIGH
bool motor_dir2 = LOW

attachInterrupt(digitalPinToInterrupt(2), buttonISR, RISING)

void setup() 
{
  pinMode(ENABLE, OUTPUT);
  pinMode(DIR1, OUTPUT);
  pinMode(DIR2, OUTPUT);
  serial.begin(9600);
  //lcd.begin(9600);

  clock.begin();
  clock.setDateTime(__DATE__, __TIME__);

  lcd.begin(16, 2);
}

void motorcontrol(byte speed, bool D1, bool D2)
{
  analogWrite(ENABLE, speed);
  digitalWrite(DIR1, D1); //start fan spinning in one direction
  digitalWrite(DIR2, D2);
}

void loop() 
{
  lcd.setCursor(0, 1);
  dt = clock.getDateTime();

  while(1) //infinite loop to keep fan running
  {
    for(int i = 0; i < 5; i++) //iterate through all 5 speeds (full, 3/4, 1/2. 1/4, off)
    {
      //digitalWrite(ENABLE, HIGH);

      lcd.print(dt.year);   lcd.print("-");
      lcd.print(dt.month);  lcd.print("-");
      lcd.print(dt.day);    lcd.print(" ");
      lcd.print(dt.hour);   lcd.print(":");
      lcd.print(dt.minute); lcd.print(":");
      lcd.print(dt.second); lcd.println("");

      motor_control(fan_speeds[i], motor_dir1, motor_dir2)
      //analogWrite(ENABLE, fan_speeds[i]);
      //digitalWrite(DIR1, HIGH); //start fan spinning in one direction
      //digitalWrite(DIR2, LOW);
      
      /*if(//button is pressed)
        {
          digitalWrite(DIR1, LOW); //change fan direction
          digitalWrite(DIR2, HIGH);
        }
      delay(1000);*/
    }

  }

void buttonISR() {
  motor_dir1 = !motor_dir1
  motor_dir2 = !motor_dir2
}

}

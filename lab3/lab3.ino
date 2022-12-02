//code modified from Elegoo website
#include <Wire.h>
#include "RTClib.h"
#include <LiquidCrystal.h>

#define ENABLE 3
#define DIR1 22
#define DIR2 23
#define BUTTON 2

RTC_DS1307 rtc;
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

uint8_t fan_speeds[] = {255, 180, 128, 50, 0};
int speed_index = 0;

bool motor_dir1 = HIGH;
bool motor_dir2 = LOW;

double debounce = 0;
static double debounce_time = 10;
bool buttonpress = LOW;

void setup() 
{
  pinMode(ENABLE, OUTPUT);
  pinMode(DIR1, OUTPUT);
  pinMode(DIR2, OUTPUT);
  Wire.begin();
  rtc.begin();


  //clock.begin();
  //clock.setDateTime(__DATE__, __TIME__);

  lcd.begin(16, 2);

  attachInterrupt(digitalPinToInterrupt(BUTTON), buttonISR, CHANGE);
  cli();//stop interrupts

  //set timer1 interrupt at 1Hz
  TCCR1A = 0; // set entire TCCR1A register to 0
  TCCR1B = 0; // same for TCCR1B
  TCNT1  = 0; //initialize counter value to 0

  // set compare match register for 1hz increments
  OCR1A = 15624;// = (16*10^6) / (1*1024) - 1 (must be <65536)

  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS12 and CS10 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);  
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);

  sei(); //allow interrupts
}

void motor_control(byte speed, bool D1, bool D2)
{
  analogWrite(ENABLE, speed);
  digitalWrite(DIR1, D1); //start fan spinning in one direction
  digitalWrite(DIR2, D2);
}

void loop() 
{
  motor_control(fan_speeds[speed_index], motor_dir1, motor_dir2);

}

void buttonISR() {
  if(buttonpress == LOW){
    buttonpress = HIGH;
    debounce = millis();
  }
  else if (buttonpress == HIGH){
    if (millis()-debounce>debounce_time){
      motor_dir1 = !motor_dir1;
      motor_dir2 = !motor_dir2;
    }
    buttonpress = LOW;

  }

}

ISR(TIMER1_COMPA_vect){//timer1 interrupt 1Hz toggles pin 13 (LED)
  lcd.clear();
  lcd.noAutoscroll();
  lcd.setCursor(0, 0);
  DateTime time = rtc.now();

  lcd.setCursor(0, 1);
  if(motor_dir1)
  {
    lcd.print("D: CCW S:" + speed_index);
  }
  else
  {
    lcd.print("D: CW  S:" + speed_index);
  }

  lcd.setCursor(0, 0);
  lcd.print(time.hour()); lcd.print(":");
  lcd.print(time.minute()); lcd.print(":");
  lcd.print(time.second()); lcd.print(":");
    
  speed_index = (speed_index + 1)%5;
}

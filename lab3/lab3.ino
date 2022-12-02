//code modified from Elegoo website
#include <Wire.h>
#include <DS3231.h>
#include <LiquidCrystal.h>

DS3231 clock;
RTCDateTime dt;
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

#define ENABLE 3
#define DIR1 22
#define DIR2 23
#define BUTTON 2
uint8_t fan_speeds[] = {255, 180, 128, 50, 0};
int speed_index = 0;

bool motor_dir1 = HIGH;
bool motor_dir2 = LOW;

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

  attachInterrupt(digitalPinToInterrupt(BUTTON), buttonISR, RISING)
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

void motorcontrol(byte speed, bool D1, bool D2)
{
  analogWrite(ENABLE, speed);
  digitalWrite(DIR1, D1); //start fan spinning in one direction
  digitalWrite(DIR2, D2);
}

void loop() 
{

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
void ISR(TIMER1_COMPA_vect){//timer1 interrupt 1Hz toggles pin 13 (LED)
  lcd.setCursor(0, 1);
  dt = clock.getDateTime();
  lcd.print(dt.year);   lcd.print("-");
  lcd.print(dt.month);  lcd.print("-");
  lcd.print(dt.day);    lcd.print(" ");
  lcd.print(dt.hour);   lcd.print(":");
  lcd.print(dt.minute); lcd.print(":");
  lcd.print(dt.second); lcd.println("");
  speed_index = (speed_index + 1)%5
}
}
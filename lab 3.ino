//code modified from Elegoo website
#define ENABLE 5
#define DIR1 3
#define DIR2 4
uint8_t fan_speeds[] = {255, 180, 128, 50, 0};

void setup() 
{
  pinMode(ENABLE, OUTPUT);
  pinMode(DIR1, OUTPUT);
  pinMode(DIR2, OUTPUT);
  Serial.begin(9600);
}

void loop() 
{
  while(1) //infinite loop to keep fan running
  {
    for(int i = 0; i < 5; i++) //iterate through all 5 speeds (full, 3/4, 1/2. 1/4, off)
    {
      //digitalWrite(ENABLE, HIGH);
      analogWrite(ENABLE, fan_speeds[i]);
      digitalWrite(DIR1, HIGH); //start fan spinning in one direction
      digitalWrite(DIR2, LOW);
      if(//button is pressed)
        {
          digitalWrite(DIR1, LOW); //change fan direction
          digitalWrite(DIR2, HIGH);
        }
      delay(2000);
    }

  }

}

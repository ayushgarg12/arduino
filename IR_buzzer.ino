// To control LED using IR sensor
int buzzer = 12;                                    // Use the onboard buzzer GPIO 12 (D6)
int IR_Pin = 13;                                    // Connect IR pin to GPIO 13 (D7)
int val = LOW;                                      // LOW MEANS NO OBSTACLE

void setup()
{
  pinMode(buzzer, OUTPUT);
  pinMode(IR_Pin, INPUT);
  Serial.begin(9600);  
}
void loop()
{
  val = digitalRead(IR_Pin);                        //Read the input of IR
  if (val == HIGH)                              
  {
    Serial.println("Stop, something is ahead!!");
    digitalWrite(buzzer,HIGH);                      //beeps the buzzer
  }
  else
  {
    Serial.println("Path is clear");
    digitalWrite(buzzer, LOW);
  }
  delay(200);
}

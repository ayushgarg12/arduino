#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
#define SS_PIN 2                                                            //connect SDA pin to GPIO 2(D4)
#define RST_PIN 0                                                           //connect RST pin to GPIO 0(D3)
#define SERVO_PIN 16                                                        //connect servo data pin to GPIO 16(D0)
Servo myservo;

#define ACCESS_DELAY 1000
#define DENIED_DELAY 1000
MFRC522 mfrc522(SS_PIN, RST_PIN);                                           // Create MFRC522 instance.
 
void setup() 
{
  Serial.begin(9600);                                                       // Initiate a serial communication
  SPI.begin();                                                              // Initiate  SPI bus
  mfrc522.PCD_Init();                                                       // Initiate MFRC522

  myservo.attach(SERVO_PIN);
  myservo.write( 180 );
  delay(1000);
  myservo.write( 0 );
  Serial.println("Put your card to the reader...");
  Serial.println();
}
void loop() 
{
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent())  
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "85 E1 CD 65")                                //change here the UID of the card
  {
    Serial.println("Authorized access");
    Serial.println();
    myservo.write( 180 );
    delay(112000);
    myservo.write( 0 );
  }
 
 else   {
    Serial.println(" Access denied");
 

    delay(DENIED_DELAY);

 
  }
}

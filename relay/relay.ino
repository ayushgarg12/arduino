
int IR = 13;                                //connect IR at GPIO 13 (D7)
int RELAY1 = 5;                            //connect Relay1 at GPIO 5 (D1)
int RELAY2 = 4;                            //connect Relay2 at GPIO 4 (D2)
int val=LOW ;
void setup(){
  pinMode(IR, INPUT);
  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2,OUTPUT);
  Serial.begin(9600);          //initialize serial communications at 9600 bps
}
void loop(){
   Serial.println(val);           // print the value
   val = digitalRead(IR);
   if(val == HIGH){
    digitalWrite(RELAY1, HIGH);
    digitalWrite(RELAY2, HIGH);
   }else{
    digitalWrite(RELAY1, LOW);
    digitalWrite(RELAY2, LOW);  }}

#include <ESP8266WiFi.h>
const char* ssid = "realme 3";
const char* password = "chamanbadshah";
const int outputL1 = 5;
const int outputL2 = 4;
const int outputR1 = 0;
const int outputR2 = 2;
WiFiServer server(80);
void setup()
{
 Serial.begin(115200);
 delay(10);
 pinMode(outputL1, OUTPUT); //Pin 5(D1) & 4(D2) are for Left Motor
 pinMode(outputL2, OUTPUT);
 pinMode(outputR1, OUTPUT); //Pin 0(D3) & 2(D4) are for Right Motor
 pinMode(outputR2, OUTPUT);
 Serial.print("\n \n Connecting to ");
 Serial.println(ssid);
 WiFi.begin(ssid, password);
 while (WiFi.status() != WL_CONNECTED)
 {
 delay(500);
 Serial.print(".");
 }
 Serial.println("\n WiFi connected");
 server.begin();
 Serial.println("Server started");

 Serial.println(WiFi.localIP());
}
void loop()
{
 WiFiClient client = server.available();
 if (!client)
 return;
 Serial.println("new client");
 while(!client.available())
 delay(1);
 String req = client.readStringUntil('\r');
 Serial.println(req);
 client.flush();
 int val;
 if (req.indexOf("/bot/L") != -1)
 val = 0;
 else if (req.indexOf("/bot/F") != -1)
 val = 1;
 else if (req.indexOf("/bot/R") != -1)
 val = 2;
 else if (req.indexOf("/bot/S") != -1)
 val = 3;
 else if (req.indexOf("/bot/B") != -1)
 val = 4;
 else {
 Serial.println("invalid request");
 client.stop();
 return;
 }
 if(val == 0) {
 motor(HIGH, LOW, LOW, HIGH, "LEFT");
 } else if(val == 1) {
 motor(HIGH, LOW, HIGH, LOW, "FORWARD");
 } else if(val == 2){
 motor(LOW, HIGH, HIGH, LOW, "RIGHT");
 } else if(val == 3) {
 motor(LOW, LOW, LOW, LOW, "STOP");
 } else if(val == 4) {
 motor(LOW, HIGH, LOW, HIGH, "BACKWARD");

 }
 client.flush();
 client.println("HTTP/1.1 200 OK");
 client.println("Content-Type: text/html");
 client.println("");
 client.print("BOT is ");
 if(val == 0)
 client.print("turning LEFT");
 else if(val == 1)
 client.print("moving FORWARD");
 else if(val == 2)
 client.print("turning RIGHT");
 else if(val == 3)
 client.print("STOPPED");
 else if(val == 4)
 client.print("BACKWARD");
 Serial.println("Client disconnected");
}
void motor(int ol1, int ol2, int or1, int or2, String msg) {
 digitalWrite(outputL1, ol1);
 digitalWrite(outputL2, ol2);
 digitalWrite(outputR1, or1);
 digitalWrite(outputR2, or2);
 Serial.println(msg);
}

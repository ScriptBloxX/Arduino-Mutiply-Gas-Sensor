#include <TridentTD_LineNotify.h>
#include <SoftwareSerial.h>

const char* SSID = "Unknow User";
#define PASSWORD    "ScriptBlox4287"                                
#define LINE_TOKEN  "4SG4wRjsMGWjE7JcYg0Gplz6YmLuo86lxXbwykqKpg9"

SoftwareSerial mySerial(D7, D8); // RX, TX pins for serial communication with the Arduino UNO

void setup() {
  Serial.begin(115200); Serial.println();
  mySerial.begin(9600);
  Serial.println(LINE.getVersion());

  pinMode(D7, INPUT);
  pinMode(D8, OUTPUT);

  WiFi.begin(SSID, PASSWORD);
  Serial.printf("WiFi connecting to %s\n",  SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(400);
  }
  Serial.printf("\nWiFi connected\nIP : ");
  Serial.println(WiFi.localIP());

  LINE.setToken(LINE_TOKEN);

  LINE.notify("ESP8266: Connected!");
}

void loop() {
   if (mySerial.available() > 1){
    int SmokeRoom = mySerial.parseInt();
    String AlarmMessage = "Room " + String(SmokeRoom) + " Detects Smoke";
    LINE.notify(AlarmMessage);
  }
  delay(200);
}

#include <SoftwareSerial.h>
SoftwareSerial esp8266Serial(8, 7); // RX | TX

const int SMOKE_DETECTOR_PINS[] = {2,3};
const int NUM_OF_SMOKE_DETECTOR_PINS = sizeof(SMOKE_DETECTOR_PINS) / sizeof(SMOKE_DETECTOR_PINS[0]);
bool SmokeFound = false;
int SmokeRoom = 0;
const int BUZZER_PIN = 9;
const int RELAY_PIN = 13;

void setup() {
  // set up all pins
  for (int i = 0; i < NUM_OF_SMOKE_DETECTOR_PINS; i++) {
    pinMode(SMOKE_DETECTOR_PINS[i], INPUT);
  }
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(8,INPUT);
  pinMode(7,OUTPUT);
  esp8266Serial.begin(9600);
  Serial.begin(9600);
}

void loop() {
  // loop for check all sensor
  if(!SmokeFound){
    for (int i = 0; i < NUM_OF_SMOKE_DETECTOR_PINS; i++) {
      int SmokeVal = digitalRead(SMOKE_DETECTOR_PINS[i]);
      if(SmokeVal == 0){
        SmokeFound = true;
        SmokeRoom = i+1;
          Serial.print("smoke_detector: ");
          Serial.print(i);
          Serial.println(" -> True!");
        }else{
          Serial.println("no smoke");
      }
      //Serial.println("IN TEST ** : " + String(SmokeVal));
    } 
  }

  // alarm when detect smoke
  if(SmokeFound){
      tone(BUZZER_PIN, 440, 5000);
      analogWrite(BUZZER_PIN, 255);
      digitalWrite(RELAY_PIN, 1);
      delay(5000);
      esp8266Serial.print(SmokeRoom);
      SmokeFound = false;
  }else {
      analogWrite(BUZZER_PIN, 0);
      digitalWrite(RELAY_PIN, 0);
  }
  delay(1000);
}

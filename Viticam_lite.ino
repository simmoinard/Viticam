#include "LowPower.h"
#include <Servo.h>
#include <Wire.h> //https://www.arduino.cc/en/reference/wire

//Variables
unsigned long timeprevious = millis();
int transistor_rasp = 8 ;
int servo_control = 9;

//Objects
Servo myservo;

void setup() {
  //Serial.begin(9600);
  pinMode(transistor_rasp, OUTPUT);
  pinMode(servo_control, OUTPUT);
}

void loop() {
  delay(1000);
  blk(3);
  //Serial.println("hey");
  //********* Turn on Servo & Raspberry *********
  digitalWrite(transistor_rasp, HIGH);   
  delay(1500);
  servo(80);
  delay(500);

  //********* Wait 2 min *********
  for (int k = 1; k <= 12; k++) { 
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  blk(12-k+1);
  }
  delay(1000);
  blk(2);
  //********* Turn off Servo *********
  servo(0);
  delay(100);
  digitalWrite(servo_control, LOW);   
  delay(100);
  digitalWrite(transistor_rasp, LOW);   
  delay(100);
  blk(3);
  //********* sleepMode *********
  //Serial.println("bye");

  delay(1000);
  for (int j = 1; j <= 8; j++){
    for (int i = 1; i <= 8*56; i++) { 
      LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
    }
    delay(1000);
    blk(1);
  }
  //Serial.println("Wake up");
}

void blk(int j) {
  for (int i = 1; i <= j; i++) { 
    digitalWrite(13,HIGH);
    delay(25);
    digitalWrite(13,LOW);
    delay(100);
  }
}

void servo(int i) {
  myservo.attach(servo_control);  
  delay(1000);
  myservo.write(i);              
  delay(1500); 
  myservo.detach();  
  delay(200);
}

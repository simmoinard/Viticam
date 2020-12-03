#include "LowPower.h"
#include <Servo.h>
#include <Wire.h> //https://www.arduino.cc/en/reference/wire

//Variables
unsigned long timeprevious = millis();
int transistor_rasp = 8 ;
int rasp_state = 11; // Pin 23 of Rasp
int rasp_shutdown_command = 12; //Pin 22 of Rasp

//Objects
Servo myservo;

void setup() {
  Serial.begin(9600);

  pinMode(transistor_rasp, OUTPUT);
  pinMode(rasp_state,INPUT);
  pinMode(rasp_shutdown_command,OUTPUT);

}

void loop() {

  delay(2000);
  Serial.println("Hello");

  //********* Turn on Servo & Raspberry *********
  digitalWrite(transistor_rasp, HIGH);   
  delay(1000);
  myservo.attach(9);  
  delay(1000);
  myservo.write(80);              
  delay(2000); 
  myservo.detach();  
  delay(200);
  
  //********* Wait for raspberry response or 4 min *********
  timeprevious = millis();  
  while (digitalRead(rasp_state)==0 && (millis() - timeprevious) < 240000){
    delay(500);
  }
  if ((millis() - timeprevious) > 240000) {Serial.println("times'up.");}
  
  digitalWrite(rasp_shutdown_command,HIGH);
  delay(2500);
  digitalWrite(rasp_shutdown_command,LOW);
  //********* Turn off Servo & Raspberry *********
  myservo.attach(9);  
  delay(1000);
  myservo.write(0);              
  delay(1000); 
  myservo.detach();
  Serial.println("waiting 15sec for raspberry shutdown...");  
  delay(15000);
  digitalWrite(transistor_rasp, LOW);
  delay(1000); 

  //********* sleepMode *********
  Serial.println("Goodnight");
  delay(1000);
  for (int i = 0; i <= 400*8; i++) { 
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  }
  delay(1000);
  Serial.println("Wake up");
}

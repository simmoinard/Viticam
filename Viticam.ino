#include "LowPower.h"
#include <Servo.h>
#include <Wire.h> //https://www.arduino.cc/en/reference/wire
#include <ds3231.h> //https://github.com/NorthernWidget/DS3231

//Variables
struct ts t;
int hour;
unsigned long timeprevious = millis();
int transistor_rasp = 8 ;
int transistor_RTC = 10;
int rasp_state = 11; // Pin 23 of Rasp
int rasp_shutdown_command = 12; //Pin 22 of Rasp

//Objects
Servo myservo;

void setup() {
  Serial.begin(9600);

  pinMode(transistor_rasp, OUTPUT);
  pinMode(transistor_RTC, OUTPUT);
  pinMode(rasp_state,INPUT);
  pinMode(rasp_shutdown_command,OUTPUT);
  
  digitalWrite(transistor_RTC,HIGH);
  delay(1000);
  Wire.begin();
  DS3231_init(DS3231_CONTROL_INTCN);

/*
  //Update time
  int firstLoop = 1;
  if (firstLoop == 1) {
  digitalWrite(transistor_RTC, HIGH);
  delay(1000);
  DS3231_init(DS3231_CONTROL_INTCN);  
    
  t.hour=19; 
  t.min=25;
  t.sec=0;
  t.mday=26;
  t.mon=8;
  t.year=2020;

  DS3231_set(t); // mise à l'heure de l'horloge
  firstLoop = 0;
  Serial.println("Time updated");
  }*/
}

void loop() {

  //********* Turn on RTC *********
  delay(2000);
  Serial.println("Hello");
  Serial.println("Turn on RTC");

  digitalWrite(transistor_RTC, HIGH);
  delay(2000);
  DS3231_get(&t);
  hour = t.hour;
  Serial.print("date : "); Serial.print(t.mday); Serial.print("/"); Serial.print(t.mon); Serial.print("/"); Serial.print(t.year);
  Serial.print("\t Heure : "); Serial.print(t.hour); Serial.print(":"); Serial.print(t.min); Serial.print("."); Serial.println(t.sec);
  Serial.print("heure : "); Serial.println(hour);
  delay(500);
  digitalWrite(transistor_RTC, LOW);

  if (hour > 8 && hour < 20){
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
      //Serial.println(analogRead(rasp_state));
      delay(500);
    }
    if ((millis() - timeprevious) > 180000) {Serial.println("times'up.");}
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
  }

  //********* sleepMode *********
  Serial.println("Goodnight");
  delay(1000);
  for (int i = 0; i <= 373*4; i++) { 
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  }
  delay(1000);
  Serial.println("Wake up");
}

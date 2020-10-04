#include <Arduino.h>
#include "ultrasonic.hpp"

UltraSonicModule::UltraSonicModule(int trigPin, int echoPin)
{
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  this->trigPin = trigPin;
  this->echoPin = echoPin;
}

float UltraSonicModule::getDistance ()
{
  // defines variables
  long duration;
  float distance;

  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

  // Calculating the distance
  distance = duration*0.034/2;

  //Return the distance
  return distance;
}

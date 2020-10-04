#include <Arduino.h>
#include "L298N_Module.hpp"
#include "ultrasonic.hpp"

#define enA 10
#define in1 9
#define in2 8
#define in3 6
#define in4 7
#define enB 5

#define echoPin 4
#define trigPin 3

MotorDriver motorDriver(enA, in1, in2, in3, in4, enB);
UltraSonicModule ultrassom(trigPin, echoPin);

void setup() {
  motorDriver.ChangeSpeed(100);
  delay(3000);
}

void loop() {
  float now_distance = ultrassom.getDistance();
  if (now_distance > 10)
  {
    motorDriver.GoForward();
  }
  else
  {
    motorDriver.GoBackward();
    delay(500);
    motorDriver.TurnLeft();
  }
}

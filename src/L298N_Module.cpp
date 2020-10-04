#include <Arduino.h>
#include "L298N_Module.hpp"
#include <string.h>

#define TIME_TO_90_TURN 800

Motor::Motor(){}

void Motor::SetPins(int enablePin, int input1Pin, int input2Pin)
{
  this->enablePin = enablePin;
  this->input1Pin = input1Pin;
  this->input2Pin = input2Pin;
}

void Motor::SetDirection(int direction)
{
  this->direction = direction;
}

void Motor::SetSpeed(float speed)
{
  this->speed = speed;
}

void Motor::UpdateState()
{
  switch (direction)
  {
    case -1:
      digitalWrite(input1Pin, HIGH);
      digitalWrite(input2Pin, LOW);
      break;
    case 0:
      digitalWrite(input1Pin, LOW);
      digitalWrite(input2Pin, LOW);
      break;
    case 1:
      digitalWrite(input1Pin, LOW);
      digitalWrite(input2Pin, HIGH);
      break;
    case 2:
      digitalWrite(input1Pin, HIGH);
      digitalWrite(input2Pin, HIGH);
      break;
  }

  analogWrite(enablePin, speed);
}



MotorDriver::MotorDriver(int enA, int in1, int in2, int in3, int in4, int enB)
{
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  this->leftMotor.SetPins(enA, in1, in2);

  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  this->rightMotor.SetPins(enB, in3, in4);
}

void MotorDriver::SetMotorDirection(String actuator, String direction)
{
  int desiredDirection;
  if (direction == "backward")
    desiredDirection = -1;
  if (direction == "neutral")
    desiredDirection = 0;
  if (direction == "forward")
    desiredDirection = 1;
  if (direction == "stall")
    desiredDirection = 2;

  if (actuator == "leftMotor")
    this->leftMotor.SetDirection(desiredDirection);
  if (actuator == "rightMotor")
    this->rightMotor.SetDirection(desiredDirection);
}

void MotorDriver::SetMotorSpeed(String actuator, float speedInPercent)
{
  int pwmSpeed = int(map(speedInPercent, 0, 100, 0 , 255));

  if (actuator == "leftMotor")
    this->leftMotor.SetSpeed(pwmSpeed);
  if (actuator == "rightMotor")
    this->rightMotor.SetSpeed(pwmSpeed);
}

void MotorDriver::GoForward()
{
  SetMotorDirection("leftMotor", "forward");
  SetMotorDirection("rightMotor", "forward");
  this->leftMotor.UpdateState();
  this->rightMotor.UpdateState();
}

void MotorDriver::GoForwardWithSpeed(float speed)
{
  SetMotorDirection("leftMotor", "forward");
  SetMotorSpeed("leftMotor", speed);
  SetMotorDirection("rightMotor", "forward");
  SetMotorSpeed("rightMotor", speed);
  this->leftMotor.UpdateState();
  this->rightMotor.UpdateState();
  this->currentSpeed = speed;
}

void MotorDriver::GoBackward()
{
  SetMotorDirection("leftMotor", "backward");
  SetMotorDirection("rightMotor", "backward");
  this->leftMotor.UpdateState();
  this->rightMotor.UpdateState();
}

void MotorDriver::GoBackwardWithSpeed(float speed)
{
  SetMotorDirection("leftMotor", "backward");
  SetMotorSpeed("leftMotor", speed);
  SetMotorDirection("rightMotor", "backward");
  SetMotorSpeed("rightMotor", speed);
  this->leftMotor.UpdateState();
  this->rightMotor.UpdateState();
  this->currentSpeed = speed;
}

void MotorDriver::NeutralStop()
{
  SetMotorDirection("leftMotor", "neutral");
  SetMotorDirection("rightMotor", "neutral");
  this->leftMotor.UpdateState();
  this->rightMotor.UpdateState();
}

void MotorDriver::HardStop()
{
  SetMotorDirection("leftMotor", "stall");
  SetMotorDirection("rightMotor", "stall");
  this->leftMotor.UpdateState();
  this->rightMotor.UpdateState();
}

void MotorDriver::TurnLeft()
{
  SetMotorDirection("leftMotor", "forward");
  SetMotorDirection("rightMotor", "backward");
  this->leftMotor.UpdateState();
  this->rightMotor.UpdateState();
  float speedRatio = 100/this->currentSpeed;
  delay(TIME_TO_90_TURN* speedRatio);
  NeutralStop();
}

void MotorDriver::TurnLeftWithSpeed(float speed)
{
  SetMotorDirection("leftMotor", "forward");
  SetMotorSpeed("leftMotor", speed);
  SetMotorDirection("rightMotor", "backward");
  SetMotorSpeed("rightMotor", speed);
  this->leftMotor.UpdateState();
  this->rightMotor.UpdateState();
  this->currentSpeed = speed;
  float speedRatio = 100/this->currentSpeed;
  delay(TIME_TO_90_TURN* speedRatio);
  NeutralStop();
}

void MotorDriver::TurnRight()
{
  SetMotorDirection("leftMotor", "backward");
  SetMotorDirection("rightMotor", "forward");
  this->leftMotor.UpdateState();
  this->rightMotor.UpdateState();
  float speedRatio = 100/this->currentSpeed;
  delay(TIME_TO_90_TURN* speedRatio);
  NeutralStop();
}

void MotorDriver::TurnRightWithSpeed(float speed)
{
  SetMotorDirection("leftMotor", "backward");
  SetMotorSpeed("leftMotor", speed);
  SetMotorDirection("rightMotor", "forward");
  SetMotorSpeed("rightMotor", speed);
  this->leftMotor.UpdateState();
  this->rightMotor.UpdateState();
  this->currentSpeed = speed;
  float speedRatio = 100/this->currentSpeed;
  delay(TIME_TO_90_TURN* speedRatio);
  NeutralStop();
}



void MotorDriver::ChangeSpeed(float newSpeed)
{
  SetMotorSpeed("leftMotor",newSpeed);
  SetMotorSpeed("rightMotor",newSpeed);
  this->leftMotor.UpdateState();
  this->rightMotor.UpdateState();
  this->currentSpeed = newSpeed;
}

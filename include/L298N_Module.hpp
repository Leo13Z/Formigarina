#include <Arduino.h>
#include <string.h>

class Motor
{
public:
  Motor();
  void SetPins(int enablePin, int input1Pin, int input2Pin);
  void UpdateState();
  void SetDirection(int direction);
  void SetSpeed(float speed);
private:
  int enablePin, input1Pin, input2Pin;
  int direction=0;// -1=backwards, 0=neutral, 1=forward, 2=stall
  float speed=0;//pwm value
};

class MotorDriver
{
public:
  MotorDriver(int enA, int in1, int in2, int in3, int in4, int enB);
  void SetMotorDirection(String actuator, String direction);
  void SetMotorSpeed(String actuator, float speedInPercent);
  void GoForward();
  void GoForwardWithSpeed(float speed);
  void GoBackward();
  void GoBackwardWithSpeed(float speed);
  void TurnLeft();
  void TurnLeftWithSpeed(float speed);
  void TurnRight();
  void TurnRightWithSpeed(float speed);
  void NeutralStop();
  void HardStop();
  void ChangeSpeed(float speed);
private:
  Motor leftMotor, rightMotor;
  float currentSpeed;
};

class UltraSonicModule
{
public:
  UltraSonicModule(int trigPin, int echoPin);
  float getDistance();
private:
  int trigPin;
  int echoPin;
};

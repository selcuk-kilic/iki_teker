
#include <CurieIMU.h>
#include <MadgwickAHRS.h>

class AHRS
{
public:
  void setup();
  bool loop(float* pitch, float* roll, float* heading);

private:
  float convertRawAcceleration(int aRaw);
  float convertRawGyro(int gRaw);

private:
  Madgwick filter;
  unsigned long microsPerReading, microsPrevious;

};


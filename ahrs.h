
#include <CurieIMU.h>
#include <MadgwickAHRS.h>

typedef void (*Reporter)(float yaw, float pitch, float roll);

class AHRS
{
public:
  void setup(Reporter sendResult);
<<<<<<< HEAD

private:
  static void filterUpdateIsr();
  static float convertRawAcceleration(int aRaw);
  static float convertRawGyro(int gRaw);

private:
  Madgwick filter;
  Reporter reporter;
=======
>>>>>>> c654cd88305a7de4f5de4b164ccfdd7b9b149cfe
};



#include <CurieIMU.h>
#include <MadgwickAHRS.h>

typedef void (*Reporter)(float yaw, float pitch, float roll);

class AHRS
{
public:
  void setup(Reporter sendResult);
};


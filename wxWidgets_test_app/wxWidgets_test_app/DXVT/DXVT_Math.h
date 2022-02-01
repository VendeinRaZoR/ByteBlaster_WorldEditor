#include "DXVT_Device.h"


bool EqFloat(float lhs, float rhs,float fEpsilon)
{
   return fabs(lhs - rhs) <= fEpsilon ? true : false;
}
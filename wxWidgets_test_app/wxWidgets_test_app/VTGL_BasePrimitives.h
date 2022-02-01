#include "VTGL_Geometry.h"

class VTGL_BasePrimitive
{
public:
VTGL_BasePrimitive();
~VTGL_BasePrimitive();
};

class VTGL_Ray : public VTGL_BasePrimitive
{
VTVector3D m_vOrigin;
VTVector3D m_vDirection;
VertexXYZ m_VXYZ[2];
VTGL_Geometry m_gmRay;
public:
VTGL_Ray(VTVector3D vOrigin,VTVector3D vDirection);
~VTGL_Ray();
};


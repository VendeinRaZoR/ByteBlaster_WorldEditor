#include "VTGL_Math.h"
#include "VTGL_Device.h"

///////////////2D Vector////////////////////////

VTVector2D::VTVector2D() 
{
}
    VTVector2D::VTVector2D( const float * pfValue)
	{
x = pfValue[0];
y = pfValue[1];
	}
    VTVector2D::VTVector2D( const VTVector2D& Vector2D )
	{
	   x = Vector2D.x;
	   y = Vector2D.y;
	}
    VTVector2D::VTVector2D(float _x, float _y)
	{
x = _x;
y = _y;
	}

    VTVector2D::operator float* ()
	{
		float vec2d[2] = {x,y};
		return &vec2d[0];
	}
    VTVector2D::operator const float* () const
	{
		float vec2d[2] = {x,y};
		return &vec2d[0];
	}

    VTVector2D& VTVector2D::operator += ( const VTVector2D& Vector2D)
	{
      x += Vector2D.x;
	  y += Vector2D.y;
	  return *this;
	}
    VTVector2D& VTVector2D::operator -= ( const VTVector2D& Vector2D)
	{
      x -= Vector2D.x;
	  y -= Vector2D.y;
      return *this;
	}
    VTVector2D& VTVector2D::operator *= ( float fValue)
	{
      x *= fValue;
	  y *= fValue;
	  return *this;
	}
	VTVector2D& VTVector2D::operator /= ( float fValue)
	{
      x /= fValue;
	  y /= fValue;
	  return *this;
	}

    VTVector2D &VTVector2D::operator + ( const VTVector2D& Vector2D)const
	{ 
VTVector2D TempVector2D;
TempVector2D.x = x + Vector2D.x;
TempVector2D.y = y + Vector2D.y;
return TempVector2D;
	}
    VTVector2D &VTVector2D::operator - ( const VTVector2D& Vector2D)const
	{
VTVector2D TempVector2D;
TempVector2D.x = x - Vector2D.x;
TempVector2D.y = y - Vector2D.y;
return TempVector2D;
	}
	VTVector2D &VTVector2D::operator * ( float fValue)const
	{
VTVector2D TempVector2D;
TempVector2D.x = x*fValue;
TempVector2D.y = y*fValue;
return TempVector2D;
	}
	VTVector2D &VTVector2D::operator / ( float fValue)const
	{
VTVector2D TempVector2D;
TempVector2D.x = x/fValue;
TempVector2D.y = y/fValue;
return TempVector2D;
	}

	VTVector2D &operator * ( float fValue, const VTVector2D& Vector2D)
	{
VTVector2D TempVector2D;
TempVector2D.x = Vector2D.x*fValue;
TempVector2D.y = Vector2D.y*fValue;
return TempVector2D;
	}

	VTVector2D VTVector2D::operator+()const
	{
return *this;
	}

	VTVector2D VTVector2D::operator-()const
	{
  return VTVector2D(-x,-y);
	}

	float VTVector2D::Length()const
	{
		return sqrt((x*x) + (y*y));
	}

    bool VTVector2D::operator == ( const VTVector2D& Vector2D)const
	{
		if(x == Vector2D.x && y == Vector2D.y)
			return true;
		else return false;
	}
	bool VTVector2D::operator != ( const VTVector2D& Vector2D)const
	{
		if(x != Vector2D.x && y != Vector2D.y)
			return true;
		else return false;
	}


///////////////3D Vector////////////////////////

	VTVector3D::VTVector3D() 
{
}
    VTVector3D::VTVector3D( const float * pfValue)
	{
x = pfValue[0];
y = pfValue[1];
z = pfValue[2];
	}
    VTVector3D::VTVector3D( const VTVector3D& Vector3D )
	{
	   x = Vector3D.x;
	   y = Vector3D.y;
	   z = Vector3D.z;
	}
    VTVector3D::VTVector3D(float _x, float _y,float _z)
	{
x = _x;
y = _y;
z = _z;
	}

    VTVector3D::operator float* ()
	{
		float vec3d[3] = {x,y,z};
		return &vec3d[0];
	}
    VTVector3D::operator const float* () const
	{
		float vec3d[3] = {x,y,z};
		return &vec3d[0];
	}

    VTVector3D& VTVector3D::operator += ( const VTVector3D& Vector3D)
	{
      x += Vector3D.x;
	  y += Vector3D.y;
	  z += Vector3D.z;
	  return *this;
	}
    VTVector3D& VTVector3D::operator -= ( const VTVector3D& Vector3D)
	{
      x -= Vector3D.x;
	  y -= Vector3D.y;
	  z -= Vector3D.z;
      return *this;
	}
    VTVector3D& VTVector3D::operator *= ( float fValue)
	{
      x *= fValue;
	  y *= fValue;
	  z *= fValue;
	  return *this;
	}
	VTVector3D& VTVector3D::operator /= ( float fValue)
	{
      x /= fValue;
	  y /= fValue;
	  z /= fValue;
	  return *this;
	}

    VTVector3D VTVector3D::operator + ( const VTVector3D& Vector3D)const
	{ 
VTVector3D TempVector3D;
TempVector3D.x = x + Vector3D.x;
TempVector3D.y = y + Vector3D.y;
TempVector3D.z = z + Vector3D.z;
return TempVector3D;
	}
    VTVector3D VTVector3D::operator - ( const VTVector3D& Vector3D)const
	{
VTVector3D TempVector3D;
TempVector3D.x = x - Vector3D.x;
TempVector3D.y = y - Vector3D.y;
TempVector3D.z = z - Vector3D.z;
return TempVector3D;
	}
	VTVector3D VTVector3D::operator * ( float fValue)const
	{
VTVector3D TempVector3D;
TempVector3D.x = x*fValue;
TempVector3D.y = y*fValue;
TempVector3D.z = z*fValue;
return TempVector3D;
}
	VTVector3D VTVector3D::operator / ( float fValue)const
	{
VTVector3D TempVector3D;
TempVector3D.x = x/fValue;
TempVector3D.y = y/fValue;
TempVector3D.z = z/fValue;
return TempVector3D;
	}

	VTVector3D operator * ( float fValue, const VTVector3D& Vector3D)
	{
VTVector3D TempVector3D;
TempVector3D.x = Vector3D.x*fValue;
TempVector3D.y = Vector3D.y*fValue;
TempVector3D.z = Vector3D.z*fValue;
return TempVector3D;
	}
	float operator * ( const VTVector3D& Vector3D_1, const VTVector3D& Vector3D_2)
	{
		return Vector3D_1.x*Vector3D_2.x + Vector3D_1.y*Vector3D_2.y + Vector3D_1.z*Vector3D_2.z;
	}

	VTVector3D VTVector3D::operator+()const
	{
return *this;
	}

	VTVector3D VTVector3D::operator-()const
	{
  return VTVector3D(-x,-y,-z);
	}

	float VTVector3D::Length()const
	{
		return sqrt((x*x) + (y*y) + (z*z));
	}

    bool VTVector3D::operator == ( const VTVector3D& Vector3D)const
	{
		if(x == Vector3D.x && y == Vector3D.y)
			return true;
		else return false;
	}
	bool VTVector3D::operator != ( const VTVector3D& Vector3D)const
	{
		if(x != Vector3D.x && y != Vector3D.y)
			return true;
		else return false;
	}

	bool VTVector3D::Normalize()
	{
x /= Length();
y /= Length();
z /= Length();
		return true;
	}

	bool VTVector3D::Cross(const VTVector3D &VT_Vector_1,const VTVector3D &VT_Vector_2)
	{
if(!strcmp(VTGL_Device::m_pszGraphicsApiChoice->ToAscii(),"OpenGL"))//Левосторонняя система координат в OpenGL
{
 //   printf("\nlook %.2f %.2f %.2f",VT_Vector_1.x,VT_Vector_1.y,VT_Vector_1.z);
	//printf("\nup %.2f %.2f %.2f",VT_Vector_2.x,VT_Vector_2.y,VT_Vector_2.z);
x = VT_Vector_1.z*VT_Vector_2.y - VT_Vector_1.y*VT_Vector_2.z;
y = VT_Vector_1.x*VT_Vector_2.z - VT_Vector_1.z*VT_Vector_2.x;
z = VT_Vector_1.y*VT_Vector_2.x - VT_Vector_1.x*VT_Vector_2.y;
}
if(!strcmp(VTGL_Device::m_pszGraphicsApiChoice->ToAscii(),"DirectX"))//Правосторонняя система координат в DirectX
{
x = VT_Vector_1.y*VT_Vector_2.z - VT_Vector_1.z*VT_Vector_2.y;
y = VT_Vector_1.z*VT_Vector_2.x - VT_Vector_1.x*VT_Vector_2.z;
z = VT_Vector_1.x*VT_Vector_2.y - VT_Vector_1.y*VT_Vector_2.x;
}
return true;
	}

///////////////3x3 Maxtrix////////////////////////

VTMatrix4::VTMatrix4()
{
f_11 = 0;
f_12 = 0;
f_13 = 0;
f_14 = 0;
f_21 = 0;
f_22 = 0;
f_23 = 0;
f_24 = 0;
f_31 = 0;
f_32 = 0;
f_33 = 0;
f_34 = 0;
f_41 = 0;
f_42 = 0;
f_43 = 0;
f_44 = 0;
}

VTMatrix4::VTMatrix4(float * pfMatrix)
	{
memcpy(&f_11, pfMatrix, sizeof(float)*4*4);
	}

/*VTMatrix4 &VTMatrix4::operator=(float * pfMatrix)
	{
memcpy(&f_11, pfMatrix, sizeof(float)*4*4);
return *this;
	}*/

bool VTMatrix4::Fill(float * pfMatrix)
{
memcpy((void*)&f_11, pfMatrix, sizeof(float)*4*4);
return true;//Should be corrected
}

VTMatrix4::VTMatrix4(const VTMatrix4 &Matrix4)
	{
f_11 = Matrix4.f_11;
f_12 = Matrix4.f_12;
f_13 = Matrix4.f_13;
f_14 = Matrix4.f_14;
f_21 = Matrix4.f_21;
f_22 = Matrix4.f_22;
f_23 = Matrix4.f_23;
f_24 = Matrix4.f_24;
f_31 = Matrix4.f_31;
f_32 = Matrix4.f_32;
f_33 = Matrix4.f_33;
f_34 = Matrix4.f_34;
f_41 = Matrix4.f_41;
f_42 = Matrix4.f_42;
f_43 = Matrix4.f_43;
f_44 = Matrix4.f_44;
	}
    
VTMatrix4::VTMatrix4(float f11, float f12, float f13, float f14, float f21, float f22, float f23, float f24, float f31, float f32, float f33, float f34,float f41, float f42, float f43, float f44)
	{
f_11 = f11;
f_12 = f12;
f_13 = f13;
f_14 = f14;
f_21 = f21;
f_22 = f22;
f_23 = f23;
f_24 = f24;
f_31 = f31;
f_32 = f32;
f_33 = f33;
f_34 = f34;
f_41 = f41;
f_42 = f42;
f_43 = f43;
f_44 = f44;
	}

VTMatrix4 &VTMatrix4::operator +(const VTMatrix4 & Matrix3) const
	{
VTMatrix4 tempMatrix3;
tempMatrix3.f_11 = f_11 + Matrix3.f_11;
tempMatrix3.f_12 = f_12 + Matrix3.f_12;
tempMatrix3.f_13 = f_13 + Matrix3.f_13;
tempMatrix3.f_21 = f_21 + Matrix3.f_21;
tempMatrix3.f_22 = f_22 + Matrix3.f_22;
tempMatrix3.f_23 = f_23 + Matrix3.f_23;
tempMatrix3.f_31 = f_31 + Matrix3.f_31;
tempMatrix3.f_32 = f_32 + Matrix3.f_32;
tempMatrix3.f_33 = f_33 + Matrix3.f_33;
return tempMatrix3;
	}

VTMatrix4 &VTMatrix4::operator -(const VTMatrix4 & Matrix3) const
	{
VTMatrix4 tempMatrix3;
tempMatrix3.f_11 = f_11 - Matrix3.f_11;
tempMatrix3.f_12 = f_12 - Matrix3.f_12;
tempMatrix3.f_13 = f_13 - Matrix3.f_13;
tempMatrix3.f_21 = f_21 - Matrix3.f_21;
tempMatrix3.f_22 = f_22 - Matrix3.f_22;
tempMatrix3.f_23 = f_23 - Matrix3.f_23;
tempMatrix3.f_31 = f_31 - Matrix3.f_31;
tempMatrix3.f_32 = f_32 - Matrix3.f_32;
tempMatrix3.f_33 = f_33 - Matrix3.f_33;
return tempMatrix3;
	}

VTMatrix4 &VTMatrix4::operator +=(const VTMatrix4 & Matrix3)
	{
f_11 += Matrix3.f_11;
f_12 += Matrix3.f_12;
f_13 += Matrix3.f_13;
f_21 += Matrix3.f_21;
f_22 += Matrix3.f_22;
f_23 += Matrix3.f_23;
f_31 += Matrix3.f_31;
f_32 += Matrix3.f_32;
f_33 += Matrix3.f_33;
return *this;
	}

VTMatrix4 &VTMatrix4::operator -=(const VTMatrix4 & Matrix3)
	{
f_11 -= Matrix3.f_11;
f_12 -= Matrix3.f_12;
f_13 -= Matrix3.f_13;
f_21 -= Matrix3.f_21;
f_22 -= Matrix3.f_22;
f_23 -= Matrix3.f_23;
f_31 -= Matrix3.f_31;
f_32 -= Matrix3.f_32;
f_33 -= Matrix3.f_33;
return *this;
	}

VTMatrix4 &VTMatrix4::operator*(float fValue) const
	{
VTMatrix4 tempMatrix3;
tempMatrix3.f_11 = f_11 * fValue;
tempMatrix3.f_12 = f_12 * fValue;
tempMatrix3.f_13 = f_13 * fValue;
tempMatrix3.f_21 = f_21 * fValue;
tempMatrix3.f_22 = f_22 * fValue;
tempMatrix3.f_23 = f_23 * fValue;
tempMatrix3.f_31 = f_31 * fValue;
tempMatrix3.f_32 = f_32 * fValue;
tempMatrix3.f_33 = f_33 * fValue;
return tempMatrix3;
	}

VTMatrix4 &VTMatrix4::operator/(float fValue) const
	{
VTMatrix4 tempMatrix3;
tempMatrix3.f_11 = f_11 / fValue;
tempMatrix3.f_12 = f_12 / fValue;
tempMatrix3.f_13 = f_13 / fValue;
tempMatrix3.f_21 = f_21 / fValue;
tempMatrix3.f_22 = f_22 / fValue;
tempMatrix3.f_23 = f_23 / fValue;
tempMatrix3.f_31 = f_31 / fValue;
tempMatrix3.f_32 = f_32 / fValue;
tempMatrix3.f_33 = f_33 / fValue;
return tempMatrix3;
	}

VTMatrix4 &operator * ( float fValue, const VTMatrix4& Matrix3 )
{
VTMatrix4 tempMatrix3;
tempMatrix3.f_11 = Matrix3.f_11 * fValue;
tempMatrix3.f_12 = Matrix3.f_12 * fValue;
tempMatrix3.f_13 = Matrix3.f_13 * fValue;
tempMatrix3.f_21 = Matrix3.f_21 * fValue;
tempMatrix3.f_22 = Matrix3.f_22 * fValue;
tempMatrix3.f_23 = Matrix3.f_23 * fValue;
tempMatrix3.f_31 = Matrix3.f_31 * fValue;
tempMatrix3.f_32 = Matrix3.f_32 * fValue;
tempMatrix3.f_33 = Matrix3.f_33 * fValue;
return tempMatrix3;
}

VTVector3D VTMatrix4::operator *(const VTVector3D& Vector3D) const
{
VTVector3D tempVector3D;
tempVector3D.x = Vector3D.x*f_11 + Vector3D.y*f_12 + Vector3D.z*f_13;
tempVector3D.y = Vector3D.x*f_21 + Vector3D.y*f_22 + Vector3D.z*f_23;
tempVector3D.z = Vector3D.x*f_31 + Vector3D.y*f_32 + Vector3D.z*f_33;
return tempVector3D;
}

VTMatrix4 VTMatrix4::operator *(const VTMatrix4& Matrix3) const /// По ссылке не передавать , объект разрушается после выхода из функции !!!
{
VTMatrix4 tempMatrix4;
tempMatrix4.f_11 = (f_11*Matrix3.f_11)+(f_12*Matrix3.f_21)+(f_13*Matrix3.f_31)+(f_14*Matrix3.f_41);
tempMatrix4.f_12 = (f_11*Matrix3.f_12)+(f_12*Matrix3.f_22)+(f_13*Matrix3.f_32)+(f_14*Matrix3.f_42);
tempMatrix4.f_13 = (f_11*Matrix3.f_13)+(f_12*Matrix3.f_23)+(f_13*Matrix3.f_33)+(f_14*Matrix3.f_43);
tempMatrix4.f_14 = (f_11*Matrix3.f_14)+(f_12*Matrix3.f_24)+(f_13*Matrix3.f_34)+(f_14*Matrix3.f_44);
tempMatrix4.f_21 = (f_21*Matrix3.f_11)+(f_22*Matrix3.f_21)+(f_23*Matrix3.f_31)+(f_24*Matrix3.f_41);
tempMatrix4.f_22 = (f_21*Matrix3.f_12)+(f_22*Matrix3.f_22)+(f_23*Matrix3.f_32)+(f_24*Matrix3.f_42);
tempMatrix4.f_23 = (f_21*Matrix3.f_13)+(f_22*Matrix3.f_23)+(f_23*Matrix3.f_33)+(f_24*Matrix3.f_43);
tempMatrix4.f_24 = (f_21*Matrix3.f_14)+(f_22*Matrix3.f_24)+(f_23*Matrix3.f_34)+(f_24*Matrix3.f_44);
tempMatrix4.f_31 = (f_31*Matrix3.f_11)+(f_32*Matrix3.f_21)+(f_33*Matrix3.f_31)+(f_34*Matrix3.f_41);
tempMatrix4.f_32 = (f_31*Matrix3.f_12)+(f_32*Matrix3.f_22)+(f_33*Matrix3.f_32)+(f_34*Matrix3.f_42);
tempMatrix4.f_33 = (f_31*Matrix3.f_13)+(f_32*Matrix3.f_23)+(f_33*Matrix3.f_33)+(f_34*Matrix3.f_43);
tempMatrix4.f_34 = (f_31*Matrix3.f_14)+(f_32*Matrix3.f_24)+(f_33*Matrix3.f_34)+(f_34*Matrix3.f_44);
tempMatrix4.f_41 = (f_41*Matrix3.f_11)+(f_42*Matrix3.f_21)+(f_43*Matrix3.f_31)+(f_44*Matrix3.f_41);
tempMatrix4.f_42 = (f_41*Matrix3.f_12)+(f_42*Matrix3.f_22)+(f_43*Matrix3.f_32)+(f_44*Matrix3.f_42);
tempMatrix4.f_43 = (f_41*Matrix3.f_13)+(f_42*Matrix3.f_23)+(f_43*Matrix3.f_33)+(f_44*Matrix3.f_43);
tempMatrix4.f_44 = (f_41*Matrix3.f_14)+(f_42*Matrix3.f_24)+(f_43*Matrix3.f_34)+(f_44*Matrix3.f_44);
return tempMatrix4;
}

VTMatrix4 &VTMatrix4::operator*=(const VTMatrix4& Matrix3)
{
f_11 = (f_11*Matrix3.f_11)+(f_12*Matrix3.f_21)+(f_13*Matrix3.f_31)+(f_14*Matrix3.f_41);
f_12 = (f_11*Matrix3.f_12)+(f_12*Matrix3.f_22)+(f_13*Matrix3.f_32)+(f_14*Matrix3.f_42);
f_13 = (f_11*Matrix3.f_13)+(f_12*Matrix3.f_23)+(f_13*Matrix3.f_33)+(f_14*Matrix3.f_43);
f_14 = (f_11*Matrix3.f_14)+(f_12*Matrix3.f_24)+(f_13*Matrix3.f_34)+(f_14*Matrix3.f_44);
f_21 = (f_21*Matrix3.f_11)+(f_22*Matrix3.f_21)+(f_23*Matrix3.f_31)+(f_24*Matrix3.f_41);
f_22 = (f_21*Matrix3.f_12)+(f_22*Matrix3.f_22)+(f_23*Matrix3.f_32)+(f_24*Matrix3.f_42);
f_23 = (f_21*Matrix3.f_13)+(f_22*Matrix3.f_23)+(f_23*Matrix3.f_33)+(f_24*Matrix3.f_43);
f_24 = (f_21*Matrix3.f_14)+(f_22*Matrix3.f_24)+(f_23*Matrix3.f_34)+(f_24*Matrix3.f_44);
f_31 = (f_31*Matrix3.f_11)+(f_32*Matrix3.f_21)+(f_33*Matrix3.f_31)+(f_34*Matrix3.f_41);
f_32 = (f_31*Matrix3.f_12)+(f_32*Matrix3.f_22)+(f_33*Matrix3.f_32)+(f_34*Matrix3.f_42);
f_33 = (f_31*Matrix3.f_13)+(f_32*Matrix3.f_23)+(f_33*Matrix3.f_33)+(f_34*Matrix3.f_43);
f_34 = (f_31*Matrix3.f_14)+(f_32*Matrix3.f_24)+(f_33*Matrix3.f_34)+(f_34*Matrix3.f_44);
f_41 = (f_41*Matrix3.f_11)+(f_42*Matrix3.f_21)+(f_43*Matrix3.f_31)+(f_44*Matrix3.f_41);
f_42 = (f_41*Matrix3.f_12)+(f_42*Matrix3.f_22)+(f_43*Matrix3.f_32)+(f_44*Matrix3.f_42);
f_43 = (f_41*Matrix3.f_13)+(f_42*Matrix3.f_23)+(f_43*Matrix3.f_33)+(f_44*Matrix3.f_43);
f_44 = (f_41*Matrix3.f_14)+(f_42*Matrix3.f_24)+(f_43*Matrix3.f_34)+(f_44*Matrix3.f_44);
return *this;
}

float VTMatrix4::operator ()(unsigned int Row, unsigned int Col) const
{
	return  m[Row][Col];
}

float &VTMatrix4::operator ()(unsigned int Row, unsigned int Col)
{
	return  m[Row][Col];
}

/*VTMatrix4::operator float *()
{
	float pfMatrix4[] = {f_11,f_12,f_13,f_14,f_21,f_22,f_23,f_24,f_31,f_32,f_33,f_34,f_41,f_42,f_43,f_44};
	return pfMatrix4;
}*/

VTMatrix4 &VTGL_TranslateXYZ(VTMatrix4 * pOut,float x,float y,float z)
{
if(!strcmp(VTGL_Device::m_pszGraphicsApiChoice->ToAscii(),"DirectX"))
{
float mafTranslation[4][4] = {
	{1,0,0,0},
	{0,1,0,0},
	{0,0,1,0},
	{x,y,z,1}
};
pOut->Fill(&mafTranslation[0][0]);
return *pOut;
}
if(!strcmp(VTGL_Device::m_pszGraphicsApiChoice->ToAscii(),"OpenGL"))
{
float mafTranslation[4][4] = {
	{1,0,0,0},
	{0,1,0,0},
	{0,0,1,0},
	{x,-y,z,1}
};
pOut->Fill(&mafTranslation[0][0]);
return *pOut;
}
}

VTMatrix4 &VTGL_RotationX(VTMatrix4 * pOut,float fAngle)
{
   fAngle = VTGL_ToRadian(fAngle);
if(!strcmp(VTGL_Device::m_pszGraphicsApiChoice->ToAscii(),"DirectX"))
{
	float mafRotationX[4][4] = {
		{1,0,0,0},
		{0,cos(fAngle),sin(fAngle),0},
		{0,-sin(fAngle),cos(fAngle),0},
		{0,0,0,1}
	};
pOut->Fill(&mafRotationX[0][0]);
return *pOut;
}
if(!strcmp(VTGL_Device::m_pszGraphicsApiChoice->ToAscii(),"OpenGL"))
{
	float mafRotationX[4][4] = {
		{1,0,0,0},
		{0,cos(fAngle),-sin(fAngle),0},
		{0,sin(fAngle),cos(fAngle),0},
		{0,0,0,1}
	};
pOut->Fill(&mafRotationX[0][0]);
return *pOut;
}
}

VTMatrix4 &VTGL_RotationY(VTMatrix4 * pOut,float fAngle)
{
   fAngle = VTGL_ToRadian(fAngle);
if(!strcmp(VTGL_Device::m_pszGraphicsApiChoice->ToAscii(),"DirectX"))
{
	float mafRotationY[4][4] = {
		{cos(fAngle),0,-sin(fAngle),0},
		{0,1,0,0},
		{sin(fAngle),0,cos(fAngle),0},
		{0,0,0,1}
	};
pOut->Fill(&mafRotationY[0][0]);
return *pOut;
}
if(!strcmp(VTGL_Device::m_pszGraphicsApiChoice->ToAscii(),"OpenGL"))
{
	float mafRotationY[4][4] = {
		{cos(fAngle),0,sin(fAngle),0},
		{0,1,0,0},
		{-sin(fAngle),0,cos(fAngle),0},
		{0,0,0,1}
	};
pOut->Fill(&mafRotationY[0][0]);
return *pOut;
}
}

VTMatrix4 &VTGL_RotationZ(VTMatrix4 * pOut,float fAngle) // Всё таки это линейный оператор :)
{
if(!strcmp(VTGL_Device::m_pszGraphicsApiChoice->ToAscii(),"DirectX"))// Коррекция осей (В OGL другая ориентация базиса (правый vs левый)
{
   fAngle = VTGL_ToRadian(fAngle);
	float mafRotationZ[4][4] = {
		{cos(fAngle),sin(fAngle),0,0},
		{-sin(fAngle),cos(fAngle),0,0},
		{0,0,1,0},
		{0,0,0,1}
	};
pOut->Fill(&mafRotationZ[0][0]);
return *pOut;
}
if(!strcmp(VTGL_Device::m_pszGraphicsApiChoice->ToAscii(),"OpenGL"))
{
   fAngle = VTGL_ToRadian(fAngle);
	float mafRotationZ[4][4] = {
		{cos(fAngle),-sin(fAngle),0,0},
		{sin(fAngle),cos(fAngle),0,0},
		{0,0,1,0},
		{0,0,0,1}
	};
pOut->Fill(&mafRotationZ[0][0]);
return *pOut;
}
}

VTMatrix4 &VTGL_RotationAxis(VTMatrix4 * pOut,VTVector3D * pAxis,float fAngle)
{
	fAngle = VTGL_ToRadian(fAngle);
if(!strcmp(VTGL_Device::m_pszGraphicsApiChoice->ToAscii(),"DirectX"))
{
	float s = sin(fAngle);
	float c = cos(fAngle);
	float mafRotationAxis[4][4] = {
		{c + (((1-c)*(*pAxis).x*(*pAxis).x)/((*pAxis).Length()*(*pAxis).Length())),(((1-c)*(*pAxis).x*(*pAxis).y)/((*pAxis).Length()*(*pAxis).Length())) + s*(*pAxis).z/(*pAxis).Length(), (((1-c)*(*pAxis).x*(*pAxis).z)/((*pAxis).Length()*(*pAxis).Length())) - s*(*pAxis).y/(*pAxis).Length() , 0 },
		{(((1-c)*(*pAxis).x*(*pAxis).y)/((*pAxis).Length()*(*pAxis).Length())) - s*(*pAxis).z/(*pAxis).Length(),c + (((1-c)*(*pAxis).y*(*pAxis).y)/((*pAxis).Length()*(*pAxis).Length())),(((1-c)*(*pAxis).y*(*pAxis).z)/((*pAxis).Length()*(*pAxis).Length())) + s*(*pAxis).x/(*pAxis).Length(),0},
		{(((1-c)*(*pAxis).x*(*pAxis).z)/((*pAxis).Length()*(*pAxis).Length())) + s*(*pAxis).y/(*pAxis).Length(),(((1-c)*(*pAxis).y*(*pAxis).z)/((*pAxis).Length()*(*pAxis).Length())) - s*(*pAxis).x/(*pAxis).Length(),c + (((1-c)*(*pAxis).z*(*pAxis).z)/((*pAxis).Length()*(*pAxis).Length())),0},
		{0,0,0,1}
	};///Матрица поворота. Получается разложением вращаемого вектора по 3-м компонентам и повороту 2-х основных перпендикулярных (см Mathematics for Game 3D programming) ...
pOut->Fill(&mafRotationAxis[0][0]);
return *pOut;
}
if(!strcmp(VTGL_Device::m_pszGraphicsApiChoice->ToAscii(),"OpenGL"))
{
	(*pAxis).y = -(*pAxis).y;
	float s = sin(-fAngle);
	float c = cos(-fAngle);
		float mafRotationAxis[4][4] = {
		{c + (((1-c)*(*pAxis).x*(*pAxis).x)/((*pAxis).Length()*(*pAxis).Length())),(((1-c)*(*pAxis).x*(*pAxis).y)/((*pAxis).Length()*(*pAxis).Length())) + s*(*pAxis).z/(*pAxis).Length(), (((1-c)*(*pAxis).x*(*pAxis).z)/((*pAxis).Length()*(*pAxis).Length())) - s*(*pAxis).y/(*pAxis).Length() , 0 },
		{(((1-c)*(*pAxis).x*(*pAxis).y)/((*pAxis).Length()*(*pAxis).Length())) - s*(*pAxis).z/(*pAxis).Length(),c + (((1-c)*(*pAxis).y*(*pAxis).y)/((*pAxis).Length()*(*pAxis).Length())),(((1-c)*(*pAxis).y*(*pAxis).z)/((*pAxis).Length()*(*pAxis).Length())) + s*(*pAxis).x/(*pAxis).Length(),0},
		{(((1-c)*(*pAxis).x*(*pAxis).z)/((*pAxis).Length()*(*pAxis).Length())) + s*(*pAxis).y/(*pAxis).Length(),(((1-c)*(*pAxis).y*(*pAxis).z)/((*pAxis).Length()*(*pAxis).Length())) - s*(*pAxis).x/(*pAxis).Length(),c + (((1-c)*(*pAxis).z*(*pAxis).z)/((*pAxis).Length()*(*pAxis).Length())),0},
		{0,0,0,1}
	};///Матрица поворота. Получается разложением вращаемого вектора по 3-м компонентам и повороту 2-х основных перпендикулярных см Mathematics for Game 3D programming ...
pOut->Fill(&mafRotationAxis[0][0]);
return *pOut;
}
}

VTMatrix4 &VTGL_Scaling(VTMatrix4 * pOut,float x,float y,float z)
{
float mafTranslation[4][4] = {
	{x,0,0,0},
	{0,y,0,0},
	{0,0,z,0},
	{0,0,0,1}
};
pOut->Fill(&mafTranslation[0][0]);
return *pOut;
}

VTMatrix4 &VTGL_Perspective(VTMatrix4 * pOut,float fFOV,float fAspect, float fZNear,float fZFar)//Perspective Projection Matrix
{
float fScaleY = cos(fFOV)/sin(fFOV);///zoom = 1/tg(FOV/2)       \FOV |   /   ZOOMx/ZOOMy = ResX/ResY
float fScaleX = fScaleY/fAspect;/////                | - zoom      \ | / 
if(!strcmp(VTGL_Device::m_pszGraphicsApiChoice->ToAscii(),"DirectX"))
{
float mafProjection[4][4] = {///////                                 O        => x' = (x*ScaleX)/Z' (devide on Z' - after 4D to 3D)
{fScaleX,0,0,0},
{0,fScaleY,0,0},
{0,0,((fZFar)/(fZFar-fZNear)),1},//         Formula :   Z' = d/Z (d=1) = 1/Z         Z'' : [0;1]
{0,0,-((fZFar*fZNear)/(fZFar-fZNear)),0}
	};//API depending         Z'' = A*Z' + B (lenear transform) A = > = _33 B => = _43
pOut->Fill(&mafProjection[0][0]);
return *pOut;
}
if(!strcmp(VTGL_Device::m_pszGraphicsApiChoice->ToAscii(),"OpenGL"))
{
float mafProjection[4][4] = {///////                                 O        => x' = (x*ScaleX)/Z' (devide on Z' - after 4D to 3D)
{fScaleX,0,0,0},
{0,fScaleY,0,0},
{0,0,((fZFar+fZNear)/(fZFar-fZNear)),1},//        Formula :   Z' = d/Z (d=1) = 1/Z         Z'' : [0;1]
{0,0,-((2*fZFar*fZNear)/(fZFar-fZNear)),0}};//         Z'' = A*Z' + B (lenear transform) A = > = _33 B => = _43 (метод конечных элементов)
pOut->Fill(&mafProjection[0][0]);
return *pOut;
} 
}

bool EqFloat(float lhs, float rhs,float fEpsilon)
{
   return fabs(lhs - rhs) <= fEpsilon ? true : false;
}

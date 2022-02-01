#ifndef _VTGL_GEOMETRY_H_
#define _VTGL_GEOMETRY_H_
#include "VTGL_Device.h"

#define MAX_FLOAT_LEN 8

#define MAX_ELEM_LOCAL 350 // can be changed 

struct VertexXYZUV
{
     VertexXYZUV(){}
     VertexXYZUV(float x, float y, float z, float u, float v)
     {
          _x = x; _y = y; _z = z; _u = u; _v = v;
     }
     float _x, _y, _z;
     float _u, _v;
     //static const DWORD FVF = D3DFVF_XYZ | D3DFVF_TEX1;
};

struct VertexXYZUVN
{
     VertexXYZUVN(){}
     VertexXYZUVN(float x, float y, float z,float nx,float ny,float nz, float u, float v)
     {
          _x = x; _y = y; _z = z; _u = u; _v = v;
		  _nx = nx;_ny = ny;_nz = nz;
     }
     float _x, _y, _z;
     float _u, _v;
	 float _nx,_ny,_nz;
     //static const DWORD FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1;
};

struct VertexXYZC
{
     VertexXYZC(){}
     VertexXYZC(float x, float y, float z,unsigned int dwColor)
     {
          _x = x; _y = y; _z = z;
		  _dwColor = dwColor;
if(!strcmp(VTGL_Device::m_pszGraphicsApiChoice->ToAscii(),"OpenGL"))
{
		  char temp1 = pBytes[0];//Color inversion in OpenGL (invert ARGB - RGBA)
		  char temp2 = pBytes[1];
		  char temp3 = pBytes[2];
		  char temp4 = pBytes[3];
		  pBytes[0] = temp3;
		  pBytes[1] = temp2;
		  pBytes[2] = temp1;
		  pBytes[3] = temp4;
}
     }
     float _x, _y, _z;
union 
{
	 unsigned int _dwColor;
	 char pBytes[4];
};
};

struct VertexXYZ
{
	VertexXYZ(){};
     VertexXYZ(float x, float y, float z)
     {
          _x = x; _y = y; _z = z;
     }
     float _x, _y, _z;
     //static const DWORD FVF = D3DFVF_XYZ;
};

struct ColorRGB
{
     ColorRGB(float cr, float cg, float cb)
     {
          _cr = cr; _cg = cg; _cb = cb;
     }
     float _cr, _cg, _cb;
};

class VTGL_BaseGeometry
{
public:
    virtual void CreateVertexBuffer(size_t Size,int nNumVert,char * szVertexFormat) = 0;
	virtual void CreateIndexBuffer16(size_t Size) = 0;
	virtual void CreateIndexBuffer32(size_t Size) = 0;
	virtual void * MapIndex() = 0;
	virtual void * MapVertex() = 0;//In User Memory
	virtual void UnMapIndex() = 0;
	virtual void UnMapVertex() = 0;
	virtual void Draw(int nNumPrimitives,wxString vszPrimitiveType = "Triangle") = 0;
};

class VTGL_Geometry : public VTGL_BaseGeometry
{
VTGL_BaseDevice * m_pVTGLDevice;
VTGL_BaseGeometry * m_pVTGLGeometry;
public:
VTGL_Geometry(VTGL_BaseDevice *pVTGLDevice = NULL);
~VTGL_Geometry();
    virtual void CreateVertexBuffer(size_t Size,int nNumVert,char * szVertexFormat);
	virtual void CreateIndexBuffer16(size_t Size);
	virtual void CreateIndexBuffer32(size_t Size);
	virtual void * MapIndex();
	virtual void * MapVertex();//In User Memory
	virtual void UnMapIndex();
	virtual void UnMapVertex();
	virtual void Draw(int nNumPrimitives,wxString vszPrimitiveType = "Triangle");
};

void SetIndice(int * Index,int nIndexNum,int nValue);


#endif
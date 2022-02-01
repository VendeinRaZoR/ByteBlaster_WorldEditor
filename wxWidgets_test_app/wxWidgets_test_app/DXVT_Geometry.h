#ifndef _DXVT_GEOMETRY_
#define _DXVT_GEOMETRY_
#include "DXVT_Device.h"
#include "DXVT_Texture.h"
#include "DXVT_Camera.h"//TODO : Луч как отдельный класс/структура !!! (класс луча как геометрия)
#include "VAlg.h"

#define MAX_FLOAT_LEN 8

#define MAX_ELEM_LOCAL 350 // can be changed 

struct VertexXYZCUV
{
     VertexXYZCUV(){}
     VertexXYZCUV(float x, float y, float z,DWORD dwColor, float u, float v)
     {
          _x = x; _y = y; _z = z;_dwColor = dwColor; _u = u; _v = v;
     }
     float _x, _y, _z;
	 DWORD _dwColor;
     float _u, _v;
     static const DWORD FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1;
};

struct VertexXYZC
{
     VertexXYZC(){}
     VertexXYZC(float x, float y, float z,DWORD dwColor)
     {
          _x = x; _y = y; _z = z;_dwColor = dwColor;
     }
     float _x, _y, _z;
	 DWORD _dwColor;
     static const DWORD FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE;
};

struct VertexXYZ
{
     VertexXYZ(){}
     VertexXYZ(float x, float y, float z)
     {
          _x = x; _y = y; _z = z;
     }
     float _x, _y, _z;
     static const DWORD FVF = D3DFVF_XYZ;
};

class DXVTBaseGeometry
{
protected:
	DXVTDevice* m_pDXVTDevice;
public:
	IDirect3DVertexBuffer9* m_pVertexBuffer;
    IDirect3DIndexBuffer9*  m_pIndexBuffer;
	size_t m_vertSize;
	int m_nNumVert;
	DWORD m_dwFormat;
public:
	DXVTBaseGeometry(DXVTDevice *pDXVTDevice = NULL);
	~DXVTBaseGeometry();
	IDirect3DVertexBuffer9* GetVertexBuffer();
	IDirect3DIndexBuffer9* GetIndexBuffer();
    void CreateVertexBuffer(size_t Size,DWORD dwFormat,int nNumVert);
	void CreateIndexBuffer16(size_t Size);
	void CreateIndexBuffer32(size_t Size);
	void GetIndex(void ** ppIndices);
	void GetVertex(void ** ppVertices);
	void SetIndex();
	void SetVertex();
	virtual void Draw(int nNumPrimitives,String::VString vszPrimitiveType = "Triangle");
	virtual void SetTexture(DXVTTexture * pDXVTTexture);
};


class DXVTRay : public DXVTBaseGeometry
{
  D3DXVECTOR3 m_Origin;
  D3DXVECTOR3 m_Direction;
  static const int MAX_LEN = 100;
  VertexXYZ * m_VXYZ;
public:
  DXVTRay(D3DXVECTOR3 Origin,D3DXVECTOR3 Direction);
  ~DXVTRay();
  D3DXVECTOR3 GetOrigin();
  D3DXVECTOR3 GetDirection();
  void Transform(D3DXMATRIX* T);
  float GetLength();
};

class DXVTTerrain : public DXVTBaseGeometry
{
int m_nNumVertsPerRow,m_nNumVertsPerCol,m_nCellSpacing;
	int m_nNumCellsPerRow;
	int m_nNumCellsPerCol;
	int m_nWidth;
	int m_nDepth;
	int m_nNumVertices;
	int m_nNumTriangles;
	std::vector<float>m_vHeightMap;
	D3DXVECTOR3 *m_pvLightDirection;
private:
		VertexXYZCUV* v;
public:
	DXVTTerrain(DXVTDevice *pDXVTDevice,int nNumVertsPerRow,int nNumVertsPerCol,int nCellSpacing);
	DXVTTerrain(DXVTDevice *pDXVTDevice);
	~DXVTTerrain();
	void SetParam(int nNumCellsPerRow,int nNumCellsPerCol,int nCellSpacing);
	bool Vertices(DWORD dwVertColor);
	bool Indices();
	void SetHeightMap(int nHeight);
	int GetNumTriangles();
	int GetCellspacing();
public:
	void SetTexture(DXVTTexture * pDXVTTexture);
	void ReadRAWData(char * szFileName);
	void WriteRAWData(char * szFileName);
public:
	float GetHeightMapElement(int nRow,int nCol);
	float GetHeightMapElement(int nIndex);
	void SetHeightMapElement(int nRow,int nCol,float fValue);
	void SetHeightMapElement(int nIndex,float fValue);
	void SetHeightMapElement(float nX,float nY,float fValue);
	float GetShadeElement(int nVertRow, int nVertCol);
	VertexXYZCUV * GetVertexXYZCUV();
	float GetWidth();
	float GetDepth();
VertexXYZCUV * FindPickNode(DXVTCamera::PickRay * pPickRay,int nTerrainLevel);
public:
	int * GetTraceRadius(D3DXVECTOR3 *pPickRay,int nTerrainLevel,float fRadius,D3DXVECTOR3 * vCenter,int &nNumVertFound);
public:
	void SetLightDirection(D3DXVECTOR3 * pLightDirection);
	D3DXVECTOR3 *GetRayTrace(DXVTCamera::PickRay * pPickRay,int nTerrainLevel);
};

#endif
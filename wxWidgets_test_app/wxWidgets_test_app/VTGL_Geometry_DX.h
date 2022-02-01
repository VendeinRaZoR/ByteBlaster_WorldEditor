#include "VTGL_Device_DX.h"
#include "VTGL_Geometry.h"

class VTGL_BaseGeometry_DX : public VTGL_BaseGeometry
{
protected:
	VTGL_Device_DX* m_pVTGLDevice;
public:
	IDirect3DVertexBuffer9* m_pVertexBuffer;
    IDirect3DIndexBuffer9*  m_pIndexBuffer;
	size_t m_vertSize;
	int m_nNumVert;
	DWORD m_dwFormat;
public:
	VTGL_BaseGeometry_DX(VTGL_Device_DX *pVTGLDevice = NULL);
	~VTGL_BaseGeometry_DX();
    virtual void CreateVertexBuffer(size_t Size,int nNumVert,char * szVertexFormat);
	virtual void CreateIndexBuffer16(size_t Size);
	virtual void CreateIndexBuffer32(size_t Size);
	virtual void * MapIndex();
	virtual void * MapVertex();//In User Memory
	virtual void UnMapIndex();
	virtual void UnMapVertex();
	virtual void Draw(int nNumPrimitives,wxString vszPrimitiveType = "Triangle");
	//virtual void SetTexture(DXVTTexture * pDXVTTexture);
};
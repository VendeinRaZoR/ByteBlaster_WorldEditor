#include "VTGL_Device_OGL.h"
#include "VTGL_Geometry.h"

class VTGL_BaseGeometry_OGL : public VTGL_BaseGeometry
{
protected:
	VTGL_Device_OGL* m_pVTGLDevice;
private:
	unsigned int m_unVBO;
	unsigned int m_unIBO;
    //IDirect3DIndexBuffer9*  m_pIndexBuffer; // index buffer for OGL
	size_t m_vertSize;
	int m_nNumVert;
	DWORD m_dwFormat;
	unsigned short *m_ppIndices;
public:
	VTGL_BaseGeometry_OGL(VTGL_Device_OGL *pVTGLDevice = NULL);
	~VTGL_BaseGeometry_OGL();
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
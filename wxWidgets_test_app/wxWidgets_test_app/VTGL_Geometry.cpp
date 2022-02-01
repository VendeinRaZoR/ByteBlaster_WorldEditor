#include "VTGL_Geometry.h"
#include "VTGL_Geometry_DX.h"
#include "VTGL_Geometry_OGL.h"

VTGL_Geometry::VTGL_Geometry(VTGL_BaseDevice *pVTGLDevice)
{
m_pVTGLDevice = pVTGLDevice;
if(!VTGL_Device::m_pszGraphicsApiChoice->Cmp("DirectX"))
m_pVTGLGeometry = new VTGL_BaseGeometry_DX(static_cast<VTGL_Device_DX*>(pVTGLDevice));
if(!VTGL_Device::m_pszGraphicsApiChoice->Cmp("OpenGL"))
m_pVTGLGeometry = new VTGL_BaseGeometry_OGL(static_cast<VTGL_Device_OGL*>(pVTGLDevice));
}

VTGL_Geometry::~VTGL_Geometry()
{

}

void VTGL_Geometry::CreateVertexBuffer(size_t Size,int nNumVert,char * szVertexFormat)
{
	m_pVTGLGeometry->CreateVertexBuffer(Size,nNumVert,szVertexFormat);
}


void VTGL_Geometry::CreateIndexBuffer16(size_t Size)
{
m_pVTGLGeometry->CreateIndexBuffer16(Size);
}

void VTGL_Geometry::CreateIndexBuffer32(size_t Size)
{
m_pVTGLGeometry->CreateIndexBuffer32(Size);
}

void VTGL_Geometry::UnMapIndex()
{
	m_pVTGLGeometry->UnMapIndex();
}

void VTGL_Geometry::UnMapVertex()
{
	m_pVTGLGeometry->UnMapVertex();
}

void * VTGL_Geometry::MapIndex()
{
return m_pVTGLGeometry->MapIndex();
}

void * VTGL_Geometry::MapVertex()
{
return m_pVTGLGeometry->MapVertex();
}

void VTGL_Geometry::Draw(int nNumPrimitives,wxString vszPrimitiveType)
{
m_pVTGLGeometry->Draw(nNumPrimitives,vszPrimitiveType);
}

void SetIndice(int * Index,int nIndexNum,int nValue)
{
	if(!VTGL_Device::m_pszGraphicsApiChoice->Cmp("DirectX"))
	{
WORD * Indices = (WORD*)Index;
Indices[nIndexNum] = (WORD)nValue;
	}
	else
	{
unsigned char * Indices = (unsigned char *)Index;
Indices[nIndexNum] = (unsigned char)nValue;
	}
}
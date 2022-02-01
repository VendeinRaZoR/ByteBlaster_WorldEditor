#include "VTGL_Geometry_DX.h"

VTGL_BaseGeometry_DX::VTGL_BaseGeometry_DX(VTGL_Device_DX *pVTGLDevice)
{
m_pVTGLDevice = pVTGLDevice;
m_pIndexBuffer = NULL;
m_pVertexBuffer = NULL;
}

VTGL_BaseGeometry_DX::~VTGL_BaseGeometry_DX()
{

}

void VTGL_BaseGeometry_DX::CreateVertexBuffer(size_t Size,int nNumVert,char * szVertexFormat)
{
	  	 m_vertSize = Size;
		 m_nNumVert = nNumVert;
if(!strcmp(szVertexFormat,"Position"))
  {
	  m_dwFormat = D3DFVF_XYZ;
	  }
 if(!strcmp(szVertexFormat,"Position+Color"))
  {
		 m_dwFormat = D3DFVF_XYZ | D3DFVF_DIFFUSE;
 }
		 m_pVTGLDevice->GetDevice()->CreateVertexBuffer(
                   Size*nNumVert, 
                   D3DUSAGE_WRITEONLY,
                   m_dwFormat,
                   D3DPOOL_MANAGED,
                   &m_pVertexBuffer,
                   0);
}

void VTGL_BaseGeometry_DX::CreateIndexBuffer16(size_t Size)
{
	     m_pVTGLDevice->GetDevice()->CreateIndexBuffer(
                   Size*sizeof(WORD),
                   D3DUSAGE_WRITEONLY,
                   D3DFMT_INDEX16,
                   D3DPOOL_MANAGED,
                   &m_pIndexBuffer,
                   0);
}

void VTGL_BaseGeometry_DX::CreateIndexBuffer32(size_t Size)
{
	     m_pVTGLDevice->GetDevice()->CreateIndexBuffer(
                   Size*sizeof(DWORD),
                   D3DUSAGE_WRITEONLY,
                   D3DFMT_INDEX32,
                   D3DPOOL_MANAGED,
                   &m_pIndexBuffer,
                   0);
}

void VTGL_BaseGeometry_DX::UnMapIndex()
{
	m_pIndexBuffer->Unlock();
}

void VTGL_BaseGeometry_DX::UnMapVertex()
{
	m_pVertexBuffer->Unlock();
}

void * VTGL_BaseGeometry_DX::MapIndex()
{
void * ppIndices = 0;
m_pIndexBuffer->Lock(0, 0, &ppIndices, 0);
return ppIndices;
}

void * VTGL_BaseGeometry_DX::MapVertex()
{
void * ppVertices = 0;
m_pVertexBuffer->Lock(0, 0,&ppVertices, 0);
return ppVertices;
}
void VTGL_BaseGeometry_DX::Draw(int nNumPrimitives,wxString vszPrimitiveType)
{
	//m_pVTGLDevice->GetDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

m_pVTGLDevice->GetDevice()->SetRenderState(D3DRS_LIGHTING, false);//Needed for setting the color !!!

		  m_pVTGLDevice->GetDevice()->SetStreamSource(0, m_pVertexBuffer, 0, m_vertSize);
		  if(m_pIndexBuffer)
          m_pVTGLDevice->GetDevice()->SetIndices(m_pIndexBuffer);
          m_pVTGLDevice->GetDevice()->SetFVF(m_dwFormat);
		  if(!vszPrimitiveType.Cmp("Triangle") && m_pIndexBuffer)
          m_pVTGLDevice->GetDevice()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,0, 0, m_nNumVert, 0, nNumPrimitives);
		  if(!vszPrimitiveType.Cmp("Triangle") && !m_pIndexBuffer)
		  m_pVTGLDevice->GetDevice()->DrawPrimitive(D3DPT_TRIANGLELIST,0,nNumPrimitives);
		  if(!vszPrimitiveType.Cmp("Line") && m_pIndexBuffer)
		  m_pVTGLDevice->GetDevice()->DrawIndexedPrimitive(D3DPT_LINELIST,0, 0, m_nNumVert, 0, nNumPrimitives);
		  if(!vszPrimitiveType.Cmp("Line") && !m_pIndexBuffer)
		  m_pVTGLDevice->GetDevice()->DrawPrimitive(D3DPT_LINELIST,0,nNumPrimitives);
		  if(!vszPrimitiveType.Cmp("Point") && m_pIndexBuffer)
		  m_pVTGLDevice->GetDevice()->DrawIndexedPrimitive(D3DPT_POINTLIST,0, 0, m_nNumVert, 0, nNumPrimitives);
		  if(!vszPrimitiveType.Cmp("Point") && !m_pIndexBuffer)
		  m_pVTGLDevice->GetDevice()->DrawPrimitive(D3DPT_POINTLIST,0,nNumPrimitives);
}

/*IDirect3DVertexBuffer9* DXVTBaseGeometry::GetVertexBuffer()
{
return m_pVertexBuffer;
}

IDirect3DIndexBuffer9* DXVTBaseGeometry::GetIndexBuffer()
{
return m_pIndexBuffer;

}*/



/*
void DXVTBaseGeometry::SetTexture(DXVTTexture * pDXVTTexture)
{

}

/*
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////Terrain//////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

DXVTTerrain::DXVTTerrain(DXVTDevice *pDXVTDevice,int nNumCellsPerRow,int nNumCellsPerCol,int nCellSpacing)
{
m_pDXVTDevice = pDXVTDevice;
m_nNumCellsPerRow = nNumCellsPerRow;
m_nNumCellsPerCol = nNumCellsPerCol;
m_nNumVertsPerRow = nNumCellsPerRow + 1;
m_nNumVertsPerCol = nNumCellsPerCol + 1;
m_nCellSpacing = nCellSpacing;
m_nWidth = m_nNumCellsPerRow * m_nCellSpacing;
m_nDepth = m_nNumCellsPerCol * m_nCellSpacing;
m_nNumVertices = m_nNumVertsPerRow * m_nNumVertsPerCol;
m_nNumTriangles = m_nNumCellsPerRow * m_nNumCellsPerCol * 2;
m_vHeightMap.resize(m_nNumVertices+1);
}

DXVTTerrain::DXVTTerrain(DXVTDevice *pDXVTDevice)
{
	m_pDXVTDevice = pDXVTDevice;
}

DXVTTerrain::~DXVTTerrain()
{

}

void DXVTTerrain::SetHeightMap(int nHeight)
{
	for(int i = 0; i < m_nNumVertices; i++)
	m_vHeightMap[i] = nHeight;
}

bool DXVTTerrain::Vertices(DWORD dwVertColor)
{
     CreateVertexBuffer(m_nNumVertices * sizeof(VertexXYZCUV),VertexXYZCUV::FVF,m_nNumVertices);

	// coordinates to start generating vertices at
	int startX = -m_nWidth / 2;
	int startZ =  m_nDepth / 2;

	// coordinates to end generating vertices at
	int endX =  m_nWidth / 2;
	int endZ = -m_nDepth / 2;

	// compute the increment size of the texture coordinates
	// from one vertex to the next.
	float uCoordIncrementSize = 1.0f / (float)(m_nNumCellsPerRow);
	float vCoordIncrementSize = 1.0f / (float)(m_nNumCellsPerCol);

	GetVertex((void**)&v);


     int i = 0;
     for(float z = startZ; z >= endZ; z -= m_nCellSpacing)
     {
          int j = 0;
          for(float x = startX; x <= endX; x += m_nCellSpacing)
          {
               // вычисляем правильный индекс в буфере вершин
               // и карте высот на основании счетчиков вложенных циклов
               int index = i * m_nNumVertsPerRow + j;

               v[index] = VertexXYZCUV(
                                   (float)x,
                                   (float)m_vHeightMap[index],
                                   (float)z,
								   dwVertColor,
                                   (float)j * uCoordIncrementSize,
                                   (float)i * vCoordIncrementSize);
               j++; // следующий столбец
          }
          i++; // следующая строка
     }
	 SetVertex();
	return true;
}

bool DXVTTerrain::Indices()
{

	CreateIndexBuffer32(m_nNumTriangles * 3 * sizeof(unsigned long));


	unsigned long * indices = 0;
	GetIndex((void**)&indices);

	// index to start of a group of 6 indices that describe the
	// two triangles that make up a quad
	int baseIndex = 0;

	// loop through and compute the triangles of each quad
	for(int i = 0; i < m_nNumCellsPerCol; i++)

	{
		for(int j = 0; j < m_nNumCellsPerRow; j++)
		{
               indices[baseIndex]     = (i+1) * m_nNumVertsPerRow + j;
               indices[baseIndex + 1] = i * m_nNumVertsPerRow + j;
                indices[baseIndex + 2] = i * m_nNumVertsPerRow + j + 1;
               indices[baseIndex + 3] = (i+1) * m_nNumVertsPerRow + j;
               indices[baseIndex + 4] = i * m_nNumVertsPerRow + j + 1;
               indices[baseIndex + 5] = (i+1) * m_nNumVertsPerRow + j + 1;
			baseIndex += 6;
		}
	}

	SetIndex();

	return true;
}

void DXVTTerrain::SetParam(int nNumCellsPerRow,int nNumCellsPerCol,int nCellSpacing)
{
m_nNumCellsPerRow = nNumCellsPerRow;
m_nNumCellsPerCol = nNumCellsPerCol;
m_nNumVertsPerRow = nNumCellsPerRow + 1;
m_nNumVertsPerCol = nNumCellsPerCol + 1;
m_nCellSpacing = nCellSpacing;
m_nWidth = m_nNumCellsPerRow * m_nCellSpacing;
m_nDepth = m_nNumCellsPerCol * m_nCellSpacing;
m_nNumVertices = m_nNumVertsPerRow * m_nNumVertsPerCol;
m_nNumTriangles = m_nNumCellsPerRow * m_nNumCellsPerCol * 2;
m_vHeightMap.resize(m_nNumVertices+1);
}

int DXVTTerrain::GetNumTriangles()
{
	return m_nNumTriangles;
}

void DXVTTerrain::SetTexture(DXVTTexture * pDXVTTexture)
{
D3DSURFACE_DESC texDesc = *pDXVTTexture->GetDesc();
D3DLOCKED_RECT TexRect = pDXVTTexture->GetRect();
DWORD* imageData = (DWORD*)TexRect.pBits;
	for(int i = 0; i < texDesc.Height; i++)
	{
		for(int j = 0; j < texDesc.Width; j++)
		{
			int index = i * TexRect.Pitch / 4 + j;

			D3DXCOLOR c( imageData[index] );

			c *= GetShadeElement(i, j);

			imageData[index] = (D3DCOLOR)c;
		}
	}
	pDXVTTexture->SetRect();
}

float DXVTTerrain::GetHeightMapElement(int nRow,int nCol)
{
	return m_vHeightMap[nRow * m_nNumVertsPerRow + nCol];
}
float DXVTTerrain::GetHeightMapElement(int nIndex)
{
	return m_vHeightMap[nIndex];
}
void DXVTTerrain::SetHeightMapElement(int nIndex,float fValue)
{
	m_vHeightMap[nIndex] = fValue;
	GetVertex((void**)&v);
	v[nIndex]._y = fValue;
	SetVertex();
}
void DXVTTerrain::SetHeightMapElement(int nRow,int nCol,float fValue)
{
    m_vHeightMap[nRow * m_nNumVertsPerRow + nCol] = fValue;
	GetVertex((void**)&v);
	v[nRow * m_nNumVertsPerRow + nCol]._y = fValue;
	SetVertex();
}
void DXVTTerrain::SetHeightMapElement(float nX,float nZ,float fValue)
{
	GetVertex((void**)&v);
	for(int index = 0;index < m_nNumVertsPerRow*m_nNumVertsPerCol;index++)
		if(v[index]._x == nX && v[index]._z == nZ)
		{
	v[index]._y = fValue;
		}
	SetVertex();
}

void DXVTTerrain::ReadRAWData(char * szFileName)///vector heightmap посмотреть !!!
{
FILE * file;
char * szBuffer;
file = fopen(szFileName,"r");
long size;
int rowsize = 0;
char c;
while((c = fgetc(file)) != '\n')
{
	if(c == '.')rowsize++;
}
fseek(file,0,SEEK_END);
size = ftell(file);
fseek(file,0,SEEK_SET);
szBuffer = new char[size];
for(int i = 0;i<size;i++)
szBuffer[i] = 0;
fread((void*)szBuffer,size,sizeof(char),file);
char *szFloat = new char[MAX_FLOAT_LEN];
int i = 0;
while(*(szBuffer) != EOF && *(szBuffer) != '\0')
{
int nNumPart = 0;
	while(*(szBuffer) != ' ')
	{
	*(szFloat++) = *(szBuffer++);
	nNumPart++;
	}
	*szFloat = '\0';
	szFloat -= nNumPart;
	float fValue = atof(szFloat);
	m_vHeightMap.push_back(fValue);
	szBuffer++;
}
m_nNumVertsPerRow = rowsize;
m_nNumVertsPerCol = m_nNumVertsPerRow;
m_nCellSpacing = 1;//TODO : Change this !!!
m_nNumCellsPerRow = m_nNumVertsPerRow - 1;
m_nNumCellsPerCol = m_nNumVertsPerCol - 1;
m_nWidth = m_nNumCellsPerRow * m_nCellSpacing;
m_nDepth = m_nNumCellsPerCol * m_nCellSpacing;
m_nNumVertices = m_nNumVertsPerRow * m_nNumVertsPerCol;
m_nNumTriangles = m_nNumCellsPerRow * m_nNumCellsPerCol * 2;
}

void DXVTTerrain::WriteRAWData(char * szFileName)
{
FILE * m_File;
String::StrCat(szFileName,".raw");
m_File = fopen(szFileName,"w");
for(int i = 0;i<m_nNumVertsPerRow;i++)
{
for(int j = 0;j<m_nNumVertsPerCol;j++)
{
fprintf(m_File,"%.2f ",GetHeightMapElement(i,j));
}
if(i != (m_nNumVertsPerRow-1))
fprintf(m_File,"\n");
}
fclose(m_File);
}

float DXVTTerrain::GetShadeElement(int nVertRow, int nVertCol)
{
	float heightA , heightB , heightC;
	heightA = heightB = heightC = 0;
	heightA = GetHeightMapElement(nVertRow,   nVertCol);
	heightB = GetHeightMapElement(nVertRow,   nVertCol+1);
if(nVertRow != m_nNumVertsPerRow-1)
	heightC = GetHeightMapElement(nVertRow+1, nVertCol);
else 
    heightC = GetHeightMapElement(nVertRow-1, nVertCol);
	D3DXVECTOR3 M1(m_nCellSpacing, heightB - heightA, 0.0f);
	D3DXVECTOR3 M2(0.0f,heightC - heightA, -m_nCellSpacing);

	D3DXVECTOR3 N;
	D3DXVec3Cross(&N, &M1, &M2);
	D3DXVec3Normalize(&N, &N);

	float Mul = D3DXVec3Dot(&N, m_pvLightDirection);

	if(Mul < 0.0f)
		Mul = 0.4f;

	return Mul;

}

float DXVTTerrain::GetWidth()
{
	return (float)m_nWidth;
}

float DXVTTerrain::GetDepth()
{
	return (float)m_nDepth;
}

void DXVTTerrain::SetLightDirection(D3DXVECTOR3 * pLightDirection)
{
	m_pvLightDirection = pLightDirection;
}

int DXVTTerrain::GetCellspacing()
{
	return m_nCellSpacing;
}

VertexXYZCUV * DXVTTerrain::GetVertexXYZCUV()
{
	return v;
}

int g_aIndex[MAX_ELEM_LOCAL];

int *DXVTTerrain::GetTraceRadius(D3DXVECTOR3 *pPickRay,int nTerrainLevel,float fRadius,D3DXVECTOR3 * vCenter,int &nNumVertFound)
{
int nFound = 0;
for(int i=0;i<MAX_ELEM_LOCAL;i++)
g_aIndex[i] = -1;
for(int index = 0;index < m_nNumVertsPerRow*m_nNumVertsPerCol;index++)
{
if(EqFloat(pPickRay->x,v[index]._x,(float)sqrt(pow((float)m_nCellSpacing,2) + pow((float)m_nCellSpacing,2))/2) && EqFloat(pPickRay->z,v[index]._z,(float)sqrt(pow((float)m_nCellSpacing,2) + pow((float)m_nCellSpacing,2))/2))
{
vCenter->x = v[index]._x;
vCenter->y = v[index]._y;
vCenter->z = v[index]._z;
}
if((pow(v[index]._x - pPickRay->x,2) + pow(v[index]._z - pPickRay->z,2)) < pow(fRadius,2))
{
g_aIndex[nFound] = index;
nFound++;
}
}
if(nFound != 0)
{
nNumVertFound = nFound;
return g_aIndex;
}
else
{
	return NULL;
}
}

D3DXVECTOR3 *DXVTTerrain::GetRayTrace(DXVTCamera::PickRay * pPickRay,int nTerrainLevel)
{
	float x = pPickRay->Origin.x - (((pPickRay->Origin.y - nTerrainLevel)*pPickRay->Direction.x)/pPickRay->Direction.y);
	float y = nTerrainLevel;
	float z = pPickRay->Origin.z - (((pPickRay->Origin.y - nTerrainLevel)*pPickRay->Direction.z)/pPickRay->Direction.y); 
	return &D3DXVECTOR3(x,y,z);
}

VertexXYZCUV * DXVTTerrain::FindPickNode(DXVTCamera::PickRay * pPickRay,int nTerrainLevel)
{
	float x = pPickRay->Origin.x - (((pPickRay->Origin.y - nTerrainLevel)*pPickRay->Direction.x)/pPickRay->Direction.y);
	float y = nTerrainLevel;
	float z = pPickRay->Origin.z - (((pPickRay->Origin.y - nTerrainLevel)*pPickRay->Direction.z)/pPickRay->Direction.y); 
	//FindNode(m_pFirstQuad,x,z,y);
	return VQuadTree<VertexXYZCUV>::m_pStaticElement;
}*/
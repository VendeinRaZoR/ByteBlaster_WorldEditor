#include "VTGL_Terrain.h"

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

VTGL_Terrain::VTGL_Terrain(VTGL_Device *pVTGLDevice,int nNumCellsPerRow,int nNumCellsPerCol,int nCellSpacing)
{
m_pVTGLDevice = pVTGLDevice;
m_pVTGLTerrain = new VTGL_Geometry(pVTGLDevice->GetBaseDevice());
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

VTGL_Terrain::VTGL_Terrain(VTGL_Device *pVTGLDevice)
{
	m_pVTGLDevice = pVTGLDevice;
}

VTGL_Terrain::~VTGL_Terrain()
{

}

void VTGL_Terrain::SetHeightMap(int nHeight)
{
	for(int i = 0; i < m_nNumVertices; i++)
	m_vHeightMap[i] = nHeight;
}

bool VTGL_Terrain::SetVertices(DWORD dwVertColor)
{
     //CreateVertexBuffer(m_nNumVertices * sizeof(VertexXYZCUV),VertexXYZCUV::FVF,m_nNumVertices);
m_pVTGLTerrain->CreateVertexBuffer(sizeof(VertexXYZC),m_nNumVertices,"Position+Color");//ѕока что Position+Color ))
	// coordinates to start generating vertices at
	int startX = -m_nWidth / 2;
	int startZ =  m_nDepth / 2;

	// coordinates to end generating vertices at
	int endX =  m_nWidth / 2;
	int endZ = -m_nDepth / 2;

	// compute the increment size of the texture coordinates
	// from one vertex to the next.
	//float uCoordIncrementSize = 1.0f / (float)(m_nNumCellsPerRow);
	//float vCoordIncrementSize = 1.0f / (float)(m_nNumCellsPerCol);

	//GetVertex((void**)&v);
	v = (VertexXYZC*)m_pVTGLTerrain->MapVertex();

     int i = 0;
     for(float z = startZ; z >= endZ; z -= m_nCellSpacing)
     {
          int j = 0;
          for(float x = startX; x <= endX; x += m_nCellSpacing)
          {
               // вычисл€ем правильный индекс в буфере вершин
               // и карте высот на основании счетчиков вложенных циклов
               int index = i * m_nNumVertsPerRow + j;

               v[index] = VertexXYZC(
                                   (float)x,
                                   (float)m_vHeightMap[index],
                                   (float)z,
								   dwVertColor);
               j++; // следующий столбец
          }
          i++; // следующа€ строка
     }
	 m_pVTGLTerrain->UnMapVertex();
	return true;
}

bool VTGL_Terrain::SetIndices()
{

	//CreateIndexBuffer32(m_nNumTriangles * 3 * sizeof(unsigned long));
	m_pVTGLTerrain->CreateIndexBuffer32(m_nNumTriangles * 3);

	DWORD * indices = 0;
	//GetIndex((void**)&indices);
	indices = (DWORD*)m_pVTGLTerrain->MapIndex();
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
	m_pVTGLTerrain->UnMapIndex();
	return true;
}

void VTGL_Terrain::SetCells(int nNumCellsPerRow,int nNumCellsPerCol,int nCellSpacing)
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

int VTGL_Terrain::GetNumTriangles()
{
	return m_nNumTriangles;
}

/*void DXVTTerrain::SetTexture(DXVTTexture * pDXVTTexture)
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
}*/

float VTGL_Terrain::GetHeightMapElement(int nRow,int nCol)
{
	return m_vHeightMap[nRow * m_nNumVertsPerRow + nCol];
}
float VTGL_Terrain::GetHeightMapElement(int nIndex)
{
	return m_vHeightMap[nIndex];
}
void VTGL_Terrain::SetHeightMapElement(int nIndex,float fValue)
{
	m_vHeightMap[nIndex] = fValue;
	//GetVertex((void**)&v);
	v[nIndex]._y = fValue;
	//SetVertex();
}
void VTGL_Terrain::SetHeightMapElement(int nRow,int nCol,float fValue)
{
    m_vHeightMap[nRow * m_nNumVertsPerRow + nCol] = fValue;
	//GetVertex((void**)&v);
	v[nRow * m_nNumVertsPerRow + nCol]._y = fValue;
	//SetVertex();
}
void VTGL_Terrain::SetHeightMapElement(float nX,float nZ,float fValue)
{
	//GetVertex((void**)&v);
	for(int index = 0;index < m_nNumVertsPerRow*m_nNumVertsPerCol;index++)
		if(v[index]._x == nX && v[index]._z == nZ)
		{
	v[index]._y = fValue;
		}
	//SetVertex();
}

void VTGL_Terrain::ReadRAWData(char * szFileName)///vector heightmap посмотреть !!!
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

void VTGL_Terrain::WriteRAWData(char * szFileName)
{
FILE * m_File;
strcat(szFileName,".raw");
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

void VTGL_Terrain::Draw()
{
	m_pVTGLTerrain->Draw(m_nNumTriangles);
}
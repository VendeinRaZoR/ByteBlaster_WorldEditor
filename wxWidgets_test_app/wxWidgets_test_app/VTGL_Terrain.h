#include "VTGL_Geometry.h"

class VTGL_Terrain //: public DXVTBaseGeometry
{
	VTGL_Device * m_pVTGLDevice;
	VTGL_Geometry * m_pVTGLTerrain;
	int m_nNumVertsPerRow,m_nNumVertsPerCol,m_nCellSpacing;
	int m_nNumCellsPerRow;
	int m_nNumCellsPerCol;
	int m_nWidth;
	int m_nDepth;
	int m_nNumVertices;
	int m_nNumTriangles;
	std::vector<float>m_vHeightMap;
	//VTVector3D *m_pvLightDirection;
private:
		VertexXYZC* v;
public:
	VTGL_Terrain(VTGL_Device *pVTGLDevice,int nNumVertsPerRow,int nNumVertsPerCol,int nCellSpacing);
	VTGL_Terrain(VTGL_Device *pVTGLDevice);
	~VTGL_Terrain();
	void SetCells(int nNumCellsPerRow,int nNumCellsPerCol,int nCellSpacing);
	bool SetVertices(DWORD dwVertColor);
	bool SetIndices();
	void SetHeightMap(int nHeight);
	int GetNumTriangles();
	int GetCellspacing();
public:
	//void SetTexture(DXVTTexture * pDXVTTexture);
	void ReadRAWData(char * szFileName);
	void WriteRAWData(char * szFileName);
public:
	float GetHeightMapElement(int nRow,int nCol);
	float GetHeightMapElement(int nIndex);
	void SetHeightMapElement(int nRow,int nCol,float fValue);
	void SetHeightMapElement(int nIndex,float fValue);
	void SetHeightMapElement(float nX,float nY,float fValue);
	void Draw();
	//float GetShadeElement(int nVertRow, int nVertCol);
	//VertexXYZCUV * GetVertexXYZCUV();
	//float GetWidth();
	//float GetDepth();
//VertexXYZCUV * FindPickNode(DXVTCamera::PickRay * pPickRay,int nTerrainLevel);
public:
	//int * GetTraceRadius(D3DXVECTOR3 *pPickRay,int nTerrainLevel,float fRadius,D3DXVECTOR3 * vCenter,int &nNumVertFound);
public:
	//void SetLightDirection(D3DXVECTOR3 * pLightDirection);
	//D3DXVECTOR3 *GetRayTrace(DXVTCamera::PickRay * pPickRay,int nTerrainLevel);
};
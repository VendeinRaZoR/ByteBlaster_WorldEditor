//#include "BBMain.h"

/*
class BBEditor : public BBMain
{
	DXVTBaseGeometry *BasePrimitive;
	DXVTBaseGeometry *RayLine;
	DXVTBaseMaterial * BaseMaterial;
	DXVTBaseLight * BaseLight;
	DXVTTerrain * m_pTerrain;
	DXVTTexture * m_pTerrainTexture;
	DXVTCamera::PickRay *m_pPickRay;
public:
	BBEditor();
	~BBEditor();
	void Setup();
	void Render(float fTimeDelta);
	void RenderAxis();
};*/
#ifndef _BBEDITOR_H_
#define _BBEDITOR_H_


struct TerrainParam
{
int nHeight;
int nWidth;
int nDepth;
int nCellSpace;
};


#endif
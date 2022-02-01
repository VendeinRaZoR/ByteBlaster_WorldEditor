#ifndef _RENDERWINDOW_H_
#define _RENDERWINDOW_H_
#include "TestWindow.h"
#include "DXVT_Geometry.h"
#include "DXVT_Material.h"
#include "DXVT_Light.h"
#include "DXVT_Font.h"
#include "DXVT_Camera.h"
#include "BBEditor.h"


#define SCREEN_X 640
#define SCREEN_Y 480

bool g_bWireframe = false;

struct Vertex
{
     Vertex(){}
     Vertex(float x, float y, float z,DWORD dwColor)
     {
          _x = x; _y = y; _z = z;_dwColor = dwColor;
     }
     float _x, _y, _z;
     DWORD _dwColor;
     static const DWORD FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE;
};

int FPS;
float g_fTimeElapsed;

int CalcFPS(float fTimeDelta)
{
     FPS++;
     g_fTimeElapsed += fTimeDelta;

     if(g_fTimeElapsed >= 1.0f)
     {
		 int _FPS = FPS;
		 float _fTimeElapsed = g_fTimeElapsed;
          return _FPS / _fTimeElapsed;
	 }
     
}

float fDetailDistance = 100.0f;

class CRenderWindow : public VSDIWindow
{
	TerrainParam *m_pTerrainParam;
	DXVTDevice *m_DXVTDevice;
	VEventHandler m_EventHandler;
	VEventHandler m_EventHandlerParent;
	DXVTBaseGeometry *BasePrimitive;
	DXVTBaseGeometry *WorldAxis;
	DXVTBaseGeometry *PickCenter;
	DXVTBaseMaterial * BaseMaterial;
	DXVTBaseLight * BaseLight;
	DXVTFont * m_pDXVTFont;
	DXVTCamera * m_pCamera;
	DXVTTerrain * m_pTerrain;
	DXVTTexture * m_pTerrainTexture;
	DXVTCamera::PickRay *m_pPickRay;
	char * m_szFPS;
	int m_nHeightMap;
	bool m_bWireFrame;
	Vertex * WorldAxisVert;
	ID3DXMesh * PickCubeMesh;
	float m_fHeight;
	float m_fBrushRadius;
	float m_fBrushStraight;
	float m_fCameraSpeed;
	int m_nTerrainHeight;
	VQuadTree<VertexXYZCUV> * m_pFirstQuad;
public:
	CRenderWindow(VBaseWindow * pParentWindow):VSDIWindow("Render Window",*pParentWindow,1,SCREEN_SIZE_X/2,SCREEN_SIZE_Y/2,SCREEN_X,SCREEN_Y,WINDOW_STYLE::dwChildWindow,WS_EX_TOOLWINDOW)
	{
	m_fHeight = 0.0f;
	m_fBrushRadius = 0.0f;
    m_fBrushStraight = 0.0f;
	m_fCameraSpeed = 0.0f;
	m_bWireFrame = false;
	m_szFPS = new char[256];
	DXVT_Param dxvtParams;
	dxvtParams.bWindowed = true;
	dxvtParams.D3D_AutoDepthStencilFormat = D3DFMT_D16;
	dxvtParams.D3D_DevType = D3DDEVTYPE_HAL;
    dxvtParams.D3D_SwapEffect = D3DSWAPEFFECT_DISCARD;
	m_EventHandler = VEventHandler(this);
	m_EventHandlerParent = VEventHandler(pParentWindow);
	m_DXVTDevice = new DXVTDevice(this);
	m_DXVTDevice->Create(&dxvtParams,SCREEN_X,SCREEN_Y);
	PickCenter = new DXVTBaseGeometry(m_DXVTDevice);
	BasePrimitive = new DXVTBaseGeometry(m_DXVTDevice);
	WorldAxis = new DXVTBaseGeometry(m_DXVTDevice);
	m_pTerrainTexture = new DXVTTexture(m_DXVTDevice);
	BaseLight = new DXVTBaseLight(m_DXVTDevice);
	m_pCamera = new DXVTCamera(m_DXVTDevice);
	m_pPickRay = new DXVTCamera::PickRay(m_DXVTDevice);
	m_pCamera->SetViewMatrix(0.0f,10.0f,0.0f);
	WorldAxis->CreateVertexBuffer(6*sizeof(Vertex),Vertex::FVF,6);
	WorldAxis->GetVertex((void**)&WorldAxisVert);
	 WorldAxisVert[0] = Vertex(0.0f,0.0f,0.0f,0x00000000);
	 WorldAxisVert[1] = Vertex(1.0f,0.0f,0.0f,0x00000000);
	 WorldAxisVert[2] = Vertex(0.0f,0.0f,0.0f,0x00000000);
	 WorldAxisVert[3] = Vertex(0.0f,0.0f,1.0f,0x00000000);
	 WorldAxisVert[4] = Vertex(0.0f,0.0f,0.0f,0x00000000);
	 WorldAxisVert[5] = Vertex(0.0f,1.0f,0.0f,0x00000000);
    WorldAxis->SetVertex();
	///////////////////////////////////////////////////////
	CreatePickCubeArray();
	///////////////////////////////////////////////////////
m_EventHandlerParent.AddEvent(WM_COMMAND);
m_EventHandler.AddEvent(WM_PARAM);
	///////////////////////////////////////////
	m_pDXVTFont = new DXVTFont(m_DXVTDevice,"Times New Roman",12);
	m_pDXVTFont->CreateText();
	 m_pCamera->SetProjectionMatrix(D3DX_PI/2,1000.0f);
	 (*m_DXVTDevice)->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_ANISOTROPIC);
	(*m_DXVTDevice)->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC);
	(*m_DXVTDevice)->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_ANISOTROPIC);
	 ///////////////////////////////////////////////////////
	m_EventHandler.CallStatic();
	}

	~CRenderWindow(){}

	void StaticMessageCallback() 
	{
	}

	void EventMessageCallback()
	{
	if(this->GetData("OpenFile"))
	{
	m_pTerrain = new DXVTTerrain(m_DXVTDevice);
	m_pTerrain->ReadRAWData((char*)this->GetData("OpenFile"));
	m_pTerrain->SetLightDirection(&D3DXVECTOR3(1.0f,1.0f,0.0f));
	m_pTerrain->Vertices(0x00CC9933);
	m_pTerrain->Indices();
	//m_pTerrainTexture->Load("desert.bmp");
	//m_pTerrain->SetTexture(m_pTerrainTexture);
	}
	if(this->GetData("SaveFile"))
	m_pTerrain->WriteRAWData((char*)this->GetData("SaveFile"));
	if(this->GetData("CamSpeed"))
    m_fCameraSpeed = (*(int*)this->GetData("CamSpeed"))/5.0f;
	if(this->GetData("Radius"))
	m_fBrushRadius = (*(int*)this->GetData("Radius"))/10.0f;
	if(this->GetData("Straight"))
	m_fBrushStraight = (*(int*)this->GetData("Straight"))/10.0f;
	if(this->GetData("GridMode"))
	m_bWireFrame = this->GetData("GridMode");
	if(m_pTerrainParam = (TerrainParam*)this->GetData("TerrainParam")) 
		{
	m_pTerrain = new DXVTTerrain(m_DXVTDevice,m_pTerrainParam->nWidth,m_pTerrainParam->nDepth,m_pTerrainParam->nCellSpace);
	 m_pTerrain->SetHeightMap(m_pTerrainParam->nHeight);
	 m_nTerrainHeight = m_pTerrainParam->nHeight;
	 m_pTerrain->SetLightDirection(&D3DXVECTOR3(1.0f,1.0f,0.0f));
	 m_pTerrain->Vertices(0x00CC9933);
	 m_pFirstQuad = FirstNode(m_pTerrain->GetVertexXYZCUV());
	 PushTree(m_pFirstQuad,0,m_pTerrain->GetWidth()/m_pTerrain->GetCellspacing(),m_pTerrain->GetDepth()/m_pTerrain->GetCellspacing());///As Linear Array not Matrix !!!
	 m_pTerrain->Indices();
	 m_pTerrainTexture->Load("desert.bmp");
	 m_pTerrain->SetTexture(m_pTerrainTexture);
	//m_pTerrain->SetParam(2,2,m_pTerrainParam->nWidth/2);
	m_pTerrain->Indices();

		}
	}



	void CreatePickCubeArray() ////////////TODO : Чтение из файла и диалоговое окно "Файл - Открыть..."
	{
	    Vertex* vertices = 0;
	BasePrimitive->CreateVertexBuffer(8*sizeof(Vertex),Vertex::FVF,8);
	BasePrimitive->GetVertex((void**)&vertices);
	///////////////////////////////////////////
     vertices[0] = Vertex(-1.0f, -1.0f, -1.0f,0xff00aa00);
     vertices[1] = Vertex(-1.0f,  1.0f, -1.0f,0xff00aa00);
     vertices[2] = Vertex( 1.0f,  1.0f, -1.0f,0xff00aa00);
     vertices[3] = Vertex( 1.0f, -1.0f, -1.0f,0xff00aa00);
     vertices[4] = Vertex(-1.0f, -1.0f,  1.0f,0xff00aa00);
     vertices[5] = Vertex(-1.0f,  1.0f,  1.0f,0xff00aa00);
     vertices[6] = Vertex( 1.0f,  1.0f,  1.0f,0xff00aa00);
     vertices[7] = Vertex( 1.0f, -1.0f,  1.0f,0xff00aa00);


	 BasePrimitive->SetVertex();
	 WORD * indices = 0;
	 BasePrimitive->CreateIndexBuffer16(36*sizeof(WORD));
 	 BasePrimitive->GetIndex((void**)&indices);
     indices[0]  = 0; indices[1]  = 1; indices[2]  = 2;
     indices[3]  = 0; indices[4]  = 2; indices[5]  = 3;

     // задняя грань
     indices[6]  = 4; indices[7]  = 6; indices[8]  = 5;
     indices[9]  = 4; indices[10] = 7; indices[11] = 6;

     // левая грань
     indices[12] = 4; indices[13] = 5; indices[14] = 1;
     indices[15] = 4; indices[16] = 1; indices[17] = 0;

     // правая грань
     indices[18] = 3; indices[19] = 2; indices[20] = 6;
     indices[21] = 3; indices[22] = 6; indices[23] = 7;

     // верх
     indices[24] = 1; indices[25] = 5; indices[26] = 6;
     indices[27] = 1; indices[28] = 6; indices[29] = 2;

     // низ
     indices[30] = 4; indices[31] = 0; indices[32] = 3;
     indices[33] = 4; indices[34] = 3; indices[35] = 7;

	 BasePrimitive->SetIndex();
	 Vertex* pickvertices = 0;
	 PickCenter->CreateVertexBuffer(8*sizeof(Vertex),Vertex::FVF,8);
PickCenter->GetVertex((void**)&pickvertices);
 pickvertices[0] = Vertex(-1.0f, -1.0f, -1.0f,0xffaa0000);
     pickvertices[1] = Vertex(-1.0f,  1.0f, -1.0f,0xffaa0000);
     pickvertices[2] = Vertex( 1.0f,  1.0f, -1.0f,0xffaa0000);
     pickvertices[3] = Vertex( 1.0f, -1.0f, -1.0f,0xffaa0000);
     pickvertices[4] = Vertex(-1.0f, -1.0f,  1.0f,0xffaa0000);
     pickvertices[5] = Vertex(-1.0f,  1.0f,  1.0f,0xffaa0000);
     pickvertices[6] = Vertex( 1.0f,  1.0f,  1.0f,0xffaa0000);
     pickvertices[7] = Vertex( 1.0f, -1.0f,  1.0f,0xffaa0000);


	 PickCenter->SetVertex();
	 WORD * pickindices = 0;
	 PickCenter->CreateIndexBuffer16(36*sizeof(WORD));
 	 PickCenter->GetIndex((void**)&pickindices);
     pickindices[0]  = 0; pickindices[1]  = 1; pickindices[2]  = 2;
     pickindices[3]  = 0; pickindices[4]  = 2; pickindices[5]  = 3;

     // задняя грань
     pickindices[6]  = 4; pickindices[7]  = 6; pickindices[8]  = 5;
     pickindices[9]  = 4; pickindices[10] = 7; pickindices[11] = 6;

     // левая грань
     pickindices[12] = 4; pickindices[13] = 5; pickindices[14] = 1;
     pickindices[15] = 4; pickindices[16] = 1; pickindices[17] = 0;

     // правая грань
     pickindices[18] = 3; pickindices[19] = 2; pickindices[20] = 6;
     pickindices[21] = 3; pickindices[22] = 6; pickindices[23] = 7;

     // верх
     pickindices[24] = 1; pickindices[25] = 5; pickindices[26] = 6;
     pickindices[27] = 1; pickindices[28] = 6; pickindices[29] = 2;

     // низ
     pickindices[30] = 4; pickindices[31] = 0; pickindices[32] = 3;
     pickindices[33] = 4; pickindices[34] = 3; pickindices[35] = 7;

	 PickCenter->SetIndex();
	}

		void RenderMessageCallback(float fTimeDelta)//Render !!!
		{
		m_DXVTDevice->Clear(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,0xFFFFFFFF);
		m_DXVTDevice->BeginRender();
		D3DXMATRIX World;
		D3DXMatrixIdentity(&World);
		(*m_DXVTDevice)->SetTransform(D3DTS_WORLD,&World);
		(*m_DXVTDevice)->SetRenderState(D3DRS_LIGHTING,false);
		POINT p;
		GetCursorPos(&p);
		ScreenToClient(*this,&p);
		m_pPickRay->Calculate(p.x,p.y);
		D3DXMATRIX mInverse;
		D3DXMatrixInverse(&mInverse,0,&m_pCamera->GetViewMatrix());
		m_pPickRay->Transform(&mInverse);
		D3DXMATRIX m_CubePick;
		D3DXMATRIX m_CubePickScale;
		D3DXMATRIX m_RayPick;
		D3DXMATRIX m_RayPickScale;
	    D3DXVECTOR3 RayTrace = *m_pTerrain->GetRayTrace(m_pPickRay,0);
		D3DXVECTOR3 vCenter;
		int nNumVert;
		int *Index = 0;
		if(Index = m_pTerrain->GetTraceRadius(&RayTrace,m_pTerrainParam->nHeight,m_fBrushRadius,&vCenter,nNumVert))
		{
	for(int i=0;i<nNumVert;i++)
	{
		D3DXMatrixTranslation(&m_CubePick,m_pTerrain->GetVertexXYZCUV()[Index[i]]._x,m_pTerrain->GetVertexXYZCUV()[Index[i]]._y,m_pTerrain->GetVertexXYZCUV()[Index[i]]._z);
        D3DXMatrixScaling(&m_CubePickScale,0.2f,1.0f,0.2f);
	    m_CubePickScale *= m_CubePick;
	    (*m_DXVTDevice)->SetTransform(D3DTS_WORLD,&m_CubePickScale);
		BasePrimitive->Draw(12,"Triangle");
	}
	 if(GetAsyncKeyState(VK_LBUTTON))
	 {
		 float h = 0.00000f;
		 float hz = 0.00000f;
		 float hk = 0.0f;
		 for(int i=0;i < nNumVert;i++)
	{
		h = (cos((abs(m_pTerrain->GetVertexXYZCUV()[Index[i]]._x - RayTrace.x)*D3DX_PI/ m_fBrushRadius)) + 1.0f)*m_fBrushStraight * 0.5;
		hz = (cos((abs(m_pTerrain->GetVertexXYZCUV()[Index[i]]._z - RayTrace.z)*D3DX_PI) / m_fBrushRadius) + 1.0f)*m_fBrushStraight * 0.5;
		hk = h*hz;
		m_pTerrain->SetHeightMapElement(Index[i],m_pTerrain->GetHeightMapElement(Index[i])+hk*0.01);
	} 
	 }
	 	 if(GetAsyncKeyState(VK_RBUTTON))
	 {
		 float h = 0.00000f;
		 float hz = 0.00000f;
		 float hk = 0.0f;
		 for(int i=0;i < nNumVert;i++)
	{
		h = (cos((abs(m_pTerrain->GetVertexXYZCUV()[Index[i]]._x - RayTrace.x)*D3DX_PI/ m_fBrushRadius)) + 1.0f) *m_fBrushStraight* 0.5;
		hz = (cos((abs(m_pTerrain->GetVertexXYZCUV()[Index[i]]._z - RayTrace.z)*D3DX_PI) / m_fBrushRadius) + 1.0f) *m_fBrushStraight* 0.5;
		hk = h*hz;
		m_pTerrain->SetHeightMapElement(Index[i],m_pTerrain->GetHeightMapElement(Index[i])-hk*0.01);
	} 
	 }
		}
	 D3DXMatrixTranslation(&m_RayPick,RayTrace.x,vCenter.y,RayTrace.z);//TODO : Только в плоскости ландшафта !!!
		D3DXMatrixScaling(&m_RayPickScale,0.3f,0.3f,0.3f);
		m_RayPickScale *= m_RayPick;
		(*m_DXVTDevice)->SetTransform(D3DTS_WORLD,&m_RayPickScale);
		PickCenter->Draw(12,"Triangle");
		/////////////////////////////////////////////
		/////////////////////////////////////////////
		/////////////////////////////////////////////
		/////////////Frustum Culling/////////////////
		/////////////////////////////////////////////
		/////////////////////////////////////////////
		/////////////////////////////////////////////
		VertexXYZCUV *TerrainVertex = m_pTerrain->GetVertexXYZCUV();
		m_pTerrain->GetVertex((void**)&TerrainVertex);
		if(GetAsyncKeyState(VK_UP))
		{
		//	TerrainVertex[0]._x
		}
		m_pTerrain->SetVertex();
		/////////////////////////////////////////////
		/////////////////////////////////////////////
		/////////////////////////////////////////////
		/////////////////////////////////////////////
	    (*m_DXVTDevice)->SetTransform(D3DTS_WORLD,&World);
		sprintf(m_szFPS,"FPS : %d",CalcFPS(fTimeDelta));
		m_pDXVTFont->DrawText(10.0f,10.0f,0xffff0000,m_szFPS,0);
	 if(GetKeyState(VK_SPACE))
	    m_pCamera->Build(this,fTimeDelta,m_fCameraSpeed);
		if(!m_bWireFrame)
		{
	m_pTerrainTexture->Set();
	m_pTerrain->Draw(m_pTerrain->GetNumTriangles(),"Triangle");
		}
		else
		{
		(*m_DXVTDevice)->SetRenderState(D3DRS_FILLMODE,D3DFILL_WIREFRAME);
		(*m_DXVTDevice)->SetTexture(0,0);
		m_pTerrain->Draw(m_pTerrain->GetNumTriangles(),"Triangle");
		(*m_DXVTDevice)->SetRenderState(D3DRS_FILLMODE,D3DFILL_SOLID);
		}
		(*m_DXVTDevice)->SetRenderState(D3DRS_LIGHTING,true);
		(*m_DXVTDevice)->SetTransform(D3DTS_WORLD,&World);
		 (*m_DXVTDevice)->SetRenderState(D3DRS_ZENABLE,false);
	    WorldAxis->Draw(3,"Line"); 
		(*m_DXVTDevice)->SetRenderState(D3DRS_ZENABLE,true);
	    m_DXVTDevice->EndRender();
		}

//////////////////////////////
		void OnDestroy()
		{
	EnableWindow(GetDlgItem(*m_WindowManager.GetWindowByName("ToolBox"),IDC_SLIDER2), false);
	EnableWindow(GetDlgItem(*m_WindowManager.GetWindowByName("ToolBox"),IDC_SLIDER1), false);
	EnableWindow(GetDlgItem(*m_WindowManager.GetWindowByName("ToolBox"),IDC_SLIDER3), false);
			m_WindowManager.DeleteWindow(this);
			DestroyWindow(*this);
		}
};

#endif
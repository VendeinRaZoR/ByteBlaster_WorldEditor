#include "CRenderWindow.h"
#include <d3d9.h>
#include "VTGL_Camera.h"
#include "VTGL_Terrain.h"

wxBEGIN_EVENT_TABLE(CRenderWindow, wxWindow) 
EVT_IDLE(OnIdle) 
wxEND_EVENT_TABLE() 

float fCameraSpeed = 10;

//ONRENDER(CRenderWindow,OnIdle);

void CRenderWindow::OnScroll(wxScrollEvent& event)
{
	fCameraSpeed = (float)(event.GetPosition());
	//printf("\n%.2f",fCameraSpeed);
}


	void CRenderWindow::OnExit()
	{
		Close(true);
	}
VTGL_Geometry * Mesh;
VTGL_Geometry * Axis;//Оси
VTGL_Camera VTGLCamera;
VTGL_Terrain * g_pVTGLTerrain;
	void CRenderWindow::OnRender(float fTimeDelta)
	{
	if(m_pGraphDevice)
	{
		m_pGraphDevice->BeginRender();
		m_pGraphDevice->Clear(m_pGraphDevice->vtglCLEARCOLOR() | m_pGraphDevice->vtglCLEARDEPTH(),wxColor("White"));
		//Render...
		static float angle = 0 ;
		angle += fTimeDelta*50;
	m_pGraphDevice->SetMatrixMode("World");
	VTMatrix4 m2;
	VTMatrix4 m5;
	VTVector3D v1(0,5,1);
	VTMatrix4 m;
	m = VTGL_RotationY(&m,angle)*VTGL_TranslateXYZ(&m2,6.0f,3.0f,7.0f);
	m_pGraphDevice->SetTransform(&m);
	Mesh->Draw(12);
	VTGL_TranslateXYZ(&m,0,0,0);
	m_pGraphDevice->SetMatrixMode("World");
	VTMatrix4 m1;
	VTMatrix4 m3 = VTGL_RotationAxis(&m3,&v1,angle)*VTGL_TranslateXYZ(&m1,-6.0f,7.0f,7.0f);
	m_pGraphDevice->SetTransform(&m3);
	Mesh->Draw(12);
	m_pGraphDevice->SetRenderMode(VTGLRM_GRID);
	m_pGraphDevice->SetTransform(&m);
	g_pVTGLTerrain->Draw();
	m_pGraphDevice->SetRenderMode(VTGLRM_SOLID);
	m_pGraphDevice->SetTransform(&m);
	m_pGraphDevice->SetRenderMode(VTGLRM_ZDISABLE);
	Axis->Draw(3,"Line");
	m_pGraphDevice->SetRenderMode(VTGLRM_ZENABLE);
	m_pGraphDevice->EndRender();
	if(GetKeyState(VK_SPACE))
	VTGLCamera.Build(this,fTimeDelta,fCameraSpeed);
	}
	}

	void CRenderWindow::OnIdle(wxIdleEvent &event)
	{
float currTime = (float)timeGetTime();
float timeDelta = (currTime - m_fLastTime) * 0.001f;
OnRender(timeDelta);
m_fLastTime = currTime; 
event.RequestMore();
	}

CRenderWindow::CRenderWindow(wxString &szDeviceChoose,wxWindow * pParentWindow,const wxPoint &pos,const wxSize &size):wxWindow(pParentWindow,-1,pos,size)
{
///////////////////////////////////////
m_pGraphDevice = NULL;
m_fLastTime = 0;
///////////////////////////////////////
SetBackgroundColour(wxColour("Grey"));
SetRenderDevice(szDeviceChoose);
}

CRenderWindow::~CRenderWindow()
{
if(m_pGraphDevice)
delete m_pGraphDevice;
}

void CRenderWindow::SetRenderDevice(wxString &szDeviceChoose)
{
if(m_pGraphDevice)
delete m_pGraphDevice;
m_pGraphDevice = new VTGL_Device(szDeviceChoose,this,true,640,480);
VTGLCamera = VTGL_Camera(m_pGraphDevice);
VTGLCamera.SetProjectionMatrix(VTGL_ToRadian(45.0),100.0f);
VTGLCamera.SetViewMatrix();
WORD * indices = 0;
VertexXYZC * MeshVert;
Mesh = new VTGL_Geometry(m_pGraphDevice->GetBaseDevice()); 
Mesh->CreateVertexBuffer(sizeof(VertexXYZC),8,"Position+Color");
MeshVert = (VertexXYZC*)Mesh->MapVertex();
     MeshVert[0] = VertexXYZC(-1.0f, -1.0f, -1.0f,0x00FF00FF);
     MeshVert[1] = VertexXYZC(-1.0f,  1.0f, -1.0f,0x00FF00FF);
     MeshVert[2] = VertexXYZC( 1.0f,  1.0f, -1.0f,0x00FF00FF);
     MeshVert[3] = VertexXYZC( 1.0f, -1.0f, -1.0f,0x00FF00FF);
     MeshVert[4] = VertexXYZC(-1.0f, -1.0f,  1.0f,0x000000FF);
     MeshVert[5] = VertexXYZC(-1.0f,  1.0f,  1.0f,0x000000FF);
     MeshVert[6] = VertexXYZC( 1.0f,  1.0f,  1.0f,0x000000FF);
     MeshVert[7] = VertexXYZC( 1.0f, -1.0f,  1.0f,0x000000FF);
Mesh->UnMapVertex();
Mesh->CreateIndexBuffer16(36);//Indexes Format the next ===>>>
indices = (WORD*)Mesh->MapIndex();

	// front side
	indices[0]  = 0; indices[1]  = 1; indices[2]  = 2;
	indices[3]  = 0; indices[4]  = 2; indices[5]  = 3;

	// back side
	indices[6]  = 4; indices[7]  = 6; indices[8]  = 5;
	indices[9]  = 4; indices[10] = 7; indices[11] = 6;

	// left side
	indices[12] = 4; indices[13] = 5; indices[14] = 1;
	indices[15] = 4; indices[16] = 1; indices[17] = 0;

	// right side
	indices[18] = 3; indices[19] = 2; indices[20] = 6;
	indices[21] = 3; indices[22] = 6; indices[23] = 7;

	// top
	indices[24] = 1; indices[25] = 5; indices[26] = 6;
	indices[27] = 1; indices[28] = 6; indices[29] = 2;

	// bottom
	indices[30] = 4; indices[31] = 0; indices[32] = 3;
	indices[33] = 4; indices[34] = 3; indices[35] = 7;



Mesh->UnMapIndex();


///Оси мирового пространства
VertexXYZC * AxisVert;
Axis = new VTGL_Geometry(m_pGraphDevice->GetBaseDevice()); // Working with matrix !!!
Axis->CreateVertexBuffer(sizeof(VertexXYZC),6,"Position+Color");//Тут ошибка в версии OGL !!!
AxisVert = (VertexXYZC*)Axis->MapVertex();
	 AxisVert[0] = VertexXYZC(0.0f,0.0f,0.0f,0x00000000);
	 AxisVert[1] = VertexXYZC(1.0f,0.0f,0.0f,0x00000000);
	 AxisVert[2] = VertexXYZC(0.0f,0.0f,0.0f,0x00000000);
	 AxisVert[3] = VertexXYZC(0.0f,0.0f,1.0f,0x00000000);
	 AxisVert[4] = VertexXYZC(0.0f,0.0f,0.0f,0x00000000);
	 AxisVert[5] = VertexXYZC(0.0f,1.0f,0.0f,0x00000000);
Axis->UnMapVertex();

g_pVTGLTerrain = new VTGL_Terrain(m_pGraphDevice,64,64,1);
g_pVTGLTerrain->SetVertices(0x00CC9933);
g_pVTGLTerrain->SetIndices();
}
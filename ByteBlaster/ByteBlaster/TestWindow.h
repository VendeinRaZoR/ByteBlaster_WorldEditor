#ifndef _TESTWINDOW_H_
#define _TESTWINDOW_H_
#include "VWindow.h"
#include "VTGui.h"
#include "VEventHandler.h"
#include "VGraphicsUser.h"
#include "RenderWindow.h"
#include "TerrainConfig.h"
#include "TerrainOpen.h"
#include "BBEditor.h"
 
class CTestWindow : public VSDIWindow
{
	VEventHandler m_EventHandler;
	VTGuiManager *GUIManager;
	TerrainConfig * m_pTerrainConfig;
	CRenderWindow * m_pRenderWindow;
	TerrainParam m_TerrainParam;
public:
	CTestWindow():VSDIWindow("Byte Blaster World Editor Pre Alpha v.0.1")
	{ 
GUIManager = new VTGuiManager(this);
m_EventHandler = VEventHandler(this);
m_EventHandler.CallStatic();
	}
	//~CTestWindow(){}
public:
	void StaticMessageCallback() 
	{
	 GUIManager->CreateTopMenu();
	GUIManager->AddToolbarElement(0,ID_FILE_NEW40005,TBSTYLE_BUTTON,TBSTATE_ENABLED,0);
	GUIManager->AddToolbarElement(0,ID_FILE_OPEN40006,TBSTYLE_BUTTON,TBSTATE_ENABLED,1);
	GUIManager->AddToolbarElement(0,ID_FILE_CLOSE40010,TBSTYLE_BUTTON,TBSTATE_ENABLED,3);
	GUIManager->AddToolbarElement(0,ID_FILE_SAVE40015,TBSTYLE_BUTTON,TBSTATE_ENABLED,2);
	GUIManager->CreateToolBar();
	GUIManager->CreateStatusBar();
	m_EventHandler.AddEvent(WM_COMMAND);
	}
	void EventMessageCallback() 
	{
		int *nRadius = NULL;
		nRadius = (int*)GetData("Radius");
		if(nRadius != NULL)
		printf("%d\n",*nRadius);
		WPARAM wParam;
		if((m_EventHandler.GetEventByType(WM_COMMAND))->isActive())
		{
		wParam = (m_EventHandler.GetEventByType(WM_COMMAND))->GetEventParam("Param1");
	if(wParam == ID_FILE_NEW40005)
		{
		m_pTerrainConfig = new TerrainConfig(this);
		}
	if(wParam == ID_FILE_OPEN40006)
		{
	OPENFILENAME ofn={0};
    char szDirect[260];
    char szFileName[260];
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = *this;
    ofn.lpstrFile = szDirect;
    *(ofn.lpstrFile) = 0;
    ofn.nMaxFile =sizeof(szDirect);
    ofn.lpstrFilter = "*.raw\0*.raw\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = szFileName;
    *(ofn.lpstrFileTitle) = 0;
    ofn.nMaxFileTitle = sizeof(szFileName);
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_EXPLORER;
    if(GetOpenFileName(&ofn))
	{
	m_pRenderWindow = new CRenderWindow(this);
	m_WindowManager.GetWindowByName("Render Window")->SendData((void*)szDirect,"OpenFile");
    SetRenderWindow(m_pRenderWindow);
	}
		}
		if(wParam == ID_FILE_EXIT)
		{
			OnDestroy();
		}
		if(m_WindowManager.GetWindowByName("Render Window"))
		{
	if(wParam == ID_FILE_SAVE40015)
	{
	OPENFILENAME ofn={0};
    char szDirect[260];
    char szFileName[260];
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = *this;
    ofn.lpstrFile = szDirect;
    *(ofn.lpstrFile) = 0;
    ofn.nMaxFile =sizeof(szDirect);
    ofn.lpstrFilter = "*.raw\0*.raw\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = szFileName;
    *(ofn.lpstrFileTitle) = 0;
    ofn.nMaxFileTitle = sizeof(szFileName);
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_EXPLORER;
    if(GetSaveFileName(&ofn))
	{
		m_WindowManager.GetWindowByName("Render Window")->SendData((void*)szDirect,"SaveFile");
		MessageBox(*this,"Save Done","Saving",MB_ICONINFORMATION);
	}
	}
		if(wParam == ID_RENDERMODE_GRID)
		{
			m_WindowManager.GetWindowByName("Render Window")->SendData((void*)true,"GridMode");
		}
		if(wParam == ID_FILE_CLOSE40010)
		{
			m_WindowManager.GetWindowByName("Render Window")->OnDestroy();
		}
		}
		if(wParam == ID_ABOUT_HELP)
		{
			MessageBox(*this,"Пробел - активировать камеру\nW,S,A,D - перемещение\nПри создании ландшафта все поля кроме 'Water Level' обязательны\n(Пример : Cell Size : 1 , 64 x 64 , Terrain Level : 1)\n\nBy Vendein_RaZoR\n","Help",MB_ICONINFORMATION);
		}
        }
	}

	void OnDestroy()
	{
		PostQuitMessage(0);
	}
//==============================================================================================================================================
//==============================================================================================================================================
//=======================================Camera Hack Methods====================================================================================
//==============================================================================================================================================
//==============================================================================================================================================
//void TestProcessMemory()
//{
			/*	if(Timer.isActive())
		{
			if(m_pKeyboard->KeyState('H'))
{
	if(m_pProcess.WriteMemory<bool>((void*)Address1,1))
	{
	printf("Value Written\n");
	}
}
			if(m_pKeyboard->KeyState('J'))
{
	if(m_pProcess.WriteMemory<bool>((void*)Address1,0))
	{
	printf("Value Written\n");
	}
			}
				}*/
//}
};



#endif
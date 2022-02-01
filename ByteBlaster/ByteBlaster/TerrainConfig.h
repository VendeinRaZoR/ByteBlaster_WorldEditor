#ifndef _TERRAINCONFIG_
#define _TERRAINCONFIG_
#include "VWindow.h"
#include "VTGUI.h"
#include "RenderWindow.h"
#include "resource.h"
#include "BBEditor.h"

class TerrainConfig : public VSDIWindow
{
	VTGuiManager *m_pGUIManager;
	VEventHandler m_EventHandler;
	VEventHandler m_RenderEventHandler;
	VBaseWindow * m_pParentWindow;
	CRenderWindow * m_pRenderWindow;
	TerrainParam m_TerrainParam;
public:
	TerrainConfig(VBaseWindow * pParentWindow):VSDIWindow(MAKEINTRESOURCE(IDD_DIALOG1),pParentWindow)
   {
	m_pParentWindow = pParentWindow;
    m_pGUIManager = new VTGuiManager(this);
	m_pGUIManager->AddElement(IDC_BUTTON1);
	m_pGUIManager->AddElement(IDC_BUTTON2);
	m_pGUIManager->AddElement(IDC_EDIT1);
	m_pGUIManager->AddElement(IDC_EDIT3);
	m_pGUIManager->AddElement(IDC_EDIT4);
	m_pGUIManager->AddElement(IDC_EDIT5);
    m_EventHandler = VEventHandler(this);
	m_EventHandler.AddEvent(WM_COMMAND);
	m_EventHandler.CallStatic();
   }
	void StaticMessageCallback()
	{

	}
	void EventMessageCallback()
	{
		if(m_pGUIManager->GetElementByID(IDC_BUTTON1)->isActive())
		{
		    DestroyWindow(*this);
		}
		if(m_pGUIManager->GetElementByID(IDC_BUTTON2)->isActive())
		{
		m_TerrainParam.nHeight = m_pGUIManager->GetElementByID(IDC_EDIT1)->GetInt();
		m_TerrainParam.nWidth = m_pGUIManager->GetElementByID(IDC_EDIT3)->GetInt();
		m_TerrainParam.nDepth = m_pGUIManager->GetElementByID(IDC_EDIT4)->GetInt();
		m_TerrainParam.nCellSpace = m_pGUIManager->GetElementByID(IDC_EDIT5)->GetInt();
        m_pRenderWindow = new CRenderWindow(m_pParentWindow);
		m_pParentWindow->SetRenderWindow(m_pRenderWindow);
		m_RenderEventHandler = VEventHandler(m_pRenderWindow);
		m_RenderEventHandler.AddEvent(WM_PARAM);
		m_WindowManager.GetWindowByName("Render Window")->SendData((void*)&m_TerrainParam,"TerrainParam");
		DestroyWindow(*this);
		}
	}
   ~TerrainConfig()
   {
   }
};

#endif
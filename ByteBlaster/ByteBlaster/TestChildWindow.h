#include "TestWindow.h"

class CTestChildWindow : public VSDIWindow
{
VEventHandler m_EventHandler;
VTGuiManager * m_pGUIManager;
public:
	CTestChildWindow(VBaseWindow * pParentWindow):VSDIWindow(MAKEINTRESOURCE(IDD_DIALOG2),pParentWindow)
	{
	m_pGUIManager = new VTGuiManager(this);
	m_pGUIManager->AddElement(IDC_SLIDER1);
	m_pGUIManager->AddElement(IDC_SLIDER2);
	m_pGUIManager->AddElement(IDC_SLIDER3);
	EnableWindow(GetDlgItem(*this,IDC_SLIDER2), false);
	EnableWindow(GetDlgItem(*this,IDC_SLIDER1), false);
	EnableWindow(GetDlgItem(*this,IDC_SLIDER3), false);
	//SendMessage(GetDlgItem(*this,IDC_SLIDER1), TBM_SETPOS, 1, 50);
	//SendMessage(GetDlgItem(*this,IDC_SLIDER2), TBM_SETPOS, 1, 50);
	//SendMessage(GetDlgItem(*this,IDC_SLIDER3), TBM_SETPOS, 1, 50);
	m_EventHandler = VEventHandler(this);
	m_EventHandler.AddEvent(WM_HSCROLL);
	m_EventHandler.StartEvents();
	}
	void EventMessageCallback()
	{
		WPARAM wParam;
		if(m_WindowManager.GetWindowByName("Render Window"))
		{
  	EnableWindow(GetDlgItem(*this,IDC_SLIDER1), true);//TODO : Работа с диалоговыми окнами и элементами !!!
	EnableWindow(GetDlgItem(*this,IDC_SLIDER2), true);
	EnableWindow(GetDlgItem(*this,IDC_SLIDER3), true);
		}
		if((m_EventHandler.GetEventByType(WM_HSCROLL))->isActive())
		{
		wParam = m_EventHandler.GetEventByType(WM_HSCROLL)->GetEventParam("Param1");
		if(wParam == TB_ENDTRACK)
		{
			int nRadius = SendMessage(GetDlgItem(*this,IDC_SLIDER1), TBM_GETPOS, 0, 0);
			int nStraight = SendMessage(GetDlgItem(*this,IDC_SLIDER2), TBM_GETPOS, 0, 0);
			int nCamSpeed = SendMessage(GetDlgItem(*this,IDC_SLIDER3), TBM_GETPOS, 0, 0);
			m_WindowManager.GetWindowByName("Render Window")->SendData((void*)&nRadius,"Radius"); //0..100
			m_WindowManager.GetWindowByName("Render Window")->SendData((void*)&nStraight,"Straight");
			m_WindowManager.GetWindowByName("Render Window")->SendData((void*)&nCamSpeed,"CamSpeed");
		}
		}
	}
};
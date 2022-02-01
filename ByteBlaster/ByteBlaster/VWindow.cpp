#include "VWindow.h"

/////////////////////////////////////////////////////////
////////////////////////Base Window//////////////////////
/////////////////////////////////////////////////////////

HINSTANCE g_hInstance;

void VBaseWindow::StartEvents()
{
	m_bStartEvents = true;
}

void VBaseWindow::StopEvents()
{
	m_bStartEvents = false;
}

bool VBaseWindow::GetEventsState()const
{
	return m_bStartEvents;
}

HWND VBaseWindow::GetWindowHandle() const
{
	return m_hWnd;
}

int VBaseWindow::GetWindowsNum()
{
	return m_nWindowID;
}

UINT VBaseWindow::GetWindowMessage() const
{
	return m_nMessage;
}

void VBaseWindow::SetWindowMessage(UINT nMessage)
{
	m_nMessage = nMessage;
}

void VBaseWindow::SetWindowParam(WPARAM wParam, LPARAM lParam)
{
	m_wParam = wParam;
	m_lParam = lParam;
}

	WPARAM  VBaseWindow::GetwParam()const
	{
		return m_wParam;
	}
	LPARAM  VBaseWindow::GetLParam()const
	{
		return m_lParam;
	}
	int VBaseWindow::GetID()
	{
		return m_nBaseWindowID;
	}
	void  VBaseWindow::SetWindowMessageCallback(GetMessageCallback WndMsgCallback)
	{
		m_StaticMessageCallback = WndMsgCallback;
	}
 VBaseWindow::operator HWND()
 {
	 return m_hWnd;
 }
 void VBaseWindow::StaticMessageCallback()
 {
	 //printf("StaticMessageCallback");
 }
 void VBaseWindow::RenderMessageCallback(float fTimeDelta)
 {
	 //printf("RenderMessageCallback");
 }

 void VBaseWindow::OnCreate()NORETURN;
 BOOL VBaseWindow::OnCommand(WPARAM wParam,LPARAM lParam)NULLRETURN;
 void VBaseWindow::OnDestroy()NORETURN;

 void VBaseWindow::EventMessageCallback()
 {

 }

 String::VString VBaseWindow::GetWindowName()
 {
	 return m_szWindowName;
 }

 void VBaseWindow::SendData(void * pParam,const char * szDataName)
 {
   SendMessage(*this,WM_PARAM,(WPARAM)pParam,(LPARAM)szDataName);
 }

 void * VBaseWindow::GetData(char * szDataName)
 {
	 if(m_nMessage == WM_PARAM)
	 {
	 if(!String::StrCmp((char*)m_lParam,szDataName))
	 {
     return (void*)m_wParam;
	 }
	 }
	 return 0;
 }

 /////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////
 /////////////////////Window Manager/////////////////////////
  ////////////////////////////////////////////////////////////
  ////////////////////////////////////////////////////////////

 VWindowManager::VWindowManager()
 {
 }

 VWindowManager::~VWindowManager()
 {

 }

 VBaseWindow * VWindowManager::GetWindowByName(String::VString vsWindowName)//Singleton
 {
	 for(list<VBaseWindow*>::iterator i = m_lWindow.begin(); i != m_lWindow.end(); i++)
	 {
		 if((*i)->GetWindowName() == vsWindowName)
		 {
             return (*i);
		 }
	 }
	 return 0;
 }

 VBaseWindow * VWindowManager::GetWindowByID(int nWindowID)
 {	 
	 for(list<VBaseWindow*>::iterator i = m_lWindow.begin();i != m_lWindow.end();i++)
	 {
		 if(nWindowID == (*i)->GetID())
		 {
			 return (*i);
		 }
 }
	 return 0;
 }

 void VWindowManager::AddWindow(VBaseWindow *pBaseWindow)
 {
 int nMatch = 0;
 for(list<VBaseWindow*>::iterator i = m_lWindow.begin();i != m_lWindow.end();i++)
 {
     if((*i) == pBaseWindow)nMatch++;
 }
 if(nMatch > 0)
::MessageBox(0,"This window already exist","Error",MB_OK|MB_ICONERROR);
 else
  m_lWindow.push_back(pBaseWindow);
 }

 void VWindowManager::DeleteWindow(VBaseWindow *pBaseWindow)
 {
	 m_lWindow.remove(pBaseWindow);
 }

 /////////////////////////////////////////////////////////
////////////////////////SDI Window//////////////////////
/////////////////////////////////////////////////////////
 VSDIWindow::VSDIWindow(LPCTSTR window_text,HWND hWndParent,int nCmdShow,UINT nX,UINT nY,UINT nSx,UINT nSy,DWORD dwStyle,DWORD dwExStyle)
 {
	m_lpcClassName = "BaseWNDClass";
	m_pRenderWindow = 0;
	RegisterWindowClass(); 
     m_hWnd = CreateWindowEx(dwExStyle,
		reinterpret_cast<LPCTSTR>(m_lpcClassName), /// Create Window
		window_text,
		dwStyle,
		nX, nY,nSx, nSy,
		hWndParent, 
		NULL, 
		GetHInst(),
		this);
	ShowWindow(m_hWnd, nCmdShow);
	m_nBaseWindowID = m_nWindowID++;
	m_szWindowName = window_text;
	//m_EventHandler = new VEventHandler(this);
	m_WindowManager.AddWindow(this);
	}

 BOOL CALLBACK VSDIWindow::DialogProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
 {
	LONG_PTR user_data = GetWindowLongPtr(hWnd, GWLP_USERDATA);
	
	VSDIWindow * this_dialog_window = reinterpret_cast<VSDIWindow *>(user_data);
	if(this_dialog_window->GetEventsState())
	{
	this_dialog_window->EventMessageCallback();
	}
	switch(Msg)
	{
		case WM_DESTROY:
			{
               this_dialog_window->OnDestroy();
				break;
			}
		case WM_CREATE:
			{
			this_dialog_window->StaticMessageCallback();
			this_dialog_window->StartEvents();
			break;
			}
			}
	 return false;
 }

 BOOL CALLBACK VSDIWindow::StaticDlgProc(HWND hWnd,UINT Msg,WPARAM wParam,LPARAM lParam)
{
	   if ( LONG_PTR user_data = GetWindowLongPtr(hWnd, GWLP_USERDATA)) {
        VSDIWindow * this_dialog_window = reinterpret_cast<VSDIWindow *>(user_data);
	    this_dialog_window->SetWindowMessage(Msg);
	    this_dialog_window->SetWindowParam(wParam,lParam);
        return this_dialog_window->DialogProc(hWnd, Msg, wParam, lParam);
      }
      if (Msg == WM_INITDIALOG) {		
        VSDIWindow * this_dialog_window = reinterpret_cast<VSDIWindow *>(lParam);
        SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this_dialog_window));
		return this_dialog_window->DialogProc(hWnd, Msg, wParam, lParam);
      }
	return false;
}

 VSDIWindow::VSDIWindow(LPCSTR lpTemplate,VBaseWindow *pParentWindow)
 {
	 m_pParentWindow = NULL;
	 m_pParentWindow = pParentWindow;
	 char * lpcWindowName = new char[32];
	 if(pParentWindow != NULL)
	 {
	 m_hWnd = CreateDialogParam(GetHInst(),lpTemplate,*pParentWindow,StaticDlgProc,(LPARAM)this);
	 ShowWindow(m_hWnd,1);
	 }
	 else
	 {
     m_hWnd = CreateDialogParam(GetHInst(),lpTemplate,NULL,StaticDlgProc,(LPARAM)this);
	 ShowWindow(m_hWnd,1);
	 }
    GetWindowText(m_hWnd,lpcWindowName,32);
	 m_szWindowName = lpcWindowName;
 	m_nBaseWindowID = VBaseWindow::m_nWindowID++;
	 m_WindowManager.AddWindow(this);
 }

 VSDIWindow::VSDIWindow()
 {
m_nBaseWindowID == m_nWindowID++;
m_WindowManager.AddWindow(this);
 }

 LPCTSTR VSDIWindow::GetClassName()
 {
	 return m_lpcClassName;
 }
ATOM VSDIWindow::RegisterWindowClass() 
{  
		WNDCLASS WNDClass;
	memset(&WNDClass,0,sizeof(WNDClass));
	WNDClass.lpszClassName = m_lpcClassName;
	WNDClass.style         = CS_HREDRAW | CS_VREDRAW;
	WNDClass.lpfnWndProc   = &StaticWndProc;
	WNDClass.hInstance     = GetHInst();
	WNDClass.hCursor       = LoadCursor(NULL, IDC_ARROW);
	WNDClass.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_HIGHLIGHT);
	WNDClass.hIcon = LoadIcon(GetHInst(),MAKEINTRESOURCE(IDI_ICON1));
      return RegisterClass(&WNDClass); 
}
HWND VSDIWindow::GetWindowHandle()const
{
	return m_hWnd;
}

VWindowManager VSDIWindow::m_WindowManager = VWindowManager();

void VSDIWindow::SetWindowMessageCallback(GetMessageCallback WndMsgCallback)
{
		m_StaticMessageCallback = WndMsgCallback;
}
void VSDIWindow::OnDestroy()NORETURN;

LRESULT CALLBACK VSDIWindow::WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) 
{
	LONG_PTR user_data = GetWindowLongPtr(hWnd, GWLP_USERDATA);
	VSDIWindow * this_window = reinterpret_cast<VSDIWindow *>(user_data);
	if(this_window->GetEventsState())
	{
	this_window->EventMessageCallback();
	}
		switch(Msg)
		{
		/*case WM_PARAM:
			{
				printf("%x",this_window);
				printf("Param Sended %x %x",lParam,wParam);
			}
			break;*/
		case WM_DESTROY:
			{
               this_window->OnDestroy();
				break;
			}
        case WM_CREATE:
			{	
			this_window->StaticMessageCallback();	
			this_window->StartEvents();
			if(m_StaticMessageCallback)
			m_StaticMessageCallback(hWnd,Msg,lParam,wParam);
				break;
			}
		default:
			{
			}
		}	
return DefWindowProc(hWnd, Msg, wParam, lParam); 
}

LRESULT CALLBACK StaticWndProc(HWND hWnd,UINT Msg,WPARAM wParam,LPARAM lParam) 
{
     if ( LONG_PTR user_data = GetWindowLongPtr(hWnd, GWLP_USERDATA)) {
        VSDIWindow * this_window = reinterpret_cast<VSDIWindow *>(user_data);
	this_window->SetWindowMessage(Msg);
	this_window->SetWindowParam(wParam,lParam);
        return this_window->WndProc(hWnd, Msg, wParam, lParam);
      }
      if (Msg == WM_NCCREATE || Msg == WM_CREATE) {
        LPCREATESTRUCT create_struct = reinterpret_cast<LPCREATESTRUCT>(lParam);
        VSDIWindow * this_window = reinterpret_cast<VSDIWindow *>(create_struct->lpCreateParams);
        SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this_window));
		return this_window->WndProc(hWnd, Msg, wParam, lParam);
      }
      return DefWindowProc(hWnd, Msg, wParam, lParam);
    }

int IBaseWindow::m_nWindowID = 0;
HWND VBaseWindow::m_hClientMDIWnd = NULL;

void VSDIWindow::SetRenderWindow(VBaseWindow * pRenderWindow)
{
     m_pRenderWindow = pRenderWindow;
}

BOOL VSDIWindow::GetMsg()
		{
	MSG Msg;
	memset((void*)&Msg,0,sizeof(MSG));
    float m_fLastTime = (float)timeGetTime();
       HWND hWnd = NULL;
	   while(Msg.message != WM_QUIT)
	{
		if (PeekMessage(&Msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		}
		else
		{
	if(m_pRenderWindow != NULL)
	{
	float fCurrTime = (float)timeGetTime();
    float fTimeDelta = (fCurrTime - m_fLastTime) * 0.001f;
	m_pRenderWindow->RenderMessageCallback(fTimeDelta);
    m_fLastTime = fCurrTime;
	}
		}
	}
        return FALSE;
}

HINSTANCE GetHInst()
{
	g_hInstance = GetModuleHandle(PROCESS_NAME);return g_hInstance;
}


///////////////////////////////////////////////////////////////
////////////////////////////MDI Window/////////////////////////
///////////////////////////////////////////////////////////////

VMDIWindow::VMDIWindow(LPCTSTR window_text,HMENU hMenu,HWND hWndParent,int nCmdShow,UINT nX,UINT nY,UINT nSx ,UINT nSy ,DWORD dwStyle)
	{

	RegisterFrameClass();
	m_hWnd = CreateWindow(
		reinterpret_cast<LPCTSTR>(m_lpcMainClassName),
		window_text,
		dwStyle,
		nX, nY,nSx, nSy,
		hWndParent, 
		hMenu, 
		GetHInst(),
		this);
    UpdateWindow(m_hWnd);
	ShowWindow(m_hWnd, nCmdShow);
	}

VMDIWindow::~VMDIWindow()
	{

	}

HWND VMDIChildWindow::GetChildMDIWindowHandle()const
{
	return m_hChildMDIWnd;
}

HWND VMDIWindow::GetWindowHandle()const
	{
		return m_hWnd;
	}

LRESULT CALLBACK VMDIWindow::FrameWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    LONG_PTR user_data = GetWindowLongPtr(hWnd, GWLP_USERDATA);
	VMDIWindow * this_window = reinterpret_cast<VMDIWindow *>(user_data);
	this_window->SetWindowMessage(uMsg);
	this_window->SetWindowParam(wParam,lParam);
	if(this_window->GetEventsState())
	this_window->EventMessageCallback();
		switch(uMsg)
		{
		case WM_DESTROY:
			{
               this_window->OnDestroy();
				break;
			}
        case WM_CREATE:
			{
				this_window->StaticMessageCallback();
				this_window->OnCreate();
				break;
			}
		case WM_COMMAND:
			{
				this_window->OnCommand(wParam,lParam);
				break;
			}
		default:
			{
			}
		}	
		return DefFrameProc(hWnd,this_window->m_hClientMDIWnd, uMsg, wParam, lParam);
}

LRESULT CALLBACK StaticMDIWndProc(HWND hWnd,UINT Msg,WPARAM wParam,LPARAM lParam) 
{
	HWND hClientMDIWnd;
     if ( LONG_PTR user_data = GetWindowLongPtr(hWnd, GWLP_USERDATA)) {
        VMDIWindow * this_window = reinterpret_cast<VMDIWindow*>(user_data);
        return this_window->FrameWndProc(hWnd, Msg, wParam, lParam);
      }
      if (Msg == WM_NCCREATE || Msg == WM_CREATE) {
	    CLIENTCREATESTRUCT ccs;
        memset(&ccs, 0, sizeof(CLIENTCREATESTRUCT));
        LPCREATESTRUCT create_struct = reinterpret_cast<LPCREATESTRUCT>(lParam);
        VMDIWindow * this_window = reinterpret_cast<VMDIWindow *>(create_struct->lpCreateParams);
		ccs.hWindowMenu=GetSubMenu(GetMenu(hWnd), 1);
        ccs.idFirstChild=100;
		hClientMDIWnd = CreateWindow("MDICLIENT", (LPCTSTR)NULL,
        WS_CHILD|WS_CLIPCHILDREN|WS_VSCROLL|WS_HSCROLL|WS_VISIBLE,
        0, 0, 0, 0, hWnd, NULL, GetHInst(), (LPSTR)&ccs);
		this_window->m_nWindowID++;
		this_window->m_hClientMDIWnd = hClientMDIWnd;
        SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this_window));
        return this_window->FrameWndProc(hWnd, Msg, wParam, lParam);
      }

	  return  DefFrameProc(hWnd,hClientMDIWnd, Msg, wParam, lParam);
    }

ATOM VMDIWindow::RegisterFrameClass()
{
		WNDCLASS FrameWndClass;

	memset(&FrameWndClass,0,sizeof(FrameWndClass));
	FrameWndClass.lpszClassName = m_lpcMainClassName;
	FrameWndClass.style         = CS_HREDRAW | CS_VREDRAW;
	FrameWndClass.lpfnWndProc   = &StaticMDIWndProc;
	FrameWndClass.hInstance     = GetHInst();
	FrameWndClass.hCursor       = LoadCursor(NULL, IDC_ARROW);
	FrameWndClass.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_BACKGROUND);

	if(!RegisterClass(&FrameWndClass))
	{
		MessageBox(NULL,
			       "Window Registration Failed!", "Error!",
			       MB_OK);
	}

	return 0;
		
}

LPCTSTR VMDIWindow::m_lpcMainClassName = "MainMDIWnd"; 
LPCTSTR VMDIChildWindow::m_lpcChildClassName = "ChildMDIWnd";

VMDIChildWindow::VMDIChildWindow(LPCTSTR szChildWndTitle,int nCmdShow,UINT nX,UINT nY,UINT nSx ,UINT nSy ,DWORD dwStyle)
{
	RegisterChildClass();
	m_hChildMDIWnd = CreateMDIWindow(m_lpcChildClassName, szChildWndTitle,
              MDIS_ALLCHILDSTYLES | WS_MINIMIZE, nX, nY, nSx,
              nSy, m_hClientMDIWnd, GetHInst(), 0);
	ShowWindow(m_hChildMDIWnd, nCmdShow);
}

ATOM VMDIChildWindow::RegisterChildClass()
{
	WNDCLASS ChildWndClass;
	memset(&ChildWndClass,0,sizeof(ChildWndClass));
	ChildWndClass.lpszClassName = m_lpcChildClassName;
	ChildWndClass.style         = CS_HREDRAW | CS_VREDRAW;
	ChildWndClass.lpfnWndProc   = &StaticChildMDIWndProc;
	ChildWndClass.hInstance     = GetHInst();
	ChildWndClass.hCursor       = LoadCursor(NULL, IDC_ARROW);
	ChildWndClass.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_BACKGROUND);

	return RegisterClass(&ChildWndClass);
}

LRESULT CALLBACK VMDIChildWindow::ChildWndProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	if(uMsg == WM_MOVE)
		MessageBox(0,"Move","Move",0);
	return DefMDIChildProc(hWnd, uMsg, wParam, lParam);
}

LRESULT CALLBACK StaticChildMDIWndProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam) 
{
	return DefMDIChildProc(hWnd, uMsg, wParam, lParam);
}
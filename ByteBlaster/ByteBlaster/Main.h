#ifndef _MAIN_
#define _MAIN_
#include <windows.h>
#include <tchar.h>
#include <sstream>
#include <stdexcept>
#include <cassert>
#include <windowsx.h>
#include <commctrl.h>

#include "Keyboard.h"
#include "CString.h"

#ifndef STRICT
#define STRICT
#endif

#ifndef WINVER
#define WINVER         0x0500
#endif
#ifndef _WIN32_WINDOWS
#define _WIN32_WINDOWS 0x0500 
#endif
#ifndef _WIN32_WINNT
#define _WIN32_WINNT   0x0600
#endif

#define MAX_ARGLEN 256

#define PROCESS_NAME "ByteBlaster.exe"

#define INIT_CMN_CNTRLS ((WINVER == _WIN32_WINDOWS) ? InitCommonControls() : NULL) 

using namespace String;

HINSTANCE g_hInstance;

BOOL GetSDIMgs();
BOOL GetMDIMgs(HWND hWnd);
void SetArgs(int argc, char **argv);
HINSTANCE GetHInst(){g_hInstance = GetModuleHandle(PROCESS_NAME);return g_hInstance;}

struct IBaseWindow
{
	HWND m_hWnd;
	static int m_nWindowID;
	WPARAM m_wParam;
	LPARAM m_lParam;
};

struct WINDOW_STYLE
{
    static const DWORD dwOverlapped = WS_OVERLAPPEDWINDOW;
    static const DWORD dwPopUp = WS_POPUPWINDOW;
    static const DWORD dwChildWindow = WS_CHILDWINDOW;
};

struct WINDOW_CMDSHOW
{
	static const DWORD dwHide = 0;
	static const DWORD dwShowNormal = 1;
	static const DWORD dwShowMinimized = 2;
	static const DWORD dwShowMaximized = 3;
};

class CBaseSDIWindow : private IBaseWindow
{
private:
    static LPCTSTR m_lpcClassName;
public:
	static int m_nArgc;
	static char *m_szArgv;
public:
	LRESULT CALLBACK WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
	friend LRESULT CALLBACK StaticWndProc(HWND hWnd,UINT Msg,WPARAM wParam,LPARAM lParam);
public:
	explicit CBaseSDIWindow(LPCTSTR window_text = "XWND : Default Window",HWND hWndParent = NULL,int nCmdShow = WINDOW_CMDSHOW::dwShowNormal,
    UINT nX = CW_USEDEFAULT,UINT nY = CW_USEDEFAULT,UINT nSx = CW_USEDEFAULT,UINT nSy = CW_USEDEFAULT,
	DWORD dwStyle = WINDOW_STYLE::dwOverlapped){
	INIT_CMN_CNTRLS;
	RegisterWindowClass();
    HWND hWnd = CreateWindowA(reinterpret_cast<LPCTSTR>(m_lpcClassName),window_text,dwStyle,nX, nY,nSx, nSy,hWndParent, NULL, GetHInst(),this);
    UpdateWindow(m_hWnd);
	ShowWindow(hWnd, nCmdShow);
	}
public:
    static LPCTSTR GetClassName(){return m_lpcClassName;}
    static ATOM RegisterWindowClass();
	HWND GetWindowHandle()const{return m_hWnd;}
  public:
	  virtual void OnDestroy(HWND hWnd){PostQuitMessage(0);}
};

int CBaseSDIWindow::m_nWindowID = 0;
LPCTSTR CBaseSDIWindow::m_lpcClassName = "BaseWNDClass";

inline void SetArgs(int argc, char **argv)
	{

	}

inline ATOM CBaseSDIWindow::RegisterWindowClass() 
{  
		WNDCLASS WNDClass;
	memset(&WNDClass,0,sizeof(WNDClass));
	WNDClass.lpszClassName = m_lpcClassName;
	WNDClass.style         = CS_HREDRAW | CS_VREDRAW;
	WNDClass.lpfnWndProc   = &StaticWndProc;
	WNDClass.hInstance     = GetHInst();
	WNDClass.hCursor       = LoadCursor(NULL, IDC_ARROW);
	WNDClass.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_BACKGROUND);
      return RegisterClass(&WNDClass); 
}

BOOL GetSDIMgs()
{
	MSG Msg;
	while(GetMessage(&Msg, NULL, 0, 0))
	{
		TranslateMessage(&Msg);
        DispatchMessage(&Msg);
	}
	    return TRUE;
}

BOOL GetMDIMgs(HWND hWnd)
{
	MSG Msg;
		while(GetMessage(&Msg, NULL, 0, 0))
	{
		if (!TranslateMDISysAccel(hWnd, &Msg))
		{
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		}
	}
        return TRUE;
}

LRESULT CALLBACK CBaseSDIWindow::WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) 
{
	LONG_PTR user_data = GetWindowLongPtr(hWnd, GWLP_USERDATA);
	CBaseSDIWindow * this_window = reinterpret_cast<CBaseSDIWindow *>(user_data);
		switch(Msg)
		{
			HANDLE_MSG(this_window->m_hWnd,WM_DESTROY,this_window->OnDestroy);
		}	
return DefWindowProc(hWnd, Msg, wParam, lParam); 
}

LRESULT CALLBACK StaticWndProc(HWND hWnd,UINT Msg,WPARAM wParam,LPARAM lParam) 
{
      if ( LONG_PTR user_data = GetWindowLongPtr(hWnd, GWLP_USERDATA)) {
        CBaseSDIWindow * this_window = reinterpret_cast<CBaseSDIWindow *>(user_data);
        return this_window->WndProc(hWnd, Msg, wParam, lParam);
      }
      if (Msg == WM_NCCREATE || Msg == WM_CREATE) {
        LPCREATESTRUCT create_struct = reinterpret_cast<LPCREATESTRUCT>(lParam);
        CBaseSDIWindow * this_window = reinterpret_cast<CBaseSDIWindow *>(create_struct->lpCreateParams);
		this_window->m_nWindowID++;
		this_window->m_hWnd = hWnd;
		this_window->m_lParam = lParam;
		this_window->m_wParam = wParam;
        SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this_window));
        return this_window->WndProc(hWnd, Msg, wParam, lParam);
      }
      return DefWindowProc(hWnd, Msg, wParam, lParam);
    }


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////MDI Window////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class CBaseMDIWindow : private IBaseWindow
{
private:
	static LPCTSTR m_lpcMainClassName;
    static LPCTSTR m_lpcChildClassName;
public:
	HWND m_hChildWnd;
public:
	CBaseMDIWindow(LPCTSTR window_text = "XWND : Default Window",HWND hWndParent = NULL,int nCmdShow = WINDOW_CMDSHOW::dwShowNormal,
    UINT nX = CW_USEDEFAULT,UINT nY = CW_USEDEFAULT,UINT nSx = CW_USEDEFAULT,UINT nSy = CW_USEDEFAULT,
	DWORD dwStyle = WINDOW_STYLE::dwOverlapped):m_hChildWnd(NULL)
	{
	INIT_CMN_CNTRLS;
	RegisterFrameClass();
	RegisterChildClass();
    HWND hWnd = CreateWindow(reinterpret_cast<LPCTSTR>(m_lpcMainClassName),window_text,dwStyle,nX, nY,nSx, nSy,hWndParent, NULL, GetHInst(),this);
    UpdateWindow(m_hWnd);
	ShowWindow(m_hWnd, nCmdShow);
	}
	~CBaseMDIWindow(){}
	HWND GetChildMDIWindowHandle()const{return m_hChildWnd;}
	virtual BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);
public:
	friend LRESULT CALLBACK StaticMDIWndProc(HWND hWnd,UINT Msg,WPARAM wParam,LPARAM lParam);
	friend LRESULT CALLBACK ChildWndProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam);
	LRESULT CALLBACK FrameWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static ATOM RegisterFrameClass();
	static ATOM RegisterChildClass();
};

LRESULT CALLBACK CBaseMDIWindow::FrameWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LONG_PTR user_data = GetWindowLongPtr(hWnd, GWLP_USERDATA);
	CBaseMDIWindow * this_window = reinterpret_cast<CBaseMDIWindow *>(user_data);
    switch(uMsg)
	{
	case WM_CREATE:
		{
				CLIENTCREATESTRUCT ccs;

			ccs.hWindowMenu  = GetSubMenu(GetMenu(hWnd), 2);
			ccs.idFirstChild = 0;

			this_window->m_hChildWnd = CreateWindowEx(WS_EX_CLIENTEDGE,
				                           "MDICLIENT",
										   NULL,
										   WS_CHILD | WS_CLIPCHILDREN | WS_VSCROLL
										            | WS_HSCROLL | WS_VISIBLE,
				                           CW_USEDEFAULT,
										   CW_USEDEFAULT,
										   680,
										   460,
										   hWnd,
										   (HMENU)0,
										   GetModuleHandle(NULL),
										   (LPVOID)&ccs);
			MDICREATESTRUCT mcs;
	HWND NewWnd;

	mcs.szTitle = "Untitled";
	mcs.szClass = m_lpcChildClassName;
	mcs.hOwner  = GetModuleHandle(NULL);
	mcs.x = mcs.cx = CW_USEDEFAULT;
	mcs.y = mcs.cy = CW_USEDEFAULT;
	mcs.style = MDIS_ALLCHILDSTYLES;

	NewWnd = (HWND)SendMessage(this_window->m_hChildWnd, WM_MDICREATE, 0, (LONG)&mcs);
	DWORD Error = GetLastError();
			return DefFrameProc(hWnd,this_window->m_hChildWnd, uMsg, wParam, lParam);
       	}
				case WM_SIZE:
		{
			HWND hWndMDI;
			RECT rctClient;

			GetClientRect(hWnd, &rctClient);

			hWndMDI = GetDlgItem(hWnd, 0);
			SetWindowPos(hWndMDI, NULL, 0, 0, rctClient.right, rctClient.bottom, SWP_NOZORDER);
			return DefFrameProc(hWnd,this_window->m_hChildWnd, uMsg, wParam, lParam);
		}
				default:
					return DefFrameProc(hWnd,this_window->m_hChildWnd, uMsg, wParam, lParam);
	}
}

LRESULT CALLBACK StaticMDIWndProc(HWND hWnd,UINT Msg,WPARAM wParam,LPARAM lParam) 
{
	HWND hChildWnd;
      if ( LONG_PTR user_data = GetWindowLongPtr(hWnd, GWLP_USERDATA)) {
        CBaseMDIWindow * this_window = reinterpret_cast<CBaseMDIWindow *>(user_data);
        return this_window->FrameWndProc(hWnd, Msg, wParam, lParam);
      }
      if (Msg == WM_NCCREATE || Msg == WM_CREATE) {
        LPCREATESTRUCT create_struct = reinterpret_cast<LPCREATESTRUCT>(lParam);
        CBaseMDIWindow * this_window = reinterpret_cast<CBaseMDIWindow *>(create_struct->lpCreateParams);
		this_window->m_nWindowID++;
		this_window->m_hWnd = hWnd;
		this_window->m_lParam = lParam;
		this_window->m_wParam = wParam;
		hChildWnd = this_window->m_hChildWnd;
        SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this_window));
        return this_window->FrameWndProc(hWnd, Msg, wParam, lParam);
      }
      return DefWindowProc(hWnd, Msg, wParam, lParam);
    }

LRESULT CALLBACK ChildWndProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	return DefMDIChildProc(hWnd, uMsg, wParam, lParam);
}

ATOM CBaseMDIWindow::RegisterFrameClass()
{
	WNDCLASSEX FrameWndClass;

	FrameWndClass.cbSize		 = sizeof(WNDCLASSEX);
	FrameWndClass.style		 = 0;
	FrameWndClass.lpfnWndProc	 = &StaticMDIWndProc;
	FrameWndClass.cbClsExtra	 = 0;
	FrameWndClass.cbWndExtra	 = 0;
	FrameWndClass.hInstance	 = GetHInst();
	FrameWndClass.hIcon		 = LoadIcon(NULL, IDI_ASTERISK);
	FrameWndClass.hCursor		 = LoadCursor(NULL, IDC_ARROW);
	FrameWndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	FrameWndClass.lpszMenuName  = 0;
	FrameWndClass.lpszClassName = m_lpcMainClassName;
	FrameWndClass.hIconSm		 = LoadIcon(NULL, IDI_ASTERISK);

	if(!RegisterClassEx(&FrameWndClass))
	{
		MessageBox(NULL,
			       "Window Registration Failed!", "Error!",
			       MB_OK);
		return 0;
	}

	return RegisterClassEx(&FrameWndClass);
		
}

ATOM CBaseMDIWindow::RegisterChildClass()
{
	WNDCLASSEX ChildWndClass;

	ChildWndClass.cbSize		 = sizeof(WNDCLASSEX);
	ChildWndClass.style		 = CS_HREDRAW | CS_VREDRAW;
	ChildWndClass.lpfnWndProc = &ChildWndProc;
	ChildWndClass.cbClsExtra	 = 0;
	ChildWndClass.cbWndExtra	 = 0;
	ChildWndClass.hInstance	 = GetHInst();
	ChildWndClass.hIcon		 = LoadIcon(NULL, IDI_WARNING);
	ChildWndClass.hCursor		 = LoadCursor(NULL, IDC_ARROW);
	ChildWndClass.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
	ChildWndClass.lpszMenuName  = NULL;
	ChildWndClass.lpszClassName = m_lpcChildClassName;
	ChildWndClass.hIconSm		 = LoadIcon(NULL, IDI_WARNING);

	return RegisterClassEx(&ChildWndClass);
}

LPCTSTR CBaseMDIWindow::m_lpcMainClassName = "MainMDIWnd"; 
LPCTSTR CBaseMDIWindow::m_lpcChildClassName = "ChildMDIWnd";

BOOL CBaseMDIWindow::OnCreate(HWND hWnd, LPCREATESTRUCT lpCreateStruct)
{
	return true;
}
#endif
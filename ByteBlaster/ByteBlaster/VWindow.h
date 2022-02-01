#ifndef VWINDOW_H
#define VWINDOW_H

#include "VApplication.h"
#include "VObject.h"

#define WM_PARAM 0x00001111

#define SCREEN_SIZE_X GetSystemMetrics(SM_CXSCREEN)
#define SCREEN_SIZE_Y GetSystemMetrics(SM_CYSCREEN)

extern HINSTANCE g_hInstance;

VTAPI BOOL DXVTGetMsg(HWND = NULL);

VTAPI HINSTANCE GetHInst();

typedef void(*GetMessageCallback)(HWND hWnd,UINT Msg,LPARAM lParam,WPARAM wParam);

struct IBaseWindow
{
protected:
	HWND m_hWnd;
	static HWND m_hClientMDIWnd;
	static int m_nWindowID;
	WPARAM m_wParam;
	LPARAM m_lParam;
	GetMessageCallback m_StaticMessageCallback;
	UINT m_nMessage;
};

struct WINDOW_STYLE
{
    static const DWORD dwOverlapped = WS_SIZEBOX | WS_SYSMENU;
	static const DWORD dwFixedSize =  WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU;
    static const DWORD dwPopUp = WS_POPUP;
    static const DWORD dwChildWindow = WS_OVERLAPPED | WS_VISIBLE | WS_SYSMENU;
};

struct WINDOW_CMDSHOW
{
	static const DWORD dwHide = 0;
	static const DWORD dwShowNormal = 1;
	static const DWORD dwShowMinimized = 2;
	static const DWORD dwShowMaximized = 3;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////Common Window Class///////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class VBaseWindow : protected IBaseWindow //, public VObject
{
	bool m_bStartEvents;
protected:
	String::VString m_szWindowName;
	int m_nBaseWindowID;
public:
	VBaseWindow()
	{
	m_StaticMessageCallback = 0;
	m_nMessage = 0;
	m_bStartEvents = false;
	};
	~VBaseWindow(){};
public:
	VTAPI void StartEvents();
	VTAPI void StopEvents();
	VTAPI bool GetEventsState()const;
    virtual VTAPI HWND GetWindowHandle()const;
	VTAPI String::VString GetWindowName();
	VTAPI UINT  GetWindowMessage()const;
	VTAPI void  SetWindowMessage(UINT nMessage);
	VTAPI void  SetWindowParam(WPARAM wParam,LPARAM lParam);
	VTAPI void  SendData(void * pData,const char * szDataName);
	VTAPI void * GetData(char * szDataName);
	VTAPI WPARAM  GetwParam()const;
	VTAPI LPARAM  GetLParam()const;
	VTAPI int GetID();
	virtual VTAPI void  SetWindowMessageCallback(GetMessageCallback WndMsgCallback);
	virtual VTAPI void  EventMessageCallback();
	virtual VTAPI void  StaticMessageCallback();
	virtual VTAPI void  RenderMessageCallback(float fTimeDelta);
	virtual void ParentMessageCallback(){}
	VTAPI operator HWND();
public:
	virtual VTAPI void OnCreate();
	virtual VTAPI BOOL OnCommand(WPARAM wParam,LPARAM lParam);
	virtual VTAPI void OnDestroy();
	VTAPI int GetWindowsNum();
	virtual void SetRenderWindow(VBaseWindow * pRenderWindow){}
	//Other virtual callback functions ...
};

class VWindowManager
{
list<VBaseWindow*>m_lWindow;
public:
VWindowManager();
~VWindowManager();
VBaseWindow * GetWindowByName(VString vsWindowName);
VBaseWindow * GetWindowByID(int nWindowID);
void AddWindow(VBaseWindow * pBaseWindow);
void DeleteWindow(VBaseWindow *pBaseWindow);
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////SDI Window////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class VSDIWindow : public VBaseWindow
{
	LPCTSTR m_lpcClassName;
	VBaseWindow * m_pRenderWindow;
	VBaseWindow * m_pParentWindow;
	//VEventHandler m_EventHandler;
protected:
	static VWindowManager m_WindowManager;
public:
	friend VTAPI LRESULT CALLBACK StaticWndProc(HWND hWnd,UINT Msg,WPARAM wParam,LPARAM lParam);
public:
	explicit VTAPI VSDIWindow(LPCTSTR window_text,HWND hWndParent = NULL,int nCmdShow = WINDOW_CMDSHOW::dwShowNormal,
    UINT nX = CW_USEDEFAULT,UINT nY = CW_USEDEFAULT,UINT nSx = CW_USEDEFAULT,UINT nSy = CW_USEDEFAULT,
	DWORD dwStyle = WINDOW_STYLE::dwChildWindow,DWORD dwExStyle = 0);
	explicit VTAPI VSDIWindow(LPCSTR lpTemplate,VBaseWindow *pParentWindow);
	explicit VTAPI VSDIWindow();
public:
    VTAPI LPCTSTR GetClassName();
    VTAPI ATOM RegisterWindowClass();
	VTAPI HWND GetWindowHandle()const;
	VTAPI void SetWindowMessageCallback(GetMessageCallback WndMsgCallback);
  public:
	VTAPI LRESULT CALLBACK WndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
	VTAPI BOOL CALLBACK DialogProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
	static BOOL CALLBACK StaticDlgProc(HWND hWnd,UINT Msg,WPARAM wParam,LPARAM lParam);
  public:
	  VTAPI void OnDestroy();
	  VTAPI void SetRenderWindow(VBaseWindow * pRenderWindow);
	  VTAPI BOOL GetMsg();
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////MDI Window////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class VMDIWindow : public VBaseWindow
{
	static LPCTSTR m_lpcMainClassName;
public:
	explicit VTAPI VMDIWindow(LPCTSTR window_text = "VT : Default MDI Window",HMENU hMenu = NULL,HWND hWndParent = NULL,int nCmdShow = WINDOW_CMDSHOW::dwShowNormal,
    UINT nX = CW_USEDEFAULT,UINT nY = CW_USEDEFAULT,UINT nSx = CW_USEDEFAULT,UINT nSy = CW_USEDEFAULT,
	DWORD dwStyle = WINDOW_STYLE::dwOverlapped);
	VTAPI ~VMDIWindow();
	VTAPI HWND GetWindowHandle()const;
private:
	static VTAPI ATOM RegisterFrameClass();
public:
	friend VTAPI LRESULT CALLBACK StaticMDIWndProc(HWND hWnd,UINT Msg,WPARAM wParam,LPARAM lParam);
	VTAPI LRESULT CALLBACK FrameWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};

class VMDIChildWindow : public VBaseWindow
{
	HWND m_hChildMDIWnd;
	static LPCTSTR m_lpcChildClassName;
	static  ATOM RegisterChildClass();
public:
	explicit VTAPI VMDIChildWindow(LPCTSTR szChildWndTitle = "New Child Window",int nCmdShow = WINDOW_CMDSHOW::dwShowNormal,
    UINT nX = CW_USEDEFAULT,UINT nY = CW_USEDEFAULT,UINT nSx = CW_USEDEFAULT,UINT nSy = CW_USEDEFAULT,
	DWORD dwStyle = WINDOW_STYLE::dwOverlapped);
	VTAPI HWND GetChildMDIWindowHandle()const;
	friend VTAPI LRESULT CALLBACK StaticChildMDIWndProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam);
	VTAPI LRESULT CALLBACK ChildWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};

#endif
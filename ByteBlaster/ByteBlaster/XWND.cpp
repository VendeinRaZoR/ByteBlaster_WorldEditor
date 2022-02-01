#include "XWND.h"
#include "XWNDGUI.h"

XWND_PARAM g_XWNDParam;
XWND_STYLE g_XWNDStyle;
CGUIManager g_GUIManager;

XWND WINAPI XWNDClass::XWNDCreateWindow(const char* strWindowTitle, HINSTANCE hInstance,
                                 HICON hIcon, HMENU hMenu, int x, int y,int sx,int sy)
{
	char szwClassName[] = "WindowClass";
	if(WINVER == _WIN32_WINDOWS)
	{
		InitCommonControls();
	}
	if(g_XWNDStyle == 0)
	{
	    g_XWNDStyle = DEFAULT;
	}
    g_XWNDParam.hWnd = CreateWindowA(szwClassName,strWindowTitle,g_XWNDStyle,x,y,640,480,0,hMenu,hInstance,0);
    g_XWNDParam.phWnd = &g_XWNDParam.hWnd;
    g_XWNDParam.phInst = &g_XWNDParam.hInst;
    ShowWindow(g_XWNDParam.hWnd,SW_SHOWNORMAL);
    return g_XWNDParam.hWnd;
}

VOID XWNDClass::XWNDRegisterClass()
{
	WNDCLASSEX WNDClass;
	memset(&WNDClass,0,sizeof(WNDClass));
	WNDClass.lpszClassName = szwClassName;
	WNDClass.cbSize        = sizeof(WNDCLASSEX);
	WNDClass.style         = CS_HREDRAW | CS_VREDRAW;
	WNDClass.lpfnWndProc   = XWNDWndProc;
	WNDClass.hInstance     = hInstance;
	WNDClass.hIcon	       = hIcon;
    WNDClass.hIconSm	   = hIcon;
	WNDClass.hCursor       = LoadCursor(NULL, IDC_ARROW);
	WNDClass.hbrBackground = (HBRUSH)CreateSolidBrush(g_XWNDParam.crXWNDColor);
	WNDClass.lpszMenuName  = NULL;
	WNDClass.cbClsExtra    = 0;
	WNDClass.cbWndExtra    = 0;
	if(!RegisterClassEx(&WNDClass))
	{
		DWORD Error = GetLastError();
		sprintf(g_XWNDParam.szwLogBuff,"Can't Register WNDClass . Code : %d",Error);
		XWNDLogInfo(g_XWNDParam.szwLogBuff,3);
		return 0;
	}   
}

LRESULT CALLBACK XWNDClass::XWNDWndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	switch(Msg)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
	case WM_DESTROY:
		PostQuitMessage(0);
	}
	return DefWindowProcA(hWnd,Msg,wParam,lParam);
}

BOOL XWNDClass::XWNDUpdateWindow()
{
	   while(1){
      MSG msg;
      BOOL bRet = GetMessage(&msg, 0, 0, 0);
      if (bRet == 0) {
      return msg.wParam;
      } else {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
      }
    }
}
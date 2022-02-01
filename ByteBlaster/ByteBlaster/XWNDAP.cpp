#include "XWND.h"

XWNDClass XWindow;

LRESULT WINAPI XWNDStaticWndProc2(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	return DefWindowProc( hWnd, uMsg, wParam, lParam ); 
}

INT WINAPI _tWinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd)
{
	HINSTANCE hInstance2;
	XWindow.XWNDCreateWindow("ByteBlaster",hInstance,0,0,500,500,500,500);
	XWindow.XWNDUpdateWindow();
  	return S_OK;
}



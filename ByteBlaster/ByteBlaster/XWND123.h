#include <winsock2.h>
#include <windows.h> 
#include <windowsx.h> 
#include <tchar.h>
#include "stdio.h"
#include <iostream>
#include "assert.h"
#include "string.h"
#include <fstream>
#include <ostream>
#include "winnt.h"
#include "commctrl.h"
#include <ctime>

#pragma once
#ifndef XWND_H
#define XWND_H

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

typedef SOCKET CLIENTSOCKET;
typedef HWND XWND;

void XWNDLogInfo(char * prgmsg,int msgtype);

#define ID_COMSTATIC 0
#define WS_STATICWINDOW    WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX 
#define WS_DEFAULTWINDOW   WS_OVERLAPPEDWINDOW | WS_VISIBLE
#define SCREENCENTER_CX GetSystemMetrics(SM_CXSCREEN)/4
#define SCREENCENTER_CY GetSystemMetrics(SM_CYSCREEN)/4

enum XWND_STYLE
{
   STATIC = WS_STATICWINDOW,
   DEFAULT = WS_DEFAULTWINDOW,
};

struct XWND_PARAM
{
HWND* phWnd;
HWND hWnd;
HINSTANCE *phInst;
HINSTANCE hInst;
COLORREF crXWNDColor;
COLORREF *pcrXWNDColor;
char szwLogBuff[256];
};

class XWNDClass {
  public:
static LRESULT CALLBACK XWNDWndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
XWND WINAPI XWNDCreateWindow(const char* strWindowTitle, HINSTANCE hInstance,
                                 HICON hIcon, HMENU hMenu, int x, int y,int sx,int sy);
BOOL WINAPI XWNDUpdateWindow();
};
#endif
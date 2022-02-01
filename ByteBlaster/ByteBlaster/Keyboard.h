#ifndef _KEYBOARD_
#define _KEYBOARD_
#include "Main.h"

struct IBaseKeyboard
{
	virtual LRESULT OnKeyDown(WPARAM)PURE;
	virtual LRESULT OnKeyUp(WPARAM)PURE;
	virtual ~IBaseKeyboard(){};
};

class CBaseKeyboard
{
public:
	CBaseKeyboard(){};
	~CBaseKeyboard(){};
	LRESULT CALLBACK KeyboardProc(HWND hWnd,UINT Msg,WPARAM wParam,LPARAM lParam);
	virtual LRESULT OnKeyDown(WPARAM wKey){return S_OK;};
	virtual LRESULT OnKeyUp(WPARAM wKey){return S_OK;};
protected:
};

inline LRESULT CALLBACK CBaseKeyboard::KeyboardProc(HWND hWnd,UINT Msg,WPARAM wParam,LPARAM lParam) 
{
	switch(Msg)
	{
	case WM_KEYDOWN:
OnKeyDown(wParam);
    break;
	case WM_KEYUP:
OnKeyUp(wParam);
    break;
	}
return DefWindowProc(hWnd,Msg,wParam,lParam);
}
#endif
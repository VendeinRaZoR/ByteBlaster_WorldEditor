#include "VApplication.h"
#include "VEventHandler.h"

struct IBaseKeyboard
{
	virtual LRESULT OnKeyDown(wParam)PURE;
	virtual LRESULT OnKeyUp(wParam)PURE;
	virtual ~IBaseKeyboard(){};
};

class VInput
{
VEvent * KeyEvent;
VEvent * MouseEvent;
public:
static VBaseWindow *m_pBaseWindow;
VInput()
{
KeyEvent = new VEvent();
MouseEvent = new VEvent();
}
bool isPressed()
{
	KeyEvent->Set(WM_KEYDOWN);
	return (KeyEvent->isActive() ? 1 : 0);
}
bool isUpped()
{
	KeyEvent->Set(WM_KEYUP);
	return (KeyEvent->isActive() ? 1 : 0);
}
bool isMousePressed()
{
	KeyEvent->Set(WM_LBUTTONUP);
	return (KeyEvent->isActive() ? 1 : 0);
}
bool isMouseUpped()
{
	KeyEvent->Set(WM_LBUTTONDOWN);
	return (KeyEvent->isActive() ? 1 : 0);
}
bool KeyState(int nVirtKey)
{
    //wParam wParam = KeyEvent->GetEventParam("Param1"); - ещё 1 поток
	//printf("%x",KeyEvent->GetEventParam("Param1"));
	//return (wParam == nVirtKey) ? 1 : 0;
	return GetAsyncKeyState(nVirtKey);
}
	~VInput()
	{
		delete KeyEvent;
	}
};

VBaseWindow *VInput::m_pBaseWindow = 0;

void VT_InitializeKeyboard(VBaseWindow * pBaseWindow)
{
	VInput::m_pBaseWindow = pBaseWindow;
}
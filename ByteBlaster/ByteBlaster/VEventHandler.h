#ifndef _VEVENTHANDLER_
#define _VEVENTHANDLER_

#include "VWindow.h"

class VEvent
{
VBaseWindow * m_pBaseWindow;
UINT m_dwEvent;
public:
	VTAPI VEvent(VBaseWindow * pBaseWindow = NULL,DWORD dwEvent = 0);
public:
	VTAPI ~VEvent();
	VTAPI void Set(DWORD dwEvent);
	VTAPI
	VTAPI bool isActive();
	VTAPI DWORD GetEvent();
	VTAPI void SetEventParam(void * wParam,void * Param2);
	VTAPI LONG_PTR GetEventParam(VString ParamType);
};

class VEventHandler
{
	list<VEvent*>m_lEvent;
	VBaseWindow * m_pBaseWindow;
public:
    VTAPI VEventHandler(VBaseWindow * pBaseWindow = NULL);
	VTAPI ~VEventHandler();
public:
	VTAPI void AddEvent(DWORD dwEvent);
	VTAPI void DeleteEvent();
	VTAPI VEvent * GetEventByType(DWORD dwEvent);
	VTAPI void CallStatic();
	VTAPI void StartEvents();

};

#endif
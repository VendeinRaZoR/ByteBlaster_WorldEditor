#include "VApplication.h"
#include "VEventHandler.h"

class VTimer
{
int m_nInterval;
UINT m_uElapse;
HWND m_hWnd; //TODO : VObject(QObject) in progress !!!
VEvent m_vEvent;
public:
	VTimer(){}
		~VTimer(){KillTimer(m_hWnd,NULL);}
		void Set(HWND hWnd,UINT uElapse);
		void SetElapse(UINT uElapse)
		{
			m_uElapse = uElapse;
		}
		static TIMERPROC TimeProc(HWND, UINT, UINT_PTR, DWORD)
		{
        return 0;
		}
		bool isActive()
		{
			return m_vEvent.isActive() ? 1 : 0;
		}
};

void VTimer::Set(HWND hWnd,UINT uElapse)
		{
			m_hWnd = hWnd;
			SetTimer(hWnd,NULL,uElapse,NULL);
			m_vEvent.Set(WM_TIMER);
		}
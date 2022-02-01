#ifndef _CRENDERWINDOW_H_
#define _CRENDERWINDOW_H_
#include "CMainWindow.h"
#include "VTGL_Device.h"
#include "VTGL_Geometry.h"

class CRenderWindow : public wxWindow 
{
	VTGL_Device *m_pGraphDevice;
	wxWindow * m_pParentWindow;
	float m_fLastTime;
public:
	CRenderWindow(wxString &szDeviceChoose,wxWindow * pParentWindow,const wxPoint &pos,const wxSize &size);
	~CRenderWindow();
	void OnExit();
	void OnRender(float fTimeDelta);
	void OnIdle(wxIdleEvent &event);
	void SetRenderDevice(wxString &szDeviceChoose);
	//Another windows methods
	void OnScroll(wxScrollEvent& event);
private:
DECLARE_EVENT_TABLE()
};

#endif
#ifndef _VTGL_DEVICE_H_
#define _VTGL_DEVICE_H_
#include "VTGL_Math.h"

#include <wx/wxprec.h>
  #ifndef WX_PRECOMP
    #include <wx/wx.h>
  #endif

#include <vector>

#define ONRENDER(window,a) wxBEGIN_EVENT_TABLE(window, wxWindow) \
	EVT_IDLE(window::a) \
wxEND_EVENT_TABLE() 

class VTGL_Device;

typedef void(VTGL_Device::*pRenderFunction)(float fTimeDelta);

///////////
class VTGL_BaseDevice
{
protected:
	wxWindow *m_pParentWindow;
	char* m_szMatrixMode;
public:
	VTGL_BaseDevice(wxWindow * pParentWindow = NULL);
virtual ~VTGL_BaseDevice();
	virtual bool Init(wxWindow * pParentWindow,bool bWindowed,int nResX,int nResY)=0;
	virtual void BeginRender()=0;
	virtual void EndRender()=0;
	virtual void Clear(DWORD dwFlags,wxColor &Color)=0;
	virtual wxPoint GetResolution()=0;
	virtual void Release()=0;
	virtual void SetTransform(VTMatrix4*)=0;
	virtual void SetMatrixMode(char *szType)=0;
	virtual DWORD vtglCLEARCOLOR()const = 0;
	virtual DWORD vtglCLEARDEPTH()const = 0;
	virtual DWORD vtglCLEARSTENCIL()const = 0;
	virtual void SetRenderMode(int vtglRenderMode) = 0;
};

/*#if g_IsOpenGL
#define __OPENGL__
#else
#define __DIRECTX__
#endif*/

/*#if defined(__OPENGL__)
      #define VTGL_Device VTGL_Device_OGL
      #include "VTGL_Device_OGL.h"
#endif 

#if defined(__DIRECTX__)
      #define VTGL_Device VTGL_Device_DX
      #include "VTGL_Device_DX.h"
#endif*/

enum //Kinds of Render Modes
{
	VTGLRM_GRID,
	VTGLRM_SOLID,
	VTGLRM_POINT,
	VTGLRM_ZENABLE,
	VTGLRM_ZDISABLE,
	VTGLRM_CULLMODE_CW,
	VTGLRM_CULLMODE_CCW,
	VTGLRM_CULLMODE_NONE
};

class VTGL_Device : public VTGL_BaseDevice /*, public wxWindow*/
{
	pRenderFunction m_pRenderFunction;
	wxPoint m_pRes;
	VTGL_BaseDevice * m_pBaseDevice;
public:
    static wxString *m_pszGraphicsApiChoice;
public:
explicit VTGL_Device(wxString &szGraphicsApiChoice,wxWindow * pParentWindow,bool bWindowed,int nResX,int nResY);
~VTGL_Device();
	virtual bool Init(wxWindow * pParentWindow,bool bWindowed,int nResX,int nResY);
	virtual void BeginRender();
	virtual void EndRender();
	virtual void Clear(DWORD dwFlags,wxColor &Color);
	virtual wxPoint GetResolution();
	virtual void Release();
	virtual void SetTransform(VTMatrix4*);
	virtual void SetMatrixMode(char *szType);
	VTGL_BaseDevice * GetBaseDevice(){return m_pBaseDevice;}
	virtual void SetRenderMode(int vtglRenderMode);
	/*	void OnIdle(wxIdleEvent &event)
	{
		printf("On Idle");
(this->*m_pRenderFunction)(0);
	}
	template <class T> void SetRenderFunction(T * pRenderObject,void (T::*_pRenderFunction)(float))
	{
		m_pRenderFunction = NULL;
		m_pParentWindow->Connect(wxEVT_IDLE,wxIdleEventHandler(VTGL_Device::OnIdle));
		m_pRenderFunction = (pRenderFunction)_pRenderFunction;
	}*/
	virtual DWORD vtglCLEARCOLOR()const{return m_pBaseDevice->vtglCLEARCOLOR();}
	virtual DWORD vtglCLEARDEPTH()const{return m_pBaseDevice->vtglCLEARDEPTH();}
	virtual DWORD vtglCLEARSTENCIL()const{return m_pBaseDevice->vtglCLEARSTENCIL();}
};

#endif
#ifndef _VTGL_DEVICE_DX_H_
#define _VTGL_DEVICE_DX_H_
#include "VTGL_Device.h"
#include <d3d9.h>
#include <d3dx9.h>

class VTGL_Device_DX : public VTGL_BaseDevice
{
IDirect3D9* m_pD3D;
IDirect3DDevice9 * m_pDirect3DDevice;
wxPoint m_pRes;
public:
VTGL_Device_DX(wxWindow * pParentWindow,bool bWindowed,int nResX,int nResY);
~VTGL_Device_DX();
	virtual bool Init(wxWindow * pParentWindow,bool bWindowed,int nResX,int nResY);
	virtual void BeginRender();
	virtual void EndRender();
	virtual void Clear(DWORD dwFlags,wxColor &Color);
	virtual wxPoint GetResolution();
	virtual void Release();
	virtual void SetTransform(VTMatrix4*);
	virtual void SetMatrixMode(char * szType);
	IDirect3DDevice9 * GetDevice();
	virtual void SetRenderMode(int vtglRenderMode);
public:
	virtual DWORD vtglCLEARCOLOR()const{return D3DCLEAR_TARGET;}
	virtual DWORD vtglCLEARDEPTH()const{return D3DCLEAR_ZBUFFER;}
	virtual DWORD vtglCLEARSTENCIL()const{return D3DCLEAR_STENCIL;}
};

#endif
#ifndef DXVT_DEVICE_H
#define DXVT_DEVICE_H

#include "DXVT.h"

struct DXVT_Param
{
D3DDEVTYPE D3D_DevType;
D3DSWAPEFFECT D3D_SwapEffect;
bool bWindowed;
D3DFORMAT D3D_AutoDepthStencilFormat;
};

class DXVTDevice : public DXVT
{
VBaseWindow * m_pBaseWindow;
IDirect3DDevice9 * m_pDirect3DDevice;
int m_nResX;
int m_nResY;
public:
	DXVTDevice(VBaseWindow * pBaseWindow);
	~DXVTDevice();
	void Create(DXVT_Param * dxvtParam,int nResX,int nResY);
	void BeginRender();
	void EndRender();
	void Clear(DWORD dwFlags,D3DCOLOR d3d_Color);
	int GetResolutionX();
	int GetResolutionY();
	operator IDirect3DDevice9*();
	IDirect3DDevice9* operator->();
	VBaseWindow * GetDeviceWindow();
};

#endif
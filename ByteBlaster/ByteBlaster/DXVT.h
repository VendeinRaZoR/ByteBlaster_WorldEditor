#include <d3d9.h>
#include <d3dx9.h>

#include "VWindow.h"


     const D3DXCOLOR     WHITE(D3DCOLOR_XRGB(255, 255, 255));
     const D3DXCOLOR     BLACK(D3DCOLOR_XRGB(  0,   0,   0));
     const D3DXCOLOR       RED(D3DCOLOR_XRGB(255,   0,   0));
     const D3DXCOLOR     GREEN(D3DCOLOR_XRGB(  0, 255,   0));
     const D3DXCOLOR      BLUE(D3DCOLOR_XRGB(  0,   0, 255));
     const D3DXCOLOR    YELLOW(D3DCOLOR_XRGB(255, 255,   0));
     const D3DXCOLOR      CYAN(D3DCOLOR_XRGB(  0, 255, 255));
     const D3DXCOLOR   MAGENTA(D3DCOLOR_XRGB(255,   0, 255));


class DXVT
{
protected:
	D3DCAPS9 d3dCaps;
	D3DDISPLAYMODE d3ddm;
    IDirect3D9* m_pD3D;
public:
DXVT();
~DXVT();
D3DCAPS9 * Init(D3DDEVTYPE D3D_DevType);
void BeginRender();
void EndRender();
void Clear(DWORD dwFlags,D3DCOLOR d3d_Color);
VTAPI operator IDirect3D9*();
};
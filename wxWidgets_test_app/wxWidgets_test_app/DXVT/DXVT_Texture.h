#include "DXVT_Device.h"

class DXVTTexture
{
DXVTDevice * m_pDXVTDevice;
IDirect3DTexture9 * m_pTexture;
D3DLOCKED_RECT m_LockedRect;
D3DSURFACE_DESC *m_pSurfDesc;
public:
   DXVTTexture(DXVTDevice * pDXVTDevice);
   ~DXVTTexture();
   void Create(int nWidth,int nHeight);
   void Load(char * szFileName);
   D3DLOCKED_RECT GetRect();
   void SetRect();
   D3DSURFACE_DESC *GetDesc();
   void Set();
   IDirect3DTexture9* operator->();
};
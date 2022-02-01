#include "DXVT_Device.h"

class DXVTBaseLight
{
	DXVTDevice *m_pDXVTDevice;
public:
	DXVTBaseLight(DXVTDevice *pDXVTDevice);
	~DXVTBaseLight();
   void CreatePoint(D3DCOLORVALUE Ambient,D3DCOLORVALUE Diffuse,D3DCOLORVALUE Specular,D3DXVECTOR3 *pPosition);
   void CreateDirectional(D3DCOLORVALUE Ambient,D3DCOLORVALUE Diffuse,D3DCOLORVALUE Specular,D3DXVECTOR3 * pDirection);
   void CreateSpot(D3DCOLORVALUE Ambient,D3DCOLORVALUE Diffuse,D3DCOLORVALUE Specular,D3DXVECTOR3 * pPosition,D3DXVECTOR3 * pDirection,float fPhi,float fTheta);
   void Draw();
};
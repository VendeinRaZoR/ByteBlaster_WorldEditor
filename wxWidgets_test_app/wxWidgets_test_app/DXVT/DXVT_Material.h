#include "DXVT_Device.h"


class DXVTBaseMaterial
{
	D3DMATERIAL9 m_Material;
	DXVTDevice *m_pDXVTDevice;
public:
	DXVTBaseMaterial(DXVTDevice *pDXVTDevice);
	~DXVTBaseMaterial();
	void Apply(D3DCOLORVALUE Ambient,D3DCOLORVALUE Diffuse,D3DCOLORVALUE Specular,D3DCOLORVALUE Emissive,float Power);
};
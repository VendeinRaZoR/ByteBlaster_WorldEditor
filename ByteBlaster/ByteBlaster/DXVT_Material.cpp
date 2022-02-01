#include "DXVT_Material.h"


DXVTBaseMaterial::DXVTBaseMaterial(DXVTDevice *pDXVTDevice)
{
	m_pDXVTDevice = pDXVTDevice;
}

DXVTBaseMaterial::~DXVTBaseMaterial()
{

}

void DXVTBaseMaterial::Apply(D3DCOLORVALUE Ambient,D3DCOLORVALUE Diffuse,D3DCOLORVALUE Specular,D3DCOLORVALUE Emissive,float Power)
{
	      m_Material.Ambient  = GREEN;
          m_Material.Diffuse  = GREEN;
          m_Material.Specular = GREEN;
          m_Material.Emissive = BLACK;
          m_Material.Power    = 8.0f;
     (*m_pDXVTDevice)->SetMaterial(&m_Material);
}
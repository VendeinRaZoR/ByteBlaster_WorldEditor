#include "DXVT_Light.h"

DXVTBaseLight::DXVTBaseLight(DXVTDevice *pDXVTDevice)
{
	m_pDXVTDevice = pDXVTDevice;
	(*m_pDXVTDevice)->SetRenderState(D3DRS_LIGHTING, true);
}

DXVTBaseLight::~DXVTBaseLight()
{

}

void DXVTBaseLight::CreateDirectional(D3DCOLORVALUE Ambient,D3DCOLORVALUE Diffuse,D3DCOLORVALUE Specular,D3DXVECTOR3 * pDirection)
{
	D3DLIGHT9 dir;
     ZeroMemory(&dir, sizeof(dir));

     dir.Type      = D3DLIGHT_DIRECTIONAL;
     dir.Diffuse   = Diffuse;
     dir.Specular  = Specular;
     dir.Ambient   = Ambient;
     dir.Direction = *pDirection;

     (*m_pDXVTDevice)->SetLight(0, &dir);
     (*m_pDXVTDevice)->LightEnable(0, true);
}

void DXVTBaseLight::CreateSpot(D3DCOLORVALUE Ambient,D3DCOLORVALUE Diffuse,D3DCOLORVALUE Specular,D3DXVECTOR3 * pPosition,D3DXVECTOR3 * pDirection,float fPhi,float fTheta)
{
	D3DLIGHT9 spot;
     ZeroMemory(&spot, sizeof(spot));

     spot.Type      = D3DLIGHT_SPOT;
     spot.Diffuse   = Diffuse;
     spot.Specular  = Specular;
     spot.Ambient   = Ambient;
	 spot.Position = *pPosition;
	 spot.Direction = *pDirection;
	 spot.Theta = fTheta;
	 spot.Phi = fPhi;
	 spot.Falloff = 1.0f;
	 

     (*m_pDXVTDevice)->SetLight(0, &spot);
     (*m_pDXVTDevice)->LightEnable(0, true);
}

void DXVTBaseLight::CreatePoint(D3DCOLORVALUE Ambient,D3DCOLORVALUE Diffuse,D3DCOLORVALUE Specular,D3DXVECTOR3 *pPosition)
{
	D3DLIGHT9 point;
     ZeroMemory(&point, sizeof(point));

     point.Type      = D3DLIGHT_SPOT;
     point.Diffuse   = Diffuse;
     point.Specular  = Specular;
     point.Ambient   = Ambient;
	 point.Position = *pPosition;

     (*m_pDXVTDevice)->SetLight(0, &point);
     (*m_pDXVTDevice)->LightEnable(0, true);
}

void DXVTBaseLight::Draw()
{
	(*m_pDXVTDevice)->SetRenderState(D3DRS_NORMALIZENORMALS, true);
     (*m_pDXVTDevice)->SetRenderState(D3DRS_SPECULARENABLE, true);
}

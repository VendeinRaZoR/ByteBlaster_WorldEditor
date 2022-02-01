#include "DXVT_Texture.h"


DXVTTexture::DXVTTexture(DXVTDevice* pDXVTDevice)
{
	m_pDXVTDevice = pDXVTDevice;
	m_pTexture = 0;
	m_LockedRect.pBits = 0;
}

DXVTTexture::~DXVTTexture()
{

}

void DXVTTexture::Create(int nWidth,int nHeight)
{
	D3DXCreateTexture(
		*m_pDXVTDevice,
		nWidth, nHeight,
		0, // create a complete mipmap chain
		0, // usage
		D3DFMT_X8R8G8B8,// 32 bit XRGB format
		D3DPOOL_MANAGED, &m_pTexture);
}

void DXVTTexture::Load(char *szFileName)
{
	if(FAILED(D3DXCreateTextureFromFile(*m_pDXVTDevice,szFileName,&m_pTexture)))
	{
		MessageBoxA(*m_pDXVTDevice->GetDeviceWindow(),"Load Texture - Failed()","Error",MB_ICONWARNING);
	}
}

void DXVTTexture::SetRect()
{
	m_pTexture->UnlockRect(0);
}

D3DLOCKED_RECT DXVTTexture::GetRect()
{
    m_pTexture->LockRect(0,&m_LockedRect,0,0);
	return m_LockedRect;
}

D3DSURFACE_DESC * DXVTTexture::GetDesc()
{
	m_pSurfDesc = new D3DSURFACE_DESC();
	m_pTexture->GetLevelDesc(0, m_pSurfDesc);
	return m_pSurfDesc;
}

void DXVTTexture::Set()
{
	(*m_pDXVTDevice)->SetTexture(0,m_pTexture);
}

IDirect3DTexture9* DXVTTexture::operator->()
{
	return m_pTexture;
}

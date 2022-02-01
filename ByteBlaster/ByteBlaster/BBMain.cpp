#include "BBMain.h"

/*
BBMain::BBMain()
{
m_pDXVTDevice = new DXVTDevice(this);
	DXVT_Param dxvtParams;
	dxvtParams.bWindowed = true;
	dxvtParams.D3D_AutoDepthStencilFormat = D3DFMT_D16;
	dxvtParams.D3D_DevType = D3DDEVTYPE_HAL;
    dxvtParams.D3D_SwapEffect = D3DSWAPEFFECT_DISCARD;
	m_pDXVTDevice->Create(&dxvtParams,SCREEN_X,SCREEN_Y);
	m_pCamera = new DXVTCamera(m_pDXVTDevice);
	m_pDXVTFont = new DXVTFont(m_pDXVTDevice,"Times New Roman",12);
}

BBMain::~BBMain()
{

}

void BBMain::InitEngine()
{
	m_pCamera->SetProjectionMatrix(D3DX_PI/2,1000.0f);
	m_pCamera->SetViewMatrix(0.0f,10.0f,0.0f);
	m_pDXVTFont->CreateText();
    (*m_pDXVTDevice)->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_ANISOTROPIC);
	(*m_pDXVTDevice)->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC);
	(*m_pDXVTDevice)->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_ANISOTROPIC);
}

void BBMain::Render(float fTimeDelta)
{
}

DXVTDevice * BBMain::GetDevice()
{
	return m_pDXVTDevice;
}*/
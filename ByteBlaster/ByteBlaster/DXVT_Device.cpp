#include "DXVT_Device.h"

DXVTDevice::DXVTDevice(VBaseWindow * pBaseWindow)
{
	m_pBaseWindow = pBaseWindow;
}


void DXVTDevice::Create(DXVT_Param * dxvtParam,int nResX,int nResY)
{
	Init(dxvtParam->D3D_DevType);
	DWORD dwBehaviorFlags = 0;

	if( d3dCaps.VertexProcessingCaps != 0 )
		dwBehaviorFlags |= D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
		dwBehaviorFlags |= D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	D3DPRESENT_PARAMETERS d3dpp;
	memset(&d3dpp, 0, sizeof(d3dpp));
    m_nResX = nResX;
	m_nResY = nResY;
	d3dpp.BackBufferFormat       = d3ddm.Format;
	d3dpp.BackBufferHeight       = m_nResY;
	d3dpp.BackBufferWidth        = m_nResX;
	d3dpp.SwapEffect             = dxvtParam->D3D_SwapEffect;
	d3dpp.Windowed               = dxvtParam->bWindowed;
    d3dpp.EnableAutoDepthStencil = TRUE;
    d3dpp.AutoDepthStencilFormat = dxvtParam->D3D_AutoDepthStencilFormat;
    d3dpp.PresentationInterval   = D3DPRESENT_INTERVAL_IMMEDIATE;
	d3dpp.hDeviceWindow          = *m_pBaseWindow;

    if( FAILED( m_pD3D->CreateDevice( D3DADAPTER_DEFAULT, dxvtParam->D3D_DevType, *m_pBaseWindow,
                                      dwBehaviorFlags, &d3dpp, &m_pDirect3DDevice ) ) )
	{
		if( m_pD3D != NULL )
			m_pD3D->Release();

		::MessageBox(0, "CreateDevice() - Failed", 0, 0);
	}
}

int DXVTDevice::GetResolutionX()
{
	return m_nResX;
}
int DXVTDevice::GetResolutionY()
{
    return m_nResY;
}

DXVTDevice::operator IDirect3DDevice9*()
{
	return m_pDirect3DDevice;
}

void DXVTDevice::BeginRender()
{
    m_pDirect3DDevice->BeginScene();
}

void DXVTDevice::EndRender()
{
	m_pDirect3DDevice->EndScene();
    m_pDirect3DDevice->Present( NULL, NULL, NULL, NULL );
}

void DXVTDevice::Clear(DWORD dwFlags,D3DCOLOR d3d_Color)
{
	m_pDirect3DDevice->Clear( 0, NULL,dwFlags, d3d_Color, 1.0f, 0 );
}

IDirect3DDevice9* DXVTDevice::operator->()
{
return m_pDirect3DDevice;
}

VBaseWindow * DXVTDevice::GetDeviceWindow()
{
return m_pBaseWindow;
}

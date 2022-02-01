#include "VTGL_Device_DX.h"

VTGL_Device_DX::VTGL_Device_DX(wxWindow * pParentWindow,bool bWindowed,int nResX,int nResY):VTGL_BaseDevice(pParentWindow)
{
m_pD3D = NULL;
m_pDirect3DDevice = NULL;
Init(pParentWindow,bWindowed,nResX,nResY);
}

VTGL_Device_DX::~VTGL_Device_DX()
{
if(m_pDirect3DDevice)
m_pDirect3DDevice->Release();
if(m_pD3D)
m_pD3D->Release();
}

bool VTGL_Device_DX::Init(wxWindow * pParentWindow,bool bWindowed,int nResX,int nResY)
{
  m_pD3D = Direct3DCreate9( D3D_SDK_VERSION );

	if( !m_pD3D )
	{
		if( m_pD3D != NULL )
			m_pD3D->Release();

		::MessageBox(0, wxT("Direct3DCreate9() - Failed"), 0, 0);
		return NULL;
	}
        D3DCAPS9 d3dCaps;
		if( FAILED( m_pD3D->GetDeviceCaps( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &d3dCaps ) ) )
	{
		if( m_pD3D != NULL )
			m_pD3D->Release();

		::MessageBox(0, wxT("GetDeviceCaps() - Failed"), 0, 0);
		return NULL;
	}
    D3DDISPLAYMODE d3ddm;
    m_pD3D->GetAdapterDisplayMode( D3DADAPTER_DEFAULT, &d3ddm );

	DWORD dwBehaviorFlags = 0;

	if( d3dCaps.VertexProcessingCaps != 0 )
		dwBehaviorFlags |= D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
		dwBehaviorFlags |= D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	D3DPRESENT_PARAMETERS d3dpp;
	memset(&d3dpp, 0, sizeof(d3dpp));
    m_pRes.x = nResX;
	m_pRes.y = nResY;
	d3dpp.BackBufferWidth            = nResX;
	d3dpp.BackBufferHeight           = nResY;
	d3dpp.BackBufferFormat           = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount            = 1;
	d3dpp.MultiSampleType            = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality         = 0;
	d3dpp.SwapEffect                 = D3DSWAPEFFECT_DISCARD; 
	d3dpp.Windowed                   = bWindowed;
	d3dpp.EnableAutoDepthStencil     = true; 
	d3dpp.AutoDepthStencilFormat     = D3DFMT_D24S8;
	d3dpp.Flags                      = 0;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval       = D3DPRESENT_INTERVAL_IMMEDIATE;
	d3dpp.hDeviceWindow          = pParentWindow->GetHWND();

    if( FAILED( m_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, pParentWindow->GetHWND(),
                                      dwBehaviorFlags, &d3dpp, &m_pDirect3DDevice ) ) )
	{
		if( m_pD3D != NULL )
			m_pD3D->Release();
		::MessageBox(0, wxT("CreateDevice() - Failed"), 0, 0);
	}
	printf("\nThis is a DirectX version");
}

wxPoint VTGL_Device_DX::GetResolution()
{
	return m_pRes;
}

void VTGL_Device_DX::BeginRender()
{
    m_pDirect3DDevice->BeginScene();
}

void VTGL_Device_DX::EndRender()
{
	m_pDirect3DDevice->EndScene();
    m_pDirect3DDevice->Present( NULL, NULL, NULL, NULL );
}

void VTGL_Device_DX::Clear(DWORD dwFlags,wxColor &Color)
{
	m_pDirect3DDevice->Clear( 0, NULL,dwFlags, Color.GetRGB(), 1.0f, 0 );
}

void VTGL_Device_DX::Release()
{
if(m_pDirect3DDevice)
m_pDirect3DDevice->Release(); 
if(m_pD3D)
m_pD3D->Release();
}

void VTGL_Device_DX::SetTransform(VTMatrix4 * vtMatrix)
{
	if(!strcmp(m_szMatrixMode,"World"))
	m_pDirect3DDevice->SetTransform(D3DTS_WORLD,&D3DXMATRIX(
		vtMatrix->f_11,vtMatrix->f_12,vtMatrix->f_13,vtMatrix->f_14,
		vtMatrix->f_21,vtMatrix->f_22,vtMatrix->f_23,vtMatrix->f_24,
		vtMatrix->f_31,vtMatrix->f_32,vtMatrix->f_33,vtMatrix->f_34,
		vtMatrix->f_41,vtMatrix->f_42,vtMatrix->f_43,vtMatrix->f_44));
	if(!strcmp(m_szMatrixMode,"Projection"))
	m_pDirect3DDevice->SetTransform(D3DTS_PROJECTION,&D3DXMATRIX(
		vtMatrix->f_11,vtMatrix->f_12,vtMatrix->f_13,vtMatrix->f_14,
		vtMatrix->f_21,vtMatrix->f_22,vtMatrix->f_23,vtMatrix->f_24,
		vtMatrix->f_31,vtMatrix->f_32,vtMatrix->f_33,vtMatrix->f_34,
		vtMatrix->f_41,vtMatrix->f_42,vtMatrix->f_43,vtMatrix->f_44));
	if(!strcmp(m_szMatrixMode,"View"))
	m_pDirect3DDevice->SetTransform(D3DTS_VIEW,&D3DXMATRIX(
		vtMatrix->f_11,vtMatrix->f_12,vtMatrix->f_13,vtMatrix->f_14,
		vtMatrix->f_21,vtMatrix->f_22,vtMatrix->f_23,vtMatrix->f_24,
		vtMatrix->f_31,vtMatrix->f_32,vtMatrix->f_33,vtMatrix->f_34,
		vtMatrix->f_41,vtMatrix->f_42,vtMatrix->f_43,vtMatrix->f_44));
}

void VTGL_Device_DX::SetMatrixMode(char* szType)
{
m_szMatrixMode = szType;
}

IDirect3DDevice9 * VTGL_Device_DX::GetDevice()
{
	return m_pDirect3DDevice;
}

void VTGL_Device_DX::SetRenderMode(int vtglRenderMode)
{
	switch(vtglRenderMode)
	{
	case VTGLRM_POINT:
m_pDirect3DDevice->SetRenderState(D3DRS_FILLMODE,D3DFILL_POINT);
		break;
	case VTGLRM_GRID:
m_pDirect3DDevice->SetRenderState(D3DRS_FILLMODE,D3DFILL_WIREFRAME);
		break;
	case VTGLRM_SOLID:
m_pDirect3DDevice->SetRenderState(D3DRS_FILLMODE,D3DFILL_SOLID);
		break;
	case VTGLRM_ZENABLE:
m_pDirect3DDevice->SetRenderState(D3DRS_ZENABLE,true);
		break;
	case VTGLRM_ZDISABLE:
m_pDirect3DDevice->SetRenderState(D3DRS_ZENABLE,false);
		break;
	case VTGLRM_CULLMODE_CCW:
m_pDirect3DDevice->SetRenderState(D3DRS_CULLMODE,D3DCULL_CCW);
		break;
	case VTGLRM_CULLMODE_CW:
m_pDirect3DDevice->SetRenderState(D3DRS_CULLMODE,D3DCULL_CW);
		break;
	case VTGLRM_CULLMODE_NONE:
m_pDirect3DDevice->SetRenderState(D3DRS_CULLMODE,D3DCULL_NONE);
		break;
	}
}

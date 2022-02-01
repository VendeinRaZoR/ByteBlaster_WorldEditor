#include "DXVT.h"


DXVT::DXVT()
{
m_pD3D = NULL;
}

DXVT::~DXVT()
{

}

D3DCAPS9 * DXVT::Init(D3DDEVTYPE D3D_DevType)
{
    m_pD3D = Direct3DCreate9( D3D_SDK_VERSION );

	if( !m_pD3D )
	{
		if( m_pD3D != NULL )
			m_pD3D->Release();

		::MessageBox(0, "Direct3DCreate9() - Failed", 0, 0);
		return NULL;
	}

		if( FAILED( m_pD3D->GetDeviceCaps( D3DADAPTER_DEFAULT, D3D_DevType, &d3dCaps ) ) )
	{
		if( m_pD3D != NULL )
			m_pD3D->Release();

		::MessageBox(0, "GetDeviceCaps() - Failed", 0, 0);
		return NULL;
	}

    m_pD3D->GetAdapterDisplayMode( D3DADAPTER_DEFAULT, &d3ddm );

 return &d3dCaps; /// Пока так будет )))
}

DXVT::operator IDirect3D9*()
{
	return m_pD3D;
}
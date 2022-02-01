#include "VTGL_Device.h"
#include "VTGL_Device_DX.h"
#include "VTGL_Device_OGL.h"

wxString * VTGL_Device::m_pszGraphicsApiChoice = NULL;

VTGL_BaseDevice::VTGL_BaseDevice(wxWindow * pParentWindow):m_szMatrixMode(0)
{
	m_pParentWindow = pParentWindow;
}

VTGL_BaseDevice::~VTGL_BaseDevice()
{

}

VTGL_Device::VTGL_Device(wxString &szGraphicsApiChoice,wxWindow * pParentWindow,bool bWindowed,int nResX,int nResY):VTGL_BaseDevice(pParentWindow)
{
m_pBaseDevice = NULL;
m_pszGraphicsApiChoice = new wxString(szGraphicsApiChoice);

Init(pParentWindow,bWindowed,nResX,nResY);
}

VTGL_Device::~VTGL_Device()
{
m_pBaseDevice->Release();
}

bool VTGL_Device::Init(wxWindow * pParentWindow,bool bWindowed,int nResX,int nResY)
{
if(m_pBaseDevice)
{
	delete m_pBaseDevice;
}
m_pRes.x = nResX;
m_pRes.y = nResY;
if(!m_pszGraphicsApiChoice->Cmp("OpenGL"))
{
m_pBaseDevice = new VTGL_Device_OGL(pParentWindow,bWindowed,nResX,nResY);
}
if(!m_pszGraphicsApiChoice->Cmp("DirectX"))
{
m_pBaseDevice = new VTGL_Device_DX(pParentWindow,bWindowed,nResX,nResY);
}
return true;//update for error msgs !!!
}

void VTGL_Device::Clear(DWORD dwFlags, wxColor &Color)
{
	m_pBaseDevice->Clear(dwFlags,Color);
}

void VTGL_Device::BeginRender()
{
	m_pBaseDevice->BeginRender();
}

void VTGL_Device::EndRender()
{
	m_pBaseDevice->EndRender();
}

void VTGL_Device::SetTransform(VTMatrix4 * vtMatrix)
{
	m_pBaseDevice->SetTransform(vtMatrix);
}

void VTGL_Device::SetMatrixMode(char *szType)
{
	m_pBaseDevice->SetMatrixMode(szType);
}

wxPoint VTGL_Device::GetResolution()
{
	return m_pRes;
}

void VTGL_Device::Release()
{
	delete m_pszGraphicsApiChoice;
	delete m_pBaseDevice;
	m_pBaseDevice = NULL;
}

void VTGL_Device::SetRenderMode(int vtglRenderMode)
{
m_pBaseDevice->SetRenderMode(vtglRenderMode);
}



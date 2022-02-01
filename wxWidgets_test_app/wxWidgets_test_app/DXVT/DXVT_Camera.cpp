#include "DXVT_Camera.h"


DXVTCamera::DXVTCamera(DXVTDevice *pDXVTDevice)
{
	m_pDXVTDevice = pDXVTDevice;
	m_vPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vRight = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	m_vUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_vLook = D3DXVECTOR3(0.0f,0.0f,1.0f);
	m_fPitch = m_fYaw = 0;
}

DXVTCamera::~DXVTCamera()
{

}
const float Epsilon = 0.001f;
void DXVTCamera::Pitch(float fAngle)
{
	D3DXMATRIX T;
	m_fPitch += fAngle;
	/*if(m_fPitch > D3DX_PI/2)
	{
        m_fPitch = D3DX_PI/2;
		fAngle = 0.0;
    }
	if(m_fPitch < -D3DX_PI/2)
	{
		m_fPitch = -D3DX_PI/2;
		fAngle = 0.0;
	}*/
		D3DXMatrixRotationAxis(&T,&m_vRight,fAngle);
	D3DXVec3TransformCoord(&m_vUp,&m_vUp, &T);
	D3DXVec3TransformCoord(&m_vLook,&m_vLook, &T);

}

void DXVTCamera::Yaw(float fAngle)
{
	D3DXMATRIX T;
	m_fYaw += fAngle;
	if(m_fYaw > 2*D3DX_PI)
	{
		m_fYaw = 0.0f;
    }
		if(m_fYaw < -2*D3DX_PI)
	{
		m_fYaw = 0.0f;
	}
    D3DXMatrixRotationY(&T,fAngle);

	D3DXVec3TransformCoord(&m_vRight,&m_vRight, &T);
	D3DXVec3TransformCoord(&m_vLook,&m_vLook, &T);
}

void DXVTCamera::Roll(float fAngle)
{
        D3DXMATRIX T;
		D3DXMatrixRotationAxis(&T, &m_vLook,fAngle);

		D3DXVec3TransformCoord(&m_vRight,&m_vRight, &T);
		D3DXVec3TransformCoord(&m_vUp,&m_vUp, &T);
} 

void DXVTCamera::SetProjectionMatrix(float fFOV,float fDistance)
{
	D3DXMatrixPerspectiveFovLH(&m_mProjection,fFOV,(float)m_pDXVTDevice->GetResolutionX() / (float)m_pDXVTDevice->GetResolutionY(),1.0f,fDistance);
    (*m_pDXVTDevice)->SetTransform(D3DTS_PROJECTION, &m_mProjection);
}

void DXVTCamera::SetViewMatrix(float fPosX,float fPosY,float fPosZ)
{
	m_vPosition.x = fPosX;
	m_vPosition.y = fPosY;
	m_vPosition.z = fPosZ;
	D3DXVec3Normalize(&m_vLook, &m_vLook);
	D3DXVec3Cross(&m_vUp, &m_vLook, &m_vRight);
	D3DXVec3Normalize(&m_vUp, &m_vUp);

	D3DXVec3Cross(&m_vRight, &m_vUp, &m_vLook);
	D3DXVec3Normalize(&m_vRight, &m_vRight);

	// Build the view matrix:
	float x = -D3DXVec3Dot(&m_vRight, &m_vPosition);
	float y = -D3DXVec3Dot(&m_vUp, &m_vPosition);
	float z = -D3DXVec3Dot(&m_vLook, &m_vPosition);

	m_mView(0,0) = m_vRight.x; m_mView(0, 1) = m_vUp.x; m_mView(0, 2) = m_vLook.x; m_mView(0, 3) = 0.0f;
	m_mView(1,0) = m_vRight.y; m_mView(1, 1) = m_vUp.y; m_mView(1, 2) = m_vLook.y; m_mView(1, 3) = 0.0f;
	m_mView(2,0) = m_vRight.z; m_mView(2, 1) = m_vUp.z; m_mView(2, 2) = m_vLook.z; m_mView(2, 3) = 0.0f;
	m_mView(3,0) = x;          m_mView(3, 1) = y;       m_mView(3, 2) = z;         m_mView(3, 3) = 1.0f;
	(*m_pDXVTDevice)->SetTransform(D3DTS_VIEW,&m_mView);
	m_fPitch = m_fYaw = 0.0f;
}

void DXVTCamera::Update()
{
D3DXVec3Normalize(&m_vLook, &m_vLook);

D3DXVec3Cross(&m_vUp, &m_vLook, &m_vRight);
D3DXVec3Normalize(&m_vUp, &m_vUp);

D3DXVec3Cross(&m_vRight, &m_vUp, &m_vLook);
D3DXVec3Normalize(&m_vRight, &m_vRight);

	// Build the view matrix:
float x = -D3DXVec3Dot(&m_vRight, &m_vPosition);
float y = -D3DXVec3Dot(&m_vUp, &m_vPosition);
float z = -D3DXVec3Dot(&m_vLook, &m_vPosition);

m_mView(0,0) = m_vRight.x; m_mView(0, 1) = m_vUp.x; m_mView(0, 2) = m_vLook.x; m_mView(0, 3) = 0.0f;
m_mView(1,0) = m_vRight.y; m_mView(1, 1) = m_vUp.y; m_mView(1, 2) = m_vLook.y; m_mView(1, 3) = 0.0f;
m_mView(2,0) = m_vRight.z; m_mView(2, 1) = m_vUp.z; m_mView(2, 2) = m_vLook.z; m_mView(2, 3) = 0.0f;
m_mView(3,0) = x;          m_mView(3, 1) = y;       m_mView(3, 2) = z;         m_mView(3, 3) = 1.0f;
(*m_pDXVTDevice)->SetTransform(D3DTS_VIEW,&m_mView);
}

void DXVTCamera::Walk(float fUnits)
{
m_vPosition += m_vLook * fUnits;
}

void DXVTCamera::Apart(float fUnits)
{
m_vPosition += m_vRight * fUnits;
}

float DXVTCamera::GetPitchAngle()
{
	return m_fPitch;
}

float DXVTCamera::GetYawAngle()
{
	return m_fYaw;
}

POINT DXVTCamera::GetCursorPos()
{
	::GetCursorPos(&m_CursorPos);
	ScreenToClient(*m_pDXVTDevice->GetDeviceWindow(),&m_CursorPos);
	return m_CursorPos;
}

D3DXMATRIX &DXVTCamera::GetViewMatrix()
{
	return m_mView;
}

void DXVTCamera::Build(VBaseWindow * pBaseWindow,float fTimeDelta,float fCameraSpeed,int vkMoveForward,int vkMoveBackward,int vkMoveRight,int vkMoveLeft,bool bShowCursor)
{
    //ShowCursor(bShowCursor);
	m_fCameraSpeed = fCameraSpeed;
	if(GetAsyncKeyState(vkMoveForward))
		Walk(fTimeDelta * m_fCameraSpeed);
	if(GetAsyncKeyState(vkMoveLeft))
		Apart(-fTimeDelta * m_fCameraSpeed);
	if(GetAsyncKeyState(vkMoveBackward))
		Walk(-fTimeDelta * m_fCameraSpeed);
	if(GetAsyncKeyState(vkMoveRight))
		Apart(fTimeDelta * m_fCameraSpeed);
    //if( GetAsyncKeyState('Q') )
			//m_pCamera->Roll(1.0f * fTimeDelta);
	//if( GetAsyncKeyState('E'))
		//	m_pCamera->Roll(-1.0f * fTimeDelta);
	::GetCursorPos(&m_CursorPos);
	ScreenToClient(*pBaseWindow,&m_CursorPos);
	Yaw((m_CursorPos.x - m_pDXVTDevice->GetResolutionX()/2)*fTimeDelta*0.5f);//Should be changed without release mode !!!!
	Pitch((m_CursorPos.y - m_pDXVTDevice->GetResolutionY()/2)*fTimeDelta*0.5f);
	m_CursorPos.x = m_pDXVTDevice->GetResolutionX()/2;
	m_CursorPos.y = m_pDXVTDevice->GetResolutionY()/2;
	ClientToScreen(*pBaseWindow,&m_CursorPos);
	SetCursorPos(m_CursorPos.x,m_CursorPos.y);
	Update();
}

DXVTCamera::PickRay::PickRay(DXVTDevice * pDXVTDevice)
{
m_pDXVTDevice = pDXVTDevice;
}

void DXVTCamera::PickRay::Calculate(int x, int y)
{
	float px = 0;
	float py = 0;
	D3DXMATRIX Proj;
	(*m_pDXVTDevice)->GetTransform(D3DTS_PROJECTION,&Proj);
	 px = ((( 2.0f*x) / m_pDXVTDevice->GetResolutionX())  - 1.0f) / Proj(0, 0);
     py = (((-2.0f*y) / m_pDXVTDevice->GetResolutionY()) + 1.0f) / Proj(1, 1);
	 Direction = D3DXVECTOR3(px,py,1.0f);
	 Origin = D3DXVECTOR3(0.0f,0.0f,0.0f);
}

void DXVTCamera::PickRay::Transform(D3DXMATRIX* T)
{
     D3DXVec3TransformCoord(&Origin,&Origin,T);
     D3DXVec3TransformNormal(&Direction,&Direction,T);
     D3DXVec3Normalize(&Direction, &Direction);
}
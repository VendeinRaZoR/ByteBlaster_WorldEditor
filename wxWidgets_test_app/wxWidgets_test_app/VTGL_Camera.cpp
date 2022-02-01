#include "VTGL_Camera.h"

VTGL_Camera::VTGL_Camera(VTGL_Device *pVTGLDevice)
{
	m_pVTGLDevice = pVTGLDevice;
	m_vPosition = VTVector3D(0.0f, 0.0f, 0.0f);
	m_vRight = VTVector3D(1.0f, 0.0f, 0.0f);
	m_vUp = VTVector3D(0.0f, 1.0f, 0.0f);
	m_vLook = VTVector3D(0.0f,0.0f,1.0f);
	m_fPitch = 0; m_fYaw = 0;
}

VTGL_Camera::~VTGL_Camera()
{

}


void VTGL_Camera::SetProjectionMatrix(float fFOV,float fDistance)
{
	m_pVTGLDevice->SetMatrixMode("Projection");
	VTGL_Perspective(&m_mProjection,fFOV,((float)m_pVTGLDevice->GetResolution().x / (float)m_pVTGLDevice->GetResolution().y),1.0f,fDistance);
    m_pVTGLDevice->SetTransform(&m_mProjection);
}

void VTGL_Camera::SetViewMatrix(float fPosX,float fPosY,float fPosZ)
{
	m_vPosition.x = fPosX;
	m_vPosition.y = fPosY;
	m_vPosition.z = fPosZ;
	m_vLook.Normalize();
	m_vUp.Cross(m_vLook, m_vRight);
	m_vUp.Normalize();
	m_vRight.Cross(m_vUp, m_vLook);
	m_vRight.Normalize();
	// Build the view matrix:
	 float x = -(m_vRight*m_vPosition);
	 float y = -(m_vUp*m_vPosition);
	 float z = -(m_vLook*m_vPosition);

    m_pVTGLDevice->SetMatrixMode("View");
	m_mView(0,0) = m_vRight.x; m_mView(0, 1) = m_vUp.x; m_mView(0, 2) = m_vLook.x; m_mView(0, 3) = 0.0f;
	m_mView(1,0) = m_vRight.y; m_mView(1, 1) = m_vUp.y; m_mView(1, 2) = m_vLook.y; m_mView(1, 3) = 0.0f;
	m_mView(2,0) = m_vRight.z; m_mView(2, 1) = m_vUp.z; m_mView(2, 2) = m_vLook.z; m_mView(2, 3) = 0.0f;
	m_mView(3,0) = x;          m_mView(3, 1) = y;       m_mView(3, 2) = z;         m_mView(3, 3) = 1.0f;
	m_pVTGLDevice->SetTransform(&m_mView);
}

void VTGL_Camera::Pitch(float fAngle)
{
	VTMatrix4 T;
	if(fAngle > 360)//Защита от неожиданно больших углов кручения 
	fAngle = 0;
	//if(fAngle < 360)
	//m_fPitch += fAngle;
	//printf("\n%f",m_fPitch);
	/*if(m_fPitch > 90)
	{
        m_fPitch = 90;
		fAngle = 0.0;
    }
	if(m_fPitch < -90)
	{
		m_fPitch = -90;
		fAngle = 0.0;
	}*/
	/*if(EqFloat(m_vLook*(VTVector3D(0,1,0)),1.0f,0.01f))
	{
    VTGL_RotationAxis(&T,&m_vRight,0.1);
	m_vUp = T*m_vUp;
	m_vLook = T*m_vLook;
	fAngle = 0;
	}
	if(EqFloat(m_vLook*(VTVector3D(0,1,0)),-1.0f,0.01f))
	{
    VTGL_RotationAxis(&T,&m_vRight,-0.1);
	m_vUp = T*m_vUp;
	m_vLook = T*m_vLook;
	fAngle = 0;
	}*/
	VTGL_RotationAxis(&T,&m_vRight,fAngle);
	m_vUp = T*m_vUp;
	m_vLook = T*m_vLook;

}

void VTGL_Camera::Yaw(float fAngle)
{
	VTMatrix4 T;
	m_fYaw += fAngle;
	if(fAngle > 360)//Защита от неожиданно больших углов кручения 
	fAngle = 0;
	//printf("\n%f",fAngle);
	/*if(m_fYaw > 2*D3DX_PI)
	{
		m_fYaw = 0.0f;
    }
		if(m_fYaw < -2*D3DX_PI)
	{
		m_fYaw = 0.0f;
	}*/
    VTGL_RotationY(&T,fAngle);
	m_vRight = T*m_vRight;
	m_vLook = T*m_vLook;
}

void VTGL_Camera::Roll(float fAngle)
{
    VTMatrix4 T;
	VTGL_RotationAxis(&T, &m_vLook,fAngle);
	m_vRight = T*m_vRight;
	m_vUp = T*m_vUp;
} 

void VTGL_Camera::Walk(float fUnits)
{
VTVector3D v = m_vLook * fUnits;
m_vPosition += v;
}

void VTGL_Camera::Apart(float fUnits)
{
VTVector3D v = m_vRight * fUnits;
m_vPosition += v;
}

void VTGL_Camera::Update()
{
	m_vLook.Normalize();
	m_vUp.Cross(m_vLook, m_vRight);
	m_vUp.Normalize();
	m_vRight.Cross(m_vUp, m_vLook);
	m_vRight.Normalize();
	// Build the view matrix:
	 float x = -(m_vRight*m_vPosition);
	 float y = -(m_vUp*m_vPosition);
	 float z = -(m_vLook*m_vPosition);

    m_pVTGLDevice->SetMatrixMode("View");
	m_mView(0,0) = m_vRight.x; m_mView(0, 1) = m_vUp.x; m_mView(0, 2) = m_vLook.x; m_mView(0, 3) = 0.0f;
	m_mView(1,0) = m_vRight.y; m_mView(1, 1) = m_vUp.y; m_mView(1, 2) = m_vLook.y; m_mView(1, 3) = 0.0f;
	m_mView(2,0) = m_vRight.z; m_mView(2, 1) = m_vUp.z; m_mView(2, 2) = m_vLook.z; m_mView(2, 3) = 0.0f;
	m_mView(3,0) = x;          m_mView(3, 1) = y;       m_mView(3, 2) = z;         m_mView(3, 3) = 1.0f;
	m_pVTGLDevice->SetTransform(&m_mView);
}

void VTGL_Camera::Build(wxWindow * pParentWindow,float fTimeDelta,float fCameraSpeed,int vkMoveForward,int vkMoveBackward,int vkMoveRight,int vkMoveLeft,bool bShowCursor)
{
	//printf("\n%.2f",fTimeDelta);
    //ShowCursor(bShowCursor);
	m_fCameraSpeed = fCameraSpeed;
	if(GetAsyncKeyState(vkMoveForward))
		Walk(fTimeDelta * fCameraSpeed);
	if(GetAsyncKeyState(vkMoveLeft))
		Apart(-fTimeDelta * fCameraSpeed);
	if(GetAsyncKeyState(vkMoveBackward))
		Walk(-fTimeDelta * fCameraSpeed);
	if(GetAsyncKeyState(vkMoveRight))
		Apart(fTimeDelta * fCameraSpeed);
    if( GetAsyncKeyState('Q') )
			Roll(1.0f * fTimeDelta*fCameraSpeed);
	if( GetAsyncKeyState('E'))
			Roll(-1.0f * fTimeDelta*fCameraSpeed);
	m_CursorPos = wxGetMousePosition();
	pParentWindow->ScreenToClient(&m_CursorPos.x,&m_CursorPos.y);
	//printf("\n%.2f",(m_CursorPos.y - (m_pVTGLDevice->GetResolution().y/2))*fTimeDelta*0.5);
	Yaw(-(m_CursorPos.x - (m_pVTGLDevice->GetResolution().x/2))*fTimeDelta*fCameraSpeed*4);//Улог в градусах !!!
	Pitch(-(m_CursorPos.y - (m_pVTGLDevice->GetResolution().y/2))*fTimeDelta*fCameraSpeed*4);//
	m_CursorPos.x = m_pVTGLDevice->GetResolution().x/2;
	m_CursorPos.y = m_pVTGLDevice->GetResolution().y/2;
	pParentWindow->WarpPointer(m_CursorPos.x,m_CursorPos.y); 
	pParentWindow->ClientToScreen(&m_CursorPos.x,&m_CursorPos.y);
	Update();
}
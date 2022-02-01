#ifndef _DXVT_CAMERA_
#define _DXVT_CAMERA_
#include "DXVT_Device.h"

class DXVTCamera
{
	VTVector3D m_vPosition;
	VTVector3D m_vRight;
	VTVector3D m_vUp;
	VTVector3D m_vLook;
	VTMatrix4 m_mView;
    VTMatrix4 m_mProjection;
	VTGL_Device *m_pVTGLDevice;
	float m_fPitch,m_fYaw;
	float m_fCameraSpeed;
	wxPoint m_CursorPos;
public:
	DXVTCamera(VTGL_Device *pVTGLDevice);
	~DXVTCamera();
	/*struct PickRay
	{
		PickRay(DXVTDevice *pDXVTDevice);
		D3DXVECTOR3 Origin;
		D3DXVECTOR3 Direction;
		DXVTDevice *m_pDXVTDevice;
		void Calculate(int x, int y);
		void Transform(D3DXMATRIX* T);
	};*/
    void SetProjectionMatrix(float fFOV,float fDistance);
	void SetViewMatrix(float fPosX = 0,float fPosY = 0,float fPosZ = 0);
	VTVector3D &GetViewMatrix();
	void Pitch(float fAngle);
	void Yaw(float fAngle);
	void Roll(float fAngle);
	void Walk(float fUnits);
	void Apart(float fUnits);
	void Update();
	float GetPitchAngle();
	float GetYawAngle();
    wxPoint GetCursorPos();
	///////////////////////////////////////////////
	////////////////////Метод для ленивых/////////
	//////////////////////////////////////////////
	//void Build(VBaseWindow * pBaseWindow,float fTimeDelta,float fCameraSpeed,int vkMoveForward = 'W',int vkMoveBackward = 'S',int vkMoveRight = 'D',int vkMoveLeft = 'A',bool bShowCursor = false);
};


#endif
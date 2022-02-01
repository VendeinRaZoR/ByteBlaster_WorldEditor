#ifndef _DXVT_CAMERA_
#define _DXVT_CAMERA_
#include "DXVT_Device.h"

class DXVTCamera
{
	D3DXVECTOR3 m_vPosition;
	D3DXVECTOR3 m_vRight;
	D3DXVECTOR3 m_vUp;
	D3DXVECTOR3 m_vLook;
	D3DXMATRIX m_mView;
    D3DXMATRIX m_mProjection;
	DXVTDevice *m_pDXVTDevice;
	float m_fPitch,m_fYaw;
	float m_fCameraSpeed;
	POINT m_CursorPos;
public:
	DXVTCamera(DXVTDevice *pDXVTDevice);
	~DXVTCamera();
	struct PickRay
	{
		PickRay(DXVTDevice *pDXVTDevice);
		D3DXVECTOR3 Origin;
		D3DXVECTOR3 Direction;
		DXVTDevice *m_pDXVTDevice;
		void Calculate(int x, int y);
		void Transform(D3DXMATRIX* T);

	};
    void SetProjectionMatrix(float fFOV,float fDistance);
	void SetViewMatrix(float fPosX = 0,float fPosY = 0,float fPosZ = 0);
	D3DXMATRIX &GetViewMatrix();
	void Pitch(float fAngle);
	void Yaw(float fAngle);
	void Roll(float fAngle);
	void Walk(float fUnits);
	void Apart(float fUnits);
	void Update();
	float GetPitchAngle();
	float GetYawAngle();
    POINT GetCursorPos();
	///////////////////////////////////////////////
	////////////////////Метод для ленивых/////////
	//////////////////////////////////////////////
	void Build(VBaseWindow * pBaseWindow,float fTimeDelta,float fCameraSpeed,int vkMoveForward = 'W',int vkMoveBackward = 'S',int vkMoveRight = 'D',int vkMoveLeft = 'A',bool bShowCursor = false);
};


#endif
#include "DXVT_Geometry.h"
#include "DXVT_Material.h"
#include "DXVT_Light.h"
#include "DXVT_Font.h"
#include "DXVT_Camera.h"

#define SCREEN_X 640
#define SCREEN_Y 480

class BBMain
{
protected:
DXVTDevice *m_pDXVTDevice;
DXVTFont * m_pDXVTFont;
DXVTCamera * m_pCamera;
public:
BBMain();
~BBMain();
void InitEngine();
virtual void Render(float fTimeDelta);
DXVTDevice * GetDevice();
DXVTFont * GetFont();
};
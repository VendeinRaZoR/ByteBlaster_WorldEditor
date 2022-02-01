#include "VApplication.h"
#include "VEventHandler.h"
#include <gdiplus.h>

using namespace Gdiplus;

class VGraphics
{
HDC m_hdc;
PAINTSTRUCT  ps;
VEvent m_Event;
VBaseWindow *m_pBaseWindow;
GdiplusStartupInput gdiplusStartupInput;
ULONG_PTR           gdiplusToken;
Image * m_pImage;//TODO : причесать
public:
	VGraphics(VBaseWindow * pBaseWindow = 0)
	{
		//m_Event = VEvent(WM_PAINT);
		m_pBaseWindow = pBaseWindow;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	}
	~VGraphics(){}
void DrawImage(int nPosX,int nPosY);
void OpenImage(VString vFileName)
{
	wchar_t *dest;
	mbstowcs(dest,vFileName,vFileName.length()+1);
	m_pImage = new Image(dest);
}
};

void VGraphics::DrawImage(int nPosX,int nPosY)
{
	if(m_Event.isActive())
	{
	m_hdc = BeginPaint(*m_pBaseWindow, &ps);
	Graphics graphics(m_hdc);
graphics.DrawImage(m_pImage, nPosX, nPosY);
EndPaint(*m_pBaseWindow,&ps);
	}
}
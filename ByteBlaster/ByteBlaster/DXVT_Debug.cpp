#include "DXVT_Debug.h"

int FPS;
float g_fTimeElapsed;
DXVTFont *g_pDXVTFont;
char * g_szFPS;


void Init(DXVTDevice * pDXVTDevice)
{
	g_szFPS = new char[256];
	g_pDXVTFont = new DXVTFont(pDXVTDevice,"Times New Roman",16);
	g_pDXVTFont->CreateText();
}
void CalcFPS(float fTimeDelta,DXVTFont *pDXVTFont)
{
     FPS++;
     g_fTimeElapsed += fTimeDelta;

     if(g_fTimeElapsed >= 1.0f)
     {
          FPS /= (int)g_fTimeElapsed;
		sprintf(g_szFPS,"%d",FPS);
		pDXVTFont->DrawText(20, 20, 0xff000000,"Hello World",0);
          g_fTimeElapsed = 0.0f;
          FPS = 0;
     }
}

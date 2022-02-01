#include "DXVT_Device.h"

#define MAX_NUM_VERTICES 50*6

#define D3DFONT_BOLD        0x0001
#define D3DFONT_ITALIC      0x0002
#define D3DFONT_ZENABLE     0x0004

#define D3DFONT_CENTERED    0x0001
#define D3DFONT_TWOSIDED    0x0002
#define D3DFONT_FILTERED    0x0004

#define D3DFVF_FONT2DVERTEX (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)

struct FONT2DVERTEX { D3DXVECTOR4 p;   DWORD color;     FLOAT tu, tv; };

class DXVTFont
{
	DXVTDevice* m_pDXVTDevice;
    TCHAR   m_strFontName[80];            // Font properties
    DWORD   m_dwFontHeight;
    DWORD   m_dwFontFlags;
    LPDIRECT3DTEXTURE9      m_pTexture;   // The d3d texture for this font
    LPDIRECT3DVERTEXBUFFER9 m_pVB;        // VertexBuffer for rendering text
    DWORD   m_dwTexWidth;                 // Texture dimensions
    DWORD   m_dwTexHeight;
    FLOAT   m_fTextScale;
    FLOAT   m_fTexCoords[128-32][4];
    LPDIRECT3DSTATEBLOCK9 m_pStateBlockSaved;
    LPDIRECT3DSTATEBLOCK9 m_pStateBlockDrawText;
public:
	DXVTFont(DXVTDevice *pDXVTDevice,char * szFontName,DWORD dwHeight);
	~DXVTFont();
	HRESULT CreateText();
	FONT2DVERTEX InitFont2DVertex( const D3DXVECTOR4& p, D3DCOLOR color, float tu, float tv );
	HRESULT LoadTextFromFile(char * szSrcText);
	void DrawText( FLOAT sx, FLOAT sy, DWORD dwColor,const char* strText, DWORD dwFlags); /// Text как в printf сделать !
};
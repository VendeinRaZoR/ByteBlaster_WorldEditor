#include <wx/wxprec.h>
  #ifndef WX_PRECOMP
    #include <wx/wx.h>
  #endif

class VTGL
{
public:
VTGL();
~VTGL();
void Init(D3DDEVTYPE D3D_DevType)=0;
};
#ifndef _VTGL_DEVICE_OGL_H_
#define _VTGL_DEVICE_OGL_H_
#include "VTGL_Device.h"
//#include <wglext.h>
//#include <glext.h>
//#include <glxext.h>
//#include <glcorearb.h>
#include "glew.h"
#include <wx/glcanvas.h>

#define OPENGL_GET_PROC(p,n) \
	n = (p)wglGetProcAddress(#n);

class VTGL_Device_OGL : public VTGL_BaseDevice
{
wxGLContext *m_pglContext;
wxGLCanvas * m_glCanvas;
wxPoint m_pRes;
VTMatrix4 m_mView;
public:
VTGL_Device_OGL(wxWindow * pParentWindow,bool bWindowed,int nResX,int nResY);
~VTGL_Device_OGL();
	virtual bool Init(wxWindow * pParentWindow,bool bWindowed,int nResX,int nResY);
	virtual void BeginRender();
	virtual void EndRender();
	virtual void Clear(DWORD dwFlags,wxColor &Color);
	virtual wxPoint GetResolution();
	virtual void Release();
	virtual void SetTransform(VTMatrix4*);
	virtual void SetMatrixMode(char* szType);
	virtual void SetRenderMode(int vtglRenderMode){}
public:
	virtual DWORD vtglCLEARCOLOR()const{return GL_COLOR_BUFFER_BIT;}
	virtual DWORD vtglCLEARDEPTH()const{return GL_DEPTH_BUFFER_BIT;}
	virtual DWORD vtglCLEARSTENCIL()const{return GL_STENCIL_BUFFER_BIT;}
};

// VAO extensions


#endif
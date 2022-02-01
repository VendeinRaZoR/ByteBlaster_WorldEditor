#include "VTGL_Device_OGL.h"
#include "VTGL_Math.h"
//#include "Shader.h"




/*bool LoadFile(const char *fileName, bool binary, unsigned char **buffer,unsigned int *size) // FOR SHADERS <---
{
	assert(fileName);
	assert(buffer);
	assert(size);

	FILE     *input;
	unsigned int fileSize, readed;

	const char mode[] = {'r', binary ? 'b' : 't', '\0'};

	if ((input = fopen(fileName, mode)) == NULL)
	{
		return false;
	}

	fseek(input, 0, SEEK_END);
	fileSize = (unsigned int)ftell(input);
	rewind(input);

	if (fileSize == 0)
	{
		fclose(input);
		return false;
	}

	*buffer = new unsigned char[fileSize];
	assert(*buffer);

	readed = fread(*buffer, 1, fileSize, input);

	fclose(input);

	if (readed != fileSize)
	{
		delete[] *buffer;
		return false;
	}

	*size = fileSize;

	return true;
}*/ 

VTGL_Device_OGL::VTGL_Device_OGL(wxWindow * pParentWindow,bool bWindowed,int nResX,int nResY):VTGL_BaseDevice(pParentWindow)
{
Init(pParentWindow,bWindowed,nResX,nResY);
printf("\nthis is OGL version");
}

VTGL_Device_OGL::~VTGL_Device_OGL()
{
delete m_glCanvas;
delete m_pglContext;
}

bool VTGL_Device_OGL::Init(wxWindow * pParentWindow,bool bWindowed,int nResX,int nResY)
{
   m_glCanvas = new wxGLCanvas(pParentWindow,wxID_ANY,wxDefaultPosition,wxSize(pParentWindow->GetSize().x,pParentWindow->GetSize().y));
   m_pglContext = new wxGLContext(m_glCanvas);
   m_pParentWindow = pParentWindow;
	if(m_glCanvas->GetContext())
	{
   	m_glCanvas->SetCurrent(*m_pglContext);
		glViewport(0, 0, (GLint)nResX, (GLint)nResY); 
		/*glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		VTMatrix4 *mProjection = VTGL_Perspective(VTGL_ToRadian(45.0), (float)nResX/(float)nResY,1, 100.0);
		SetTransform(mProjection);*/
		//glMatrixMode(GL_MODELVIEW);
		glewInit();

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);
/*glEnableClientState(GL_VERTEX_ARRAY);
glEnableClientState(GL_COLOR_ARRAY);
	 glGenBuffers( 1, &meshVBO );
  glBindBuffer(GL_ARRAY_BUFFER, meshVBO );
  glBufferData(GL_ARRAY_BUFFER, sizeof(float)*3*MESH_VERTEX_COUNT, NULL, GL_STATIC_DRAW);
meshVA = (GLfloat*)glMapBuffer(GL_ARRAY_BUFFER,GL_WRITE_ONLY);
for(int i = 0;i<3*MESH_VERTEX_COUNT;i++)
meshVA[i] = triangleMesh[i];
glUnmapBuffer(GL_ARRAY_BUFFER);*/


	// glGenBuffers( 1, &meshcolor );
//  glBindBuffer(GL_ARRAY_BUFFER, meshcolor );
 // glBufferData(GL_ARRAY_BUFFER, sizeof(float)*3*MESH_VERTEX_COUNT, &colorMesh[0], GL_STATIC_DRAW);
 // glBindBuffer(GL_ARRAY_BUFFER,0);

 
	}
	else
	{
		printf("Init Fail\n");
	}



   return true;//error logging !!!
}

wxPoint VTGL_Device_OGL::GetResolution()
{
	return m_pRes;
}
void VTGL_Device_OGL::BeginRender()
{
	glClearDepth(1.0f);	
}

void VTGL_Device_OGL::EndRender()
{
	glFlush();
	m_glCanvas->SwapBuffers();
}

void VTGL_Device_OGL::Clear(DWORD dwFlags,wxColor &Color)
{
		if(!m_glCanvas->GetContext())return;
	    glClearColor(Color.Red(), Color.Green(), Color.Blue(), Color.Alpha());
	    glClear(dwFlags);
	   // glLoadIdentity();
  /*glBindBuffer(GL_ARRAY_BUFFER, meshVBO );
  glVertexPointer( 3, GL_FLOAT, 0, NULL );
  glColorPointer( 3, GL_UNSIGNED_BYTE, 3, NULL );
  glDrawArrays(GL_TRIANGLES , 0, 3);*/

}

void VTGL_Device_OGL::Release()
{
delete m_glCanvas;
delete m_pglContext;
m_pglContext = NULL;
m_glCanvas = NULL;
}

void VTGL_Device_OGL::SetTransform(VTMatrix4 * vtMatrix)
{
	static float pmMatrix[16];
	if(!strcmp(m_szMatrixMode,"View"))//В OGL нет понятия "матрица вида" , так что проскакиваем самостоятельно этот участок конвейера (Мировое пространствво
	{                                 // + Пространство вида = Модель-видовое пространство) Вот так вот ...
		for(int i = 0;i<4;i++)
		{
		for(int j = 0;j<4;j++)
		{
			pmMatrix[4*i+j] = (*vtMatrix)(i,j);
		}
		}
    m_mView = VTMatrix4(pmMatrix);
	glLoadMatrixf(pmMatrix);
	}
	if(!strcmp(m_szMatrixMode,"World"))
	{
	(*vtMatrix) *= m_mView;
		for(int i = 0;i<4;i++)
		{
		for(int j = 0;j<4;j++)
		{
			pmMatrix[4*i+j] = (*vtMatrix)(i,j);
		}
		}
    glLoadMatrixf(pmMatrix);
	}
	if(!strcmp(m_szMatrixMode,"Projection"))
	{
		for(int i = 0;i<4;i++)
		{
		for(int j = 0;j<4;j++)
		{
			pmMatrix[4*i+j] = (*vtMatrix)(i,j);
		}
		}
    glLoadMatrixf(pmMatrix);
	}
}

void VTGL_Device_OGL::SetMatrixMode(char* szType)
{
	m_szMatrixMode = szType;
	if(!strcmp(m_szMatrixMode,"World"))
	glMatrixMode(GL_MODELVIEW);
	if(!strcmp(m_szMatrixMode,"View"))
	glMatrixMode(GL_MODELVIEW);
	if(!strcmp(m_szMatrixMode,"Projection"))
	glMatrixMode(GL_PROJECTION);
}


/*wxWindow * VTGL_Device_OGL::GetDeviceWindow()
{
return m_pParentWindow;
}*/


// VAO extensions

#include "VTGL_Geometry_OGL.h"

VTGL_BaseGeometry_OGL::VTGL_BaseGeometry_OGL(VTGL_Device_OGL *pVTGLDevice)
{
m_pVTGLDevice = pVTGLDevice;
m_unVBO = 0;
m_ppIndices = 0;
}

VTGL_BaseGeometry_OGL::~VTGL_BaseGeometry_OGL()
{

}

void VTGL_BaseGeometry_OGL::CreateVertexBuffer(size_t Size,int nNumVert,char * szVertexFormat)
{
	   	m_vertSize = Size;
		 m_nNumVert = nNumVert;
glGenBuffers( 1, &m_unVBO );
 glBindBuffer(GL_ARRAY_BUFFER, m_unVBO );
  glBufferData(GL_ARRAY_BUFFER,Size*nNumVert, NULL, GL_STATIC_DRAW);
    if(!strcmp(szVertexFormat,"Position"))
  {
	  glEnableClientState(GL_VERTEX_ARRAY);
	  glVertexPointer( 3, GL_FLOAT, m_vertSize, 0 );
	}
  if(!strcmp(szVertexFormat,"Position+Color"))
  {
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);
 glVertexPointer( 3, GL_FLOAT, m_vertSize,(const GLubyte *) 0 );//Должно быть видимо в рендере
 glColorPointer( 4, GL_UNSIGNED_BYTE, m_vertSize, (const GLubyte *)0 + sizeof(float)*3);
  }
 // glBindBuffer(GL_ARRAY_BUFFER,0);
  ///and other (tex1,tex2...)
}

void VTGL_BaseGeometry_OGL::CreateIndexBuffer32(size_t Size)
{
	///For 32 (int) indices
}

void VTGL_BaseGeometry_OGL::CreateIndexBuffer16(size_t Size)
{
 /*glGenBuffers(1, &m_unIBO);
 glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_unIBO);
 glBufferData(GL_ELEMENT_ARRAY_BUFFER, Size, NULL, GL_STATIC_DRAW);*/
	m_ppIndices = new unsigned short[Size];
}

void VTGL_BaseGeometry_OGL::UnMapIndex()
{
//glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);//Smth this ...
}

void VTGL_BaseGeometry_OGL::UnMapVertex()
{
glUnmapBuffer(GL_ARRAY_BUFFER);
}

void *VTGL_BaseGeometry_OGL::MapIndex()
{
//ppIndices = glMapBuffer(GL_ELEMENT_ARRAY_BUFFER,GL_WRITE_ONLY);
return m_ppIndices;
}

void * VTGL_BaseGeometry_OGL::MapVertex()
{
void* ppVertices = glMapBuffer(GL_ARRAY_BUFFER,GL_WRITE_ONLY); 
return ppVertices;
}

void VTGL_BaseGeometry_OGL::Draw(int nNumPrimitives,wxString vszPrimitiveType)
{
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	//glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	 glBindBuffer(GL_ARRAY_BUFFER, m_unVBO );
	if(!vszPrimitiveType.Cmp("Triangle") && !m_ppIndices)
	{ 
			  glDrawArrays(GL_TRIANGLES , 0, nNumPrimitives);
	}
if(!vszPrimitiveType.Cmp("Triangle") && m_ppIndices)
{
			  glDrawElements(GL_TRIANGLES,nNumPrimitives*3,GL_UNSIGNED_SHORT,&m_ppIndices[0]);// ... * 3 - for triangles 
	}
		  if(!vszPrimitiveType.Cmp("Line"))  glDrawArrays(GL_LINES , 0, nNumPrimitives*2);/// * 2 - for lines
		  if(!vszPrimitiveType.Cmp("Point"))  glDrawArrays(GL_POINTS , 0, nNumPrimitives);
		   //glBindBuffer(GL_ARRAY_BUFFER, 0 );
}
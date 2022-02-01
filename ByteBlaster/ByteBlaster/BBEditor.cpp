#include "BBEditor.h"
/*

BBEditor::BBEditor()
{

}

BBEditor::~BBEditor()
{

}

void BBEditor::Setup()
{
BasePrimitive = new DXVTBaseGeometry(m_pDXVTDevice);
RayLine = new DXVTBaseGeometry(m_pDXVTDevice);
m_pTerrainTexture = new DXVTTexture(m_pDXVTDevice);
BaseLight = new DXVTBaseLight(m_pDXVTDevice);
m_pPickRay = new DXVTCamera::PickRay(m_pDXVTDevice);
    Vertex* vertices = 0;
	BasePrimitive->CreateVertexBuffer(4*sizeof(Vertex),Vertex::FVF,4);
	BasePrimitive->GetVertex((void**)&vertices);
	///////////////////////////////////////////
	vertices[0] = Vertex(-1.0f, 0.0f, -1.0f,0xff00aa00);
	vertices[1] = Vertex(-1.0f,  0.0f, 1.0f,0xff00aa00);
	vertices[2] = Vertex( 1.0f,  0.0f, 1.0f,0xff00aa00);
	vertices[3] = Vertex( 1.0f, 0.0f, -1.0f,0xff00aa00);

	 BasePrimitive->SetVertex();

	 BasePrimitive->CreateIndexBuffer(6*sizeof(WORD));
     WORD * pIndices = 0;
 	 BasePrimitive->GetIndex((void**)&pIndices);
	 pIndices[0] = 0; pIndices[1] = 1; pIndices[2] = 2;
	 pIndices[3] = 0; pIndices[4] = 2; pIndices[5] = 3;
	 BasePrimitive->SetIndex();
	 m_pTerrainTexture->Load("desert.bmp");
}

void BBEditor::Render(float fTimeDelta)
{
		POINT p;
		GetCursorPos(&p);
		ScreenToClient(*this,&p);
		m_pPickRay->Calculate(p.x,p.y);
		D3DXMATRIX mInverse;
		D3DXMatrixInverse(&mInverse,0,&m_pCamera->GetViewMatrix());
		m_pPickRay->Transform(&mInverse);
	D3DXVECTOR3 RayTrace = *m_pTerrain->GetRayTrace(m_pPickRay,0);
	 if(GetAsyncKeyState(VK_RBUTTON))
	 {
	int *Index  = m_pTerrain->GetTraceRadius(&RayTrace,0,m_pTerrain->GetCellspacing()*2);
	for(int i=0;Index[i] != 0;i++)
	{
		m_pTerrain->SetHeightMapElement(Index[i],m_pTerrain->GetHeightMapElement(Index[i])+(float)(1/(i+5.0f)));
	}
	 }
	 	if(GetKeyState(VK_SPACE))
	    m_pCamera->Build(this,fTimeDelta);
		(*m_DXVTDevice)->SetRenderState(D3DRS_LIGHTING,false);
		m_pTerrainTexture->Set();
		m_pTerrain->Draw(m_pTerrain->GetNumTriangles(),"Triangle");
		(*m_DXVTDevice)->SetRenderState(D3DRS_FILLMODE,D3DFILL_WIREFRAME);
		if(g_bWireframe)
		{
		(*m_DXVTDevice)->SetTexture(0,0);
		m_pTerrain->Draw(m_pTerrain->GetNumTriangles(),"Triangle");
		}
		(*m_DXVTDevice)->SetRenderState(D3DRS_FILLMODE,D3DFILL_SOLID);
		(*m_DXVTDevice)->SetRenderState(D3DRS_LIGHTING,true);
}

void BBEditor::RenderAxis()
{
	 Vertex* vertices = 0; 
	 RayLine->CreateVertexBuffer(4*sizeof(Vertex),Vertex::FVF,4);
	 RayLine->GetVertex((void**)&vertices);
	 vertices[0] = Vertex(0.0f,0.0f,0.0f,0xff00aa00);
	 vertices[1] = Vertex(1.0f,0.0f,0.0f,0xff00aa00);
	 vertices[2] = Vertex(0.0f,0.0f,0.0f,0xffaaaa00);
	 vertices[3] = Vertex(0.0f,0.0f,1.0f,0xffaa0000);
     RayLine->SetVertex();
	 RayLine->Draw(2,"Line"); 
}*/
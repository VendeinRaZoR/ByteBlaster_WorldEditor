
template<class V_T>struct VQuadTree
{
	    static V_T *m_pStaticElement;
		VQuadTree * m_Node[4];
        V_T m_Element[4];
};

template<class V_T>V_T *VQuadTree<V_T>::m_pStaticElement = NULL;

template<class V_T> VQuadTree<V_T> * FirstNode(V_T *TreeElement)
{
VQuadTree<V_T>::m_pStaticElement = NULL;
VQuadTree<V_T> * pFirst = new VQuadTree<V_T>();
VQuadTree<V_T>::m_pStaticElement = TreeElement;

return pFirst;
}

template<class V_T> void PushTree(VQuadTree<V_T> * pQuadFirst,int nBaseIndex,int nNumNodesPerRow,int nNumElemPerRow)
{
pQuadFirst->m_Element[0] = VQuadTree<V_T>::m_pStaticElement[nBaseIndex]; 
pQuadFirst->m_Element[1] = VQuadTree<V_T>::m_pStaticElement[nBaseIndex + (nNumNodesPerRow)*(nNumElemPerRow)];
pQuadFirst->m_Element[2] = VQuadTree<V_T>::m_pStaticElement[nBaseIndex + nNumNodesPerRow];
pQuadFirst->m_Element[3] = VQuadTree<V_T>::m_pStaticElement[nBaseIndex + ((nNumNodesPerRow)*(nNumElemPerRow))+nNumNodesPerRow]; 
pQuadFirst->m_Node[0] = NULL;
pQuadFirst->m_Node[1] = NULL;
pQuadFirst->m_Node[2] = NULL;
pQuadFirst->m_Node[3] = NULL;
if(((nNumNodesPerRow)) >= 2)
{
pQuadFirst->m_Node[0] = new VQuadTree<V_T>();
pQuadFirst->m_Node[1] = new VQuadTree<V_T>();
pQuadFirst->m_Node[2] = new VQuadTree<V_T>();
pQuadFirst->m_Node[3] = new VQuadTree<V_T>();
PushTree(pQuadFirst->m_Node[0],nBaseIndex,(nNumNodesPerRow)/2,nNumElemPerRow);
PushTree(pQuadFirst->m_Node[1],nBaseIndex+(nNumNodesPerRow/2)*(nNumElemPerRow),(nNumNodesPerRow)/2,nNumElemPerRow);
PushTree(pQuadFirst->m_Node[2],nBaseIndex+nNumNodesPerRow/2,(nNumNodesPerRow)/2,nNumElemPerRow);
PushTree(pQuadFirst->m_Node[3],nBaseIndex+(nNumNodesPerRow/2)*(nNumElemPerRow)+nNumNodesPerRow/2,(nNumNodesPerRow)/2,nNumElemPerRow);
}
}

template<class V_T>VQuadTree<V_T> * FindNode(VQuadTree<V_T> * pQuadFirst,float fX,float fZ,int nLevel)//,int nQuadScale)
{
// Точка пересечения
	if(pQuadFirst->m_Node[0] != NULL || pQuadFirst->m_Node[1] != NULL || pQuadFirst->m_Node[2] != NULL || pQuadFirst->m_Node[3] != NULL)
	{
	if(fX < pQuadFirst->m_Node[0]->m_Element[2]._x && fZ > pQuadFirst->m_Node[0]->m_Element[1]._z && fX > pQuadFirst->m_Node[0]->m_Element[1]._x && fZ < pQuadFirst->m_Node[0]->m_Element[2]._z)
	{
		//printf("->First Quad\n");
		FindNode(pQuadFirst->m_Node[0],fX,fZ,nLevel);
	}
	if(fX < pQuadFirst->m_Node[1]->m_Element[2]._x && fZ < pQuadFirst->m_Node[1]->m_Element[2]._z && fX > pQuadFirst->m_Node[1]->m_Element[0]._x && fZ > pQuadFirst->m_Node[1]->m_Element[3]._z)
	{
		//printf("->Second Quad\n");
		FindNode(pQuadFirst->m_Node[1],fX,fZ,nLevel);
	}
	if(fX > pQuadFirst->m_Node[2]->m_Element[1]._x && fZ > pQuadFirst->m_Node[2]->m_Element[1]._z && fX < pQuadFirst->m_Node[2]->m_Element[3]._x && fZ < pQuadFirst->m_Node[2]->m_Element[0]._z)
	{
		//printf("->Third Quad\n");
		FindNode(pQuadFirst->m_Node[2],fX,fZ,nLevel);
	}
	if(fX > pQuadFirst->m_Node[3]->m_Element[0]._x && fZ < pQuadFirst->m_Node[3]->m_Element[0]._z && fX < pQuadFirst->m_Node[3]->m_Element[2]._x && fZ > pQuadFirst->m_Node[3]->m_Element[1]._z)
	{
		//printf("->Fourth Quad\n");
		FindNode(pQuadFirst->m_Node[3],fX,fZ,nLevel);
	}
}
else
{
	VQuadTree<V_T>::m_pStaticElement = pQuadFirst->m_Element;//"return" quad
	return 0;//pQuadFirst; 0 - for the present !
}
}

//Bin Tree
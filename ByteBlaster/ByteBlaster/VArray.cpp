#include "VArray.h"


template <class ArrType,class Alloc>VArray<ArrType,Alloc>::VArray()
	{
	m_nStackPos = 0;
	m_ArrSize = 0;
	m_pArr = (ArrType*)malloc(m_ArrSize);
	m_pArrBegin = m_pArr;
	m_pcArrBegin = m_pArr;
	m_pcArrEnd = m_pArr + m_ArrSize;
	}

template <class ArrType,class Alloc> void VArray<ArrType,Alloc>::sort()
{

}

template <class ArrType,class Alloc>VArray<ArrType,Alloc>::VArray(const size_t ArrSize,ArrType Value = ArrType())
	{
      m_ArrSize = ArrSize;
	  m_pArr = (ArrType*)malloc(m_ArrSize*sizeof(ArrType));
	  m_pArrBegin = (ArrType*)malloc(m_ArrSize*sizeof(ArrType));
	  int p = 0;
	  if(Value != 0)
	  {
	  for(int p = 0;p<m_ArrSize;p++)m_pArr[p] = Value;
	  for(int p = 0;p<m_ArrSize;p++)m_pArrBegin[p] = Value;
	  }
	  m_nStackPos = p;
	  m_pcArrBegin = m_pArr;
	  m_pcArrEnd = m_pArr + m_ArrSize;
	}

template <class ArrType,class Alloc>VArray<ArrType,Alloc>::VArray(iterator startIndex,iterator endIndex)
	{
m_ArrSize = endIndex - startIndex;
m_pArr = (ArrType*)malloc(m_ArrSize*sizeof(ArrType));
m_pArrBegin = (ArrType*)malloc(m_ArrSize*sizeof(ArrType));
for(int p = 0;p<m_ArrSize;p++)
m_pArr[p] = rand() % (*endIndex) + (*startIndex);
for(int p = 0;p<m_ArrSize;p++)
m_pArrBegin[p] = rand() % (*endIndex) + (*startIndex);
m_nStackPos = m_ArrSize;
	}

template <class ArrType,class Alloc>VArray<ArrType,Alloc>::VArray(const VArray& vArr)
{
		free(m_pArr);
		m_pArr = (ArrType*)malloc(vArr.size());
		m_pArr = vArr.m_pArr;
		m_pcArr = m_pArr;
}

template <class ArrType,class Alloc>VArray<ArrType,Alloc>::~VArray()
{
	if(m_pArr != 0)
	{
		free(m_pArr);
	}
}

VArray<class ArrType,class Alloc>::iterator VArray<class ArrType,class Alloc>::start()
{
	iterator i = m_pcArrBegin;
	i.size() = m_ArrSize;
	return i;
}

VArray<class ArrType,class Alloc>::iterator VArray<class ArrType,class Alloc>::end()
{
    iterator i = m_pcArrEnd;
	return i;
}

template <class ArrType,class Alloc> void VArray<ArrType,Alloc>::push(const ArrType &ArrVal)
{
	if(m_ArrSize > m_nStackPos)
{
 m_pArr[m_nStackPos] = ArrVal;
 m_pArrBegin[m_nStackPos] = ArrVal;
}
else
{
	delete m_pArr;
	m_ArrSize = m_nStackPos+1;
	m_pArr = new ArrType[m_ArrSize];
	m_pcArrBegin = m_pArr;
	m_pcArrEnd = m_pArr + m_ArrSize;
	for(int p=0;p<m_ArrSize-1;p++)
	m_pArr[p] = m_pArrBegin[p];
	m_pArr[m_ArrSize-1] = ArrVal;
	delete m_pArrBegin;
	m_pArrBegin = new ArrType[m_ArrSize];
	for(int p=0;p<m_ArrSize+1;p++)
	m_pArrBegin[p] = m_pArr[p];
}
	m_nStackPos++;
}

template <class ArrType,class Alloc> ArrType VArray<ArrType,Alloc>::pop()
{
	if(m_nStackPos != 0)
	{
	if(m_ArrSize < m_nStackPos)
{
	ArrType PopElem = m_pArr[--m_nStackPos];
	delete m_pArr;
	m_ArrSize = m_nStackPos;
	m_pArr = new ArrType[m_nStackPos];
	m_pcArrBegin = m_pArr;
	m_pcArrEnd = m_pArr + m_ArrSize;
	for(int p=0;p<m_ArrSize;p++)
	m_pArr[p] = m_pArrBegin[p];
	return PopElem;
	}
	else
	{
  ArrType PopElem = m_pArr[--m_nStackPos] = 0;
  m_ArrSize = m_nStackPos;
  return PopElem;
	}
	}
	else
	{
	return EMPTY; // Array Empty
	}
}

template <class ArrType,class Alloc> int &VArray<ArrType,Alloc>::size()
{
	return m_ArrSize;
}

template <class ArrType,class Alloc> bool VArray<ArrType,Alloc>::empty()const
{
	return (m_ArrSize == 0) ? 1 : 0;
}

template <class ArrType,class Alloc> void VArray<ArrType,Alloc>::fill(ArrType FillElem)
{
	for(int i = 0;i<m_ArrSize;i++)
	m_pArr[i] = FillElem;
}

template <class ArrType,class Alloc> void VArray<ArrType,Alloc>::clear()
{
	for(int i=0;i<m_ArrSize;i++)
	m_pArr[i] = 0;
}

///////////////////////////////////////////////
////////////////Operators//////////////////////
///////////////////////////////////////////////
template <class ArrType,class Alloc> ArrType VArray<ArrType,Alloc>::operator[](size_t index)
{
	if(index >= m_ArrSize)return 0;
	return m_pArr[index];
}
template <class ArrType,class Alloc> VArray<ArrType,Alloc>  &VArray<ArrType,Alloc>::operator=(const ArrType *ArrElem)
{
	m_pArr = (ArrType*)malloc(m_ArrSize);
	clear();
	for(int i=0;i<m_ArrSize;i++)
	m_pArr[i] = ArrElem[i];
	return *this;
}
template <class ArrType,class Alloc>  void* VArray<ArrType,Alloc>::operator new(size_t AllocSize)
{
	void *pAlloc;
	pAlloc = malloc(AllocSize);
	if(!pAlloc)
	{
		bad_alloc ba;
		throw ba;
	}
   return pAlloc;
}
template <class ArrType,class Alloc>  void VArray<ArrType,Alloc>::operator delete(void *pAlloc)
{
	free(pAlloc);
}
template <class ArrType,class Alloc>  void* VArray<ArrType,Alloc>::operator new[](size_t AllocSize)
{
	void *pAlloc;
	pAlloc = malloc(AllocSize);
	if(!pAlloc)
	{
		bad_alloc ba;
		throw ba;
	}
   return pAlloc;
}
template <class ArrType,class Alloc>  void VArray<ArrType,Alloc>::operator delete[](void *pAlloc)
{
	free(pAlloc);
}
template <class ArrType,class Alloc>  void VArray<ArrType,Alloc>::destroy()
{
	delete m_pArr;
}

template <class ArrType,class Alloc> ArrType * VArray<ArrType,Alloc>::data()
{
	return m_pArr;
}

template <class ArrType,class Alloc> ArrType VArray<ArrType,Alloc>::first()
{
   return *m_pcArrBegin;
}

template <class ArrType,class Alloc> ArrType VArray<ArrType,Alloc>::last()
{
   return *m_pcArrEnd;
}

template <class ArrType,class Alloc> ArrType VArray<ArrType,Alloc>::at(int nIndex)
{
	if(nIndex == m_ArrSize)return 0;
	return m_pArr[nIndex];
}
//////////////////////////////////////////////
////////////////Iterator//////////////////////
//////////////////////////////////////////////

template <class ArrType,class Alloc> VArray<ArrType,Alloc>::iterator::iterator(const ArrType *pArr = NULL)
{
	m_pArr = (ArrType*)pArr;
}

template <class ArrType,class Alloc> VArray<ArrType,Alloc>::iterator::iterator( iterator &i)
{
	m_pArr = i.m_pArr;
}

template <class ArrType,class Alloc> VArray<ArrType,Alloc>::iterator::~iterator()
{

}
/*
VArray<class ArrType,class Alloc>::iterator VArray<ArrType,Alloc>::iterator::operator[](size_t index)
{
	return (index < m_ArrSize) ? m_pArr[index] : printf("Out of Index");/*for further doing !!
}
template <class ArrType,class Alloc> VArray<class ArrType,class Alloc>::iterator VArray<ArrType,Alloc>::iterator::operator++()
{
   return ++m_pArr;
}
template <class ArrType,class Alloc> VArray<class ArrType,class Alloc>::iterator VArray<ArrType,Alloc>::iterator::operator++(int)
{
   return m_pArr++;
}
template <class ArrType,class Alloc> VArray<class ArrType,class Alloc>::iterator VArray<ArrType,Alloc>::iterator::operator--()
{
   return --m_pArr;
}
template <class ArrType,class Alloc> VArray<class ArrType,class Alloc>::iterator VArray<ArrType,Alloc>::iterator::operator--(int)
{
   return m_pArr--;
}
operator ArrType*()
{
	return m_pArr;
}
ArrType operator*() const
{
return *m_pArr;
}
bool operator!=(iterator i)
{
	return (m_pArr != i.m_pArr) ? 1 : 0;
}
int &size()
{
	return (int&)m_ArrSize;
}


*/
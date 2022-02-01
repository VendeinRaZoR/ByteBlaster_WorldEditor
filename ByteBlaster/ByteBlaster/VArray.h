#include <stdio.h>
#include <memory>
#include "VT.h"
////////VBaseVector/////////////
using namespace std;

#define EMPTY -1

template<class ArrType,class Alloc = allocator<ArrType>>class VArray
{
	 ArrType * m_pArr;
	 ArrType * m_pArrBegin;
	 const ArrType * m_pcArrBegin;
	 const ArrType * m_pcArrEnd;
	 size_t m_ArrSize;
	 size_t m_PrevSize;
	 //Alloc m_Allocator;
     int m_nStackPos;
public:
	 typedef struct iterator;
public:
	 VArray();
	 VArray(const size_t ArrSize,ArrType Value = ArrType());
	 VArray(iterator startIndex,iterator endIndex);
	 VArray(const VArray& vArr);
	 ~VArray();
 iterator start();
 iterator end();
 void sort();
 void push(const ArrType &ArrVal);
 ArrType pop();
 void swap();
 void assign();
 void emplace();
//void insert(){}
 int &size();
 bool empty()const;
 void fill(ArrType FillElem);
 void clear();
///////////////////////////////////////////////
////////////////Operators//////////////////////
///////////////////////////////////////////////
ArrType operator[](size_t index);
VArray &operator=(const ArrType *ArrElem);
void* operator new(size_t AllocSize);
void operator delete(void *pAlloc);
void* operator new[](size_t AllocSize);
void operator delete[](void *pAlloc);
void destroy();
ArrType * data();
ArrType first();
ArrType last();
ArrType at(int nIndex);
//////////////////////////////////////////////
////////////////Iterator//////////////////////
//////////////////////////////////////////////
typedef struct iterator
{
iterator(const ArrType *pArr = NULL);
iterator( iterator &i);
~iterator();
private:
	ArrType * m_pArr;
	size_t m_ArrSize;
public:
iterator operator[](size_t index)
{
	return (index < m_ArrSize) ? m_pArr[index] : printf("Out of Index");/*for further doing !!*/
}
iterator operator++()
{
   return ++m_pArr;
}
iterator operator++(int)
{
   return m_pArr++;
}
iterator operator--()
{
   return --m_pArr;
}
iterator operator--(int)
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
};
///////////////////////////////////////////////////
///////////////////////////////////////////////////
///////////////////////////////////////////////////
///////////////////////////////////////////////////
///////////////////////////////////////////////////
};

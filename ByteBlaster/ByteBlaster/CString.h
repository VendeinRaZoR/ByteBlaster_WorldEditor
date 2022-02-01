#ifndef 
#include <iostream>
#include <conio.h>
#include <new>

using namespace std;

#define MAX_NUMBER_LENGTH 500

namespace String
{

char * StrCat(char * dest,const char * source);
char * StrCpy(char * dest,const char * source);
char * StrNCpy(char *dest,const char * source,int num);
int StrLen(const char * source);
char * StrChr(char * source,char ch);
char * StrStr(char * Str1,char * Str2);
int StrCmp(char * Str1,char * Str2);

class CString
{
  char * m_szString;
  int m_nStrInputLen;
public:
	CString(char *szString = "\0")
	{
		m_nStrInputLen = StrLen(szString)+1;
		m_szString = new char[m_nStrInputLen];
		StrCpy(m_szString,szString);
	}
	~CString()
	{
			if(m_szString)
				delete[] m_szString;
	}
	CString(CString &Str)
	{	
         m_szString = new char[StrLen(Str.m_szString)+1];
		StrCpy(m_szString,Str.get());
	}
public:
	template<class T_String>CString operator+=(T_String Str);
public:
	CString operator+(CString Str);
	CString operator-(CString Str);
	CString operator-=(CString Str);
	CString operator-=(char * szStr);
	CString operator=(CString Str);
	CString operator+=(char * szStr);
	CString operator+=(CString Str);
	CString operator=(char * szStr);
public:
	char &operator[](int index);
	void * operator new(size_t size,const nothrow_t &n);
	void operator delete(void *pAlloc,const nothrow_t &n);
	void * operator new[](size_t size,const nothrow_t &n);
	void operator delete[](void *pAlloc,const nothrow_t &n);
	operator char*(){return m_szString;};
public:
	bool operator==(CString Str); 
	bool operator!=(CString Str); 
	bool operator<=(CString Str);
    bool operator>=(CString Str);
	bool operator<(CString Str);
	bool operator>(CString Str);
public:
	friend CString operator+(char *szStr1,CString Str2);
	friend CString operator-(char *szStr1,CString Str2);
	friend ostream &operator<<(ostream &stream,CString Str);
	friend istream &operator>>(istream &stream,CString &Str);
public:
	int length(){int i;for(i=0;m_szString[i];i++);return i;}
	bool empty(){if(length() == 0)  return true; else return false;}
	void clear(){for(int i=0;i<length()+1;i++)m_szString[i] ='\0';}
	char * get(){return m_szString;}
};

CString CString::operator+(CString Str)
{
	CString sztemp;
	if((StrLen(Str.m_szString)+StrLen(m_szString)) > m_nStrInputLen)
	{
	delete [] sztemp.m_szString;
	sztemp.m_szString = new char[StrLen(Str.m_szString)+StrLen(sztemp.m_szString)+1];
	}
	StrCpy(sztemp.m_szString,m_szString);
	StrCat(sztemp.m_szString,Str.m_szString);
	return sztemp;
}

CString CString::operator+=(char *szStr)
{
    char * sztemp = new char[StrLen(m_szString)+1];
	StrCpy(sztemp,m_szString);
	if((StrLen(szStr)+StrLen(m_szString)) > m_nStrInputLen)
	{
	delete [] m_szString;
	m_szString = new char[StrLen(szStr)+StrLen(sztemp)+1];
	}
	StrCpy(m_szString,sztemp);
	StrCat(m_szString,szStr);
	return *this;
}


CString operator+(char * szStr1,CString Str2)
{
   char * sztemp = new char[StrLen(Str2.m_szString)+1];
	StrCpy(sztemp,Str2.m_szString);
	if((StrLen(szStr1)+StrLen(Str2.m_szString)) > StrLen(Str2.m_szString))
	{
	delete [] Str2.m_szString;
	Str2.m_szString = new char[StrLen(szStr1)+StrLen(sztemp)+1];
	}
	StrCpy(Str2.m_szString,sztemp);
	StrCat(Str2.m_szString,szStr1);
	return Str2;
}

template<class T_String>CString CString::operator+=(T_String Str)
	{
	char * sztemp = new char[StrLen(m_szString)+1];
	char * szTypeString = new char[MAX_NUMBER_LENGTH];
	if(typeid(Str) == typeid(int))
	sprintf(szTypeString,"%.d",Str);
	else if(typeid(Str) == typeid(double))
	sprintf(szTypeString,"%.2f",Str);
	else if(typeid(Str) == typeid(float))
	sprintf(szTypeString,"%.2f",Str);
	else if(typeid(Str) == typeid(char))
	sprintf(szTypeString,"%.c",Str);
	else sprintf(szTypeString,"%.c",Str);
	StrCpy(sztemp,m_szString);
	if((StrLen(szTypeString)+StrLen(m_szString)) >= m_nStrInputLen)
	{
	delete [] m_szString;
	m_szString = new char[StrLen(szTypeString)+StrLen(sztemp)+1];
	}
	StrCpy(m_szString,sztemp);
	StrCat(m_szString,szTypeString);
	return *this;
	}

CString CString::operator+=(CString Str)
{
	char * sztemp = new char[StrLen(m_szString)+1];
	StrCpy(sztemp,m_szString);
	if((StrLen(Str.m_szString)+StrLen(m_szString)) >= m_nStrInputLen)
	{
	delete [] m_szString;
	m_szString = new char[StrLen(Str.m_szString)+StrLen(sztemp)+1];
	}
	StrCpy(m_szString,sztemp);
	StrCat(m_szString,Str.m_szString);
	return *this;
}

CString CString::operator-=(CString Str)
{
	char *szResStr = new char[StrLen(m_szString)+1];
	char *sztemp = new char[StrLen(m_szString)+1];
	char *szStrCopy = new char[StrLen(m_szString)+1];
	StrCpy(sztemp,m_szString);
	StrCpy(szStrCopy,m_szString);
	StrCpy(szStrCopy,StrStr(sztemp,Str.m_szString));
	if(StrCmp(szStrCopy,"\0")){
	for(int i=0;i<StrLen(Str.m_szString);i++)szStrCopy[i] = ' '; 
	szStrCopy += StrLen(Str.m_szString);
	StrNCpy(szResStr,sztemp,(StrLen(sztemp)-(StrLen(szStrCopy)+StrLen(Str.m_szString))));
	StrCat(szResStr,szStrCopy);
	delete [] m_szString;
	m_szString = new char[(StrLen(sztemp)-StrLen(Str.m_szString))+1];
	StrCpy(m_szString,szResStr);}
	return *this;
}

CString CString::operator-=(char * szStr)
{
	char *szResStr = new char[StrLen(m_szString)+1];
	char *sztemp = new char[StrLen(m_szString)+1];
	char *szStrCopy = new char[StrLen(m_szString)+1];
	StrCpy(sztemp,m_szString);
	StrCpy(szStrCopy,m_szString);
	StrCpy(szStrCopy,StrStr(sztemp,szStr));
	if(StrCmp(szStrCopy,"\0")){
	for(int i=0;i<StrLen(szStr);i++)szStrCopy[i] = ' '; 
	szStrCopy += StrLen(szStr);
	StrNCpy(szResStr,sztemp,(StrLen(sztemp)-(StrLen(szStrCopy)+StrLen(szStr))));
	StrCat(szResStr,szStrCopy);
	delete [] m_szString;
	m_szString = new char[(StrLen(sztemp)-StrLen(szStr))+1];
	StrCpy(m_szString,szResStr);}
	return *this;
}

CString operator-(char * Str1,CString Str2)
{
	char * szResStr = new char[StrLen(Str1)+1];
	char *sztemp = new char[StrLen(Str1)+1];
	StrCpy(szResStr,StrStr(Str1,Str2.m_szString));
	if(StrCmp(Str1,"\0")){
		for(int i=0;i<StrLen(Str2.m_szString);i++)szResStr[i] = ' '; 
		szResStr += StrLen(Str2.m_szString);
		StrNCpy(sztemp,Str1,(StrLen(Str1)-(StrLen(Str2.m_szString)+StrLen(szResStr))));
	StrCat(sztemp,szResStr);
	delete [] Str2.m_szString;
	Str2.m_szString = new char[StrLen(sztemp)+1];
	StrCpy(Str2.m_szString,sztemp);}
	return Str2;
}

CString CString::operator=(CString Str)
{
	if(StrLen(Str.m_szString) > m_nStrInputLen)
	{
	delete [] m_szString;
	m_szString = new char[StrLen(Str.m_szString)+1];
	}
	StrCpy(m_szString,Str.m_szString);
    return *this;
}

CString CString::operator=(char * Str)
{
	if(StrLen(Str) > m_nStrInputLen)
	{
	delete [] m_szString;
	m_szString = new char[StrLen(Str)+1];
	}
	StrCpy(m_szString,Str);
    return *this;
}

char &CString::operator [](int index)
{
	if(index < 0 || index > sizeof(m_szString)) exit(0);
	return m_szString[index];
}

void * CString::operator new(size_t size,const nothrow_t &n)
{
	void *pAlloc;
	pAlloc = malloc(size);
	if(!pAlloc)
	{
		bad_alloc ba;
		throw ba;
	}
   return pAlloc;
}

void CString::operator delete(void *pAlloc,const nothrow_t &n)
{
	free(pAlloc);
}

void * CString::operator new[](size_t size,const nothrow_t &n)
{
	void *pAlloc;
	pAlloc = malloc(size);
	if(!pAlloc)
	{
		bad_alloc ba;
		throw ba;
	}
   return pAlloc;
}

void CString::operator delete[](void *pAlloc,const nothrow_t &n)
{
	free(pAlloc);
}


bool CString::operator==(CString Str)
{
	if(!StrCmp(m_szString,Str.m_szString))
	return true;
	else return false;
}

bool CString::operator>=(CString Str)
{
	if(StrCmp(m_szString,Str.m_szString) == 2)
	return true;
	else return false;
}

bool CString::operator<=(CString Str)
{
	if(StrCmp(m_szString,Str.m_szString) == -2)
	return true;
	else return false;
}

bool CString::operator<(CString Str)
{
	if(StrCmp(m_szString,Str.m_szString) == -1)
	return true;
	else return false;
}

bool CString::operator>(CString Str)
{
	if(StrCmp(m_szString,Str.m_szString))
	return true;
	else return false;
}

bool CString::operator!=(CString Str)
{
	if(StrCmp(m_szString,Str.m_szString))
	return true;
	else return false;
}

ostream &operator<<(ostream &stream,CString Str)
{ 
	stream << Str.m_szString;
	return stream;
}

istream &operator>>(istream &stream,CString &Str)
{ 
	stream >> Str.m_szString;
	return stream;
}

int StrCmp(char *Str1, char *Str2)
{
	int count = 0;
	int Strslen = StrLen(Str1);
	int Strslen2 = StrLen(Str2);
	while(*Str1)
	{
		if(*Str1 == *Str2)
			count++;
		Str1++;Str2++;
	}
	if(count == Strslen && count == Strslen2)
      return 0;
	else if(Strslen > Strslen2)
	  return 1;
	else if(Strslen < Strslen2)
      return -1;
		else if(Strslen >= Strslen2)
	  return 2;
	else if(Strslen <= Strslen2)
      return -2;
}

char * StrStr(char * Str1,char * Str2)
{
	int count=0;
	int Str2len = StrLen(Str2);
	while(*Str1)
	{
		if(*Str1 == *Str2)
		{
		while(*Str2)
		{
			if(*Str2 == *Str1)
			{
				count++;
			}
			Str2++;Str1++;
		}
		if(count == Str2len)
			break;
		else count = 0;
		Str2 -= Str2len;
		Str1 -= Str2len-1;
		}
		Str1++;
	}
	Str1 -= count;
	return Str1;
}

char * StrCat(char * dest,const char * source)
{
int Strcatlen = StrLen(dest) + StrLen(source);
while(*dest++);dest--;
while(*source)
{
*dest++ = *source++;
}
*dest = '\0';
dest -= Strcatlen;
return dest;
}

char * StrCpy(char * dest,const char * source)
{
	int i;
	for(i=0;i<StrLen(source)+1;i++)dest[i] ='\0';
	while(*source)
	{
		*dest++ = *source++;
	}
	dest -= i-1; 
	return dest; 
}

char * StrNCpy(char * dest,const char * source,int num)
{
	int i;
	int _num=0;
	for(i=0;i<StrLen(source)+1;i++)dest[i] ='\0';
	while(*source && _num < num)
	{
		*dest++ = *source++;
		_num++;
	}
	dest -= num-1; 
	return dest; 
}

int StrLen(const char * source)
{
  int i=0;
 while(*source++)i++;
	return i;
}

char * StrChr(char * source,char ch)
{
	while(*source++ && *source++ != ch);source--;
 return source;
}

typedef CString NSTR;

};
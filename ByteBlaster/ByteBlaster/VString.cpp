#include "VString.h"

namespace String
{

VString::VString(char *szString)
{
		m_nStrInputLen = StrLen(szString)+1;
		m_szString = new char[m_nStrInputLen];
		StrCpy(m_szString,szString);
}

VString::VString(VString &Str)
{	
         m_szString = new char[StrLen(Str.m_szString)+1];
		StrCpy(m_szString,Str.get());
}

VString::~VString()
{
			if(m_szString)
			delete[] m_szString;
}

VString VString::operator+(VString Str)
{
	VString sztemp;
	if((StrLen(Str.m_szString)+StrLen(m_szString)) > m_nStrInputLen)
	{
	delete [] sztemp.m_szString;
	sztemp.m_szString = new char[StrLen(Str.m_szString)+StrLen(sztemp.m_szString)+1];
	}
	StrCpy(sztemp.m_szString,m_szString);
	StrCat(sztemp.m_szString,Str.m_szString);
	return sztemp;
}

VString VString::operator+=(char *szStr)
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


VString operator+(char * szStr1,VString Str2)
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

template<class T_String>VString VString::operator+=(T_String Str)
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
	sprintf(szTypeString,"%.d",Str);
	else sprintf(szTypeString,"%.d",Str);
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

VString VString::operator+=(VString Str)
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

VString VString::operator-=(VString Str)
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

VString VString::operator-=(char * szStr)
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

VString operator-(char * Str1,VString Str2)
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

VString &VString::operator=(const VString Str)
{
	if(StrLen(Str.m_szString) > m_nStrInputLen)
	{
	delete [] m_szString;
	m_szString = new char[StrLen(Str.m_szString)+1];
	}
	StrCpy(m_szString,Str.m_szString);
    return *this;
}

VString &VString::operator=(const char * Str)
{
	if(StrLen(Str) > m_nStrInputLen)
	{
	delete [] m_szString;
	m_szString = new char[StrLen(Str)+1];
	}
	StrCpy(m_szString,Str);
    return *this;
}

char &VString::operator [](int index)
{
	if(index < 0 || index > sizeof(m_szString)) exit(0);
	return m_szString[index];
}

void * VString::operator new(size_t size,const nothrow_t &n)
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

void VString::operator delete(void *pAlloc,const nothrow_t &n)
{
	free(pAlloc);
}

void * VString::operator new[](size_t size,const nothrow_t &n)
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

void VString::operator delete[](void *pAlloc,const nothrow_t &n)
{
	free(pAlloc);
}


bool VString::operator==(VString Str)
{
	if(!StrCmp(m_szString,Str.m_szString))
	return true;
	else return false;
}

bool VString::operator==(char * szStr)
{
	if(!StrCmp(m_szString,szStr))
	return true;
	else return false;
}

bool VString::operator>=(VString Str)
{
	if(StrCmp(m_szString,Str.m_szString) == 2)
	return true;
	else return false;
}

bool VString::operator<=(VString Str)
{
	if(StrCmp(m_szString,Str.m_szString) == -2)
	return true;
	else return false;
}

bool VString::operator<(VString Str)
{
	if(StrCmp(m_szString,Str.m_szString) == -1)
	return true;
	else return false;
}

bool VString::operator>(VString Str)
{
	if(StrCmp(m_szString,Str.m_szString))
	return true;
	else return false;
}

bool VString::operator!=(VString Str)
{
	if(StrCmp(m_szString,Str.m_szString))
	return true;
	else return false;
}

bool VString::operator!=(char * szStr)
{
	if(StrCmp(m_szString,szStr))
	return true;
	else return false;
}
VString::operator char*()
{
	return m_szString;
}

VString::operator wchar_t*()
{
	return (wchar_t*)m_szString;
}

int VString::length(){int i;for(i=0;m_szString[i];i++);return i;}
bool VString::empty(){if(length() == 0)  return true; else return false;}
void VString::clear(){for(int i=0;i<length()+1;i++)m_szString[i] ='\0';}
char * VString::get(){return m_szString;}

ostream &operator<<(ostream &stream,VString Str)
{ 
	stream << Str.m_szString;
	return stream;
}

istream &operator>>(istream &stream,VString &Str)
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
	return count ? Str1 : NULL;
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



};
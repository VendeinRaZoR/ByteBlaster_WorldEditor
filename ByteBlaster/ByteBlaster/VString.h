#ifndef VSTRING_H
#define VSTRING_H

#include "VT.h"

#include <iostream>
#include <conio.h>
#include <new>

using namespace std;

#define MAX_NUMBER_LENGTH 500

namespace String
{

VTAPI char * StrCat(char * dest,const char * source);
VTAPI char *  StrCpy(char * dest,const char * source);
VTAPI char *  StrNCpy(char *dest,const char * source,int num);
VTAPI int  StrLen(const char * source);
VTAPI char *  StrChr(char * source,char ch);
VTAPI char *  StrStr(char * Str1,char * Str2);
VTAPI int  StrCmp(char * Str1,char * Str2);

class VString
{
  char * m_szString;
  int m_nStrInputLen;
public:
	VTAPI VString(char *szString = "\0");
	VTAPI VString(VString &Str);
	VTAPI ~VString();
public:
	template<class T_String>VString operator+=(T_String Str);
public:
	VTAPI VString operator+(VString Str);
	VTAPI VString operator-(VString Str);
	VTAPI VString operator-=(VString Str);
	VTAPI VString operator-=(char * szStr);
	VTAPI VString &operator=(const VString Str);
	VTAPI VString operator+=(char * szStr);
	VTAPI VString operator+=(VString Str);
	VTAPI VString &operator=(const char * szStr);
public:
	VTAPI char &operator[](int index);
	VTAPI void * operator new(size_t size,const nothrow_t &n);
	VTAPI void operator delete(void *pAlloc,const nothrow_t &n);
	VTAPI void * operator new[](size_t size,const nothrow_t &n);
	VTAPI void operator delete[](void *pAlloc,const nothrow_t &n);
	VTAPI operator char*();
	VTAPI operator wchar_t*();
public:
	VTAPI bool operator==(VString Str); 
	VTAPI bool operator==(char * szStr); 
	VTAPI bool operator!=(VString Str); 
	VTAPI bool operator!=(char * szStr); 
	VTAPI bool operator<=(VString Str);
    VTAPI bool operator>=(VString Str);
	VTAPI bool operator<(VString Str);
	VTAPI bool operator>(VString Str);
public:
	VTAPI friend VString operator+(char *szStr1,VString Str2);
	VTAPI friend VString operator-(char *szStr1,VString Str2);
	VTAPI friend ostream &operator<<(ostream &stream,VString Str);
	VTAPI friend istream &operator>>(istream &stream,VString &Str);
public:
	VTAPI int length();
	VTAPI bool empty();
	VTAPI void clear();
	VTAPI char * get();
};

};

#endif
#ifndef VOBJECT_H
#define VOBJECT_H

#include "VApplication.h"

DECLARE_HANDLE(VUSERHANDLE);

class VObject
{
	HINSTANCE m_hInstance;
protected:
	HANDLE m_hHandle;
	VUSERHANDLE m_hUserHandle;//User Object
	VString m_vObjectType;
	SECURITY_ATTRIBUTES m_SecurityAttributes;
public:
	VObject(VString vObjectType = "Unknown",bool bInherit = false,HINSTANCE hInstance = (HINSTANCE)0x00040000)
	{
	  m_hInstance = hInstance;
	  m_vObjectType = vObjectType;
	  m_SecurityAttributes.nLength = sizeof(m_SecurityAttributes);
	  m_SecurityAttributes.lpSecurityDescriptor = &m_SecurityAttributes;
	  m_SecurityAttributes.bInheritHandle = bInherit;
	}
	operator HANDLE(){return m_hHandle;}
	VObject &operator=(VString vObjectType){m_vObjectType = vObjectType; return *this;}
    VString GetName(){return m_vObjectType;}
    //void SetSecurityDescriptor(){};
	virtual ~VObject(){CloseHandle(m_hHandle);}
};

#endif
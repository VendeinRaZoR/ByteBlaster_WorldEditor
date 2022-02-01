#ifndef _VTHREAD_
#define _VTHREAD_

class VThread  : protected VObject
{
	void * m_pParam;
	int m_nMaxSupendCount;
	LPTHREAD_START_ROUTINE m_ThreadStartFunc;
	CONTEXT m_ThreadContext;
public:
	VThread()
	{
		m_nMaxSupendCount = 0;
		m_vObjectType = "Kernel";
	}
	~VThread(){}
	bool Open(DWORD dwThreadID,bool bInherit = false)
	{
		return (m_hHandle = OpenThread(THREAD_ALL_ACCESS,bInherit,dwThreadID));
	}
	bool Create(void * pParam)
	{
		m_pParam = pParam;
		return (m_hHandle = CreateThread(&m_SecurityAttributes,32,m_ThreadStartFunc,pParam,0,NULL));
	}
	void SetStartFunc(LPTHREAD_START_ROUTINE ThreadStartFunc)
	{
       m_ThreadStartFunc = ThreadStartFunc;
	}
	bool GetContext()
	{
		return GetThreadContext(m_hHandle,&m_ThreadContext);
	}
	bool SetContext()
	{

	}
	DWORD GetRegisterValue(VString vRegisterName)
	{
      
	}
	template<class ValType>DWORD SetRegisterValue(VString vRegisterName,ValType Value)
	{

	}
	void Suspend()
	{
		if(m_nMaxSupendCount < 127)
		SuspendThread(m_hHandle);
		m_nMaxSupendCount++;
	}
	bool Resume()
	{
		return (ResumeThread(m_hHandle) != 0xFFFFFFFF) ? 1 : 0;
	}
	VThread &operator=(LPTHREAD_START_ROUTINE ThreadStartFunc){ m_ThreadStartFunc = ThreadStartFunc;return *this;}
};



#endif
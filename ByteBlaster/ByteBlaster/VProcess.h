
class VProcess : public VObject
{
private:
VString m_vProcessName;
VString m_vszCommandLine;// Переделать
VString m_vszEnvVar;// Переделать
DWORD m_dwReaded; 
UINT m_nProcessVersion;
PROCESSENTRY32 m_ProcessEntry32;
HANDLE m_hSnapshot;
DWORD m_dwPID;
public:
VProcess(VString vProcessName = "")
{
	m_vProcessName = vProcessName;
}
bool Create()
{
	//CreateProcess(...);
	return 0;
}
bool Open(bool bInheritObject = false)
{
if(m_vProcessName != "")
return (m_hHandle = OpenProcess(PROCESS_ALL_ACCESS,bInheritObject,GetID())) ? 1 : 0;
else
return (m_hHandle = OpenProcess(PROCESS_ALL_ACCESS,bInheritObject,m_dwPID)) ? 1 : 0;
}
template<class MemVar>bool WriteMemory(void * pAddress,MemVar pBuffer)
{
return WriteProcessMemory(m_hHandle,pAddress,(void*)&pBuffer,sizeof(MemVar),&m_dwReaded);
}
template<class MemVar>bool ReadMemory(void * pAddress,MemVar pBuffer)
{
return ReadProcessMemory(m_hHandle,pAddress,(void*)&pBuffer,sizeof(MemVar),&m_dwReaded);
}
DWORD GetID()
{
	if(m_vProcessName != "")
	{
    PROCESSENTRY32 m_ProcessEntry32 = {sizeof(m_ProcessEntry32)};  
    m_hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);   
    if (m_hSnapshot == INVALID_HANDLE_VALUE) 
        return 0;                          
    if (!Process32First(m_hSnapshot, &m_ProcessEntry32))   
        return 0;                          
    do {
        if (!StrCmp(m_ProcessEntry32.szExeFile, m_vProcessName)) 
            return (m_dwPID = m_ProcessEntry32.th32ProcessID);                 
	}while (Process32Next(m_hSnapshot, &m_ProcessEntry32));  
    return 0;    
	}
	else
	{
		return GetCurrentProcessId();
	}
}
void Exit()
{
	//???//ExitProcess(0);
}
VString GetCmdLine()
{
	m_vszCommandLine = (char*)GetCommandLine();
	return m_vszCommandLine;
}
VString GetEnvVar()
{
	///GetEnviromentVariable(...)
return m_vszEnvVar;
}
int GetVersion()
{
	m_nProcessVersion = 0;
	//GetProcessVersion(..)
	return m_nProcessVersion;
}
bool isRun()
{
	return m_hHandle ? 1 : 0;
}
void Suspend()
{
	//Suspend Process by the Toolhelp32 Threads
}
void Resume()
{
	//Resume Process by the Toolhelp32 Threads
}
public:
	VProcess &operator=(VString vProcessName)
	{
		m_vProcessName = vProcessName;
      return *this;
	}
	VProcess &operator=(char * vProcessName)
	{
		m_vProcessName = vProcessName;
      return *this;
	}
	VProcess &operator=(DWORD dwPID)
	{
		m_dwPID = dwPID;
		return *this;
	}
   
};
#include "VEventHandler.h"

VEvent::VEvent(VBaseWindow * pBaseWindow,DWORD dwEvent)
	{
          m_dwEvent = dwEvent;
		  m_pBaseWindow = pBaseWindow;
	}
	VEvent::~VEvent()
	{

	}
	void VEvent::Set(DWORD dwEvent)
	{
        m_dwEvent = dwEvent;
	}
	bool VEvent::isActive()
	{
		if(m_pBaseWindow->GetWindowMessage() != m_dwEvent)
		return false;
		else if(m_pBaseWindow->GetWindowMessage() == m_dwEvent)
		return true;
	}
	void VEvent::SetEventParam(void * pParam1,void * pParam2)
	{
		SendMessage(*m_pBaseWindow,m_dwEvent,(WPARAM)pParam1,(LPARAM)pParam2);
	}
	LONG_PTR VEvent::GetEventParam(VString ParamType)
	{
		if(ParamType == "Param1")
			return m_pBaseWindow->GetwParam();
		else if(ParamType == "Param2")
		    return m_pBaseWindow->GetLParam();
		else
		return 0;
	}

	DWORD VEvent::GetEvent()
	{
		return m_dwEvent;
	}

	VEventHandler::VEventHandler(VBaseWindow * pBaseWindow)
	{
       m_pBaseWindow = pBaseWindow;
	}

	VEventHandler::~VEventHandler()
	{

	}
	void VEventHandler::CallStatic()
	{
		SendMessage(*m_pBaseWindow,WM_CREATE,0,0);
	}
	void VEventHandler::StartEvents()
	{
		m_pBaseWindow->StartEvents();
	}
void VEventHandler::AddEvent(DWORD dwEvent)
{
	//ѕроверка на схожесть !!!
VEvent * pEvent = new VEvent(m_pBaseWindow,dwEvent);// потер€ производительности (???)
m_lEvent.push_back(pEvent);
}

void VEventHandler::DeleteEvent()
{

}

VEvent * VEventHandler::GetEventByType(DWORD dwEvent)
{
	for(list<VEvent*>::iterator i = m_lEvent.begin();i != m_lEvent.end();i++)
	{
		if(dwEvent == (*i)->GetEvent())
		{
           return (*i);
		}
	}
}
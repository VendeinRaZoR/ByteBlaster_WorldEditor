#ifndef _CPAGE_2_H_
#define _CPAGE_2_H_

#include "CMainWindow.h"

class CPage_2 : public wxWindow//Настройки окна вида
{
public:
	CPage_2(wxWindow * pParentWindow,wxPoint Position,wxSize Size);
	~CPage_2();
	DECLARE_EVENT_TABLE()
};


#endif
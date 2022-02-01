#ifndef _CTOOLMENU_H_
#define _CTOOLMENU_H_

#include "CMainWindow.h"

class CToolMenu : public wxWindow
{
public:
	CToolMenu(wxWindow * pParentWindow):wxWindow(pParentWindow,-1)
	{
	}
	~CToolMenu(){}
//DECLARE_EVENT_TABLE()
};

#endif
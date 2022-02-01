#ifndef _CPAGE_1_H_
#define _CPAGE_1_H_

#include "CMainWindow.h"

class CPage_1 : public wxWindow//Настройки окна вида
{
	wxSlider * pSlider_1;
public:
	CPage_1(wxWindow * pParentWindow,wxPoint Position,wxSize Size);
	~CPage_1();
	DECLARE_EVENT_TABLE()
};

enum
{
	wxSLIDER_1 = wxID_HIGHEST + 10
};

#endif
#include "CPage_1.h"

wxBEGIN_EVENT_TABLE(CPage_1, wxWindow)
EVT_COMMAND_SCROLL_CHANGED(wxSLIDER_1,CRenderWindow::OnScroll)
wxEND_EVENT_TABLE()

CPage_1::CPage_1(wxWindow * pParentWindow,wxPoint Position,wxSize Size):wxWindow(pParentWindow,-1,Position,Size)
	{
	wxPanel *panel = new wxPanel(this,-1,wxPoint(-1,-1),wxSize(200,600));
    wxStaticBox *pGroupBox_1 = new wxStaticBox(panel, wxID_ANY, "Camera Options",wxPoint(0,10),wxSize(190,100));
	wxStaticBox *pGroupBox_2 = new wxStaticBox(panel, wxID_ANY, "Screen Options",wxPoint(0,120),wxSize(190,100));
	wxStaticText *pStatic_1 = new wxStaticText(pGroupBox_1, wxID_ANY, "Camera Speed",wxPoint(5,20),wxSize(190,20));
	pSlider_1 = new wxSlider(pGroupBox_1,wxSLIDER_1,1,0,100,wxPoint(10,40),wxSize(160,30));
//pSlider_1->Show(true);
//pSlider_1->SetValue(50);

	}


CPage_1::~CPage_1()
{

}

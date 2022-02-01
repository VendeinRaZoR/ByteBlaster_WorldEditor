#include "CPage_2.h"

wxBEGIN_EVENT_TABLE(CPage_2, wxWindow)
//EVT_COMMAND_SCROLL_CHANGED(wxSLIDER_1,CPage_1::OnScroll)
//EVT_BUTTON(wxBUTTON_1,CMainWindow::OnNewFile)
EVT_BUTTON(wxBUTTON_2,CMainWindow::OnFileOpen)
wxEND_EVENT_TABLE()

CPage_2::CPage_2(wxWindow * pParentWindow,wxPoint Position,wxSize Size):wxWindow(pParentWindow,-1,Position,Size)
	{
	wxPanel *panel = new wxPanel(this,-1,wxPoint(-1,-1),wxSize(200,600));
	wxStaticBox *pGroupBox_1 = new wxStaticBox(panel, wxID_ANY, "Start",wxPoint(0,10),wxSize(190,200));
	wxStaticText *pStatic_1 = new wxStaticText(pGroupBox_1, wxID_ANY, "This is a ByteBlaster World Editor\nVersion 0.1 Alpha\nBy Vendein_RaZoR",wxPoint(5,30),wxSize(190,40));
	wxStaticText *pStatic_2 = new wxStaticText(pGroupBox_1, wxID_ANY, "Let's start :\n",wxPoint(5,70),wxSize(190,15));
	wxButton * pButton_1 = new wxButton(pGroupBox_1,wxBUTTON_1,"Create New Terrain",wxPoint(5,90));
	wxButton * pButton_2 = new wxButton(pGroupBox_1,wxBUTTON_2,"Open Terrain",wxPoint(5,120));
    }

CPage_2::~CPage_2()
{

}

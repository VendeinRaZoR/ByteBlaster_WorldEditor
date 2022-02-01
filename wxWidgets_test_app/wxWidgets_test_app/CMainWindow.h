// wxWidgets "Hello world" Program
// For compilers that support precompilation, includes "wx/wx.h".
#ifndef _CMAINWINDOW_H_
#define _CMAINWINDOW_H_

    #include <wx/wx.h>
#include <wx/aui/aui.h>
#include "resource.h"
#include "CRenderWindow.h"
#include "CPage_1.h"
#include "CPage_2.h"

#define MENU_NUM 3
#define SUB_MENU_NUM 2

    class CMainApp: public wxApp // MainApp is the class for our application
    { 
    // MainApp just acts as a container for the window,
    public: // or frame in MainFrame
      virtual bool OnInit();
    };
 
    class CMainWindow: public wxFrame // MainFrame is the class for our window,
    {
		wxString m_szMenuItem[MENU_NUM];
		wxMenu * m_pMainMenu[MENU_NUM];
		wxMenu * m_pSubMainMenu[SUB_MENU_NUM];
		wxMenuBar * m_pMainMenuBar;
		wxToolBar * m_pMainToolBar;
		wxAuiNotebook * m_pNotebook;
		wxAuiManager *m_pManager;
    public:
		wxNotebook * m_pToolBar;
    public:
      CMainWindow( const wxString &title, const wxPoint &pos ,const wxSize &size);
	  CMainWindow();
	  ~CMainWindow();
      void OnExit( wxCommandEvent& event );
	  void OnNewFile( wxCommandEvent& event );
	  void OnAbout( wxCommandEvent& event );
	  void OnFileOpen( wxCommandEvent& event );
	  void OnFileClose( wxCommandEvent& event );
	  void OnRenderOGL( wxCommandEvent& event );
	  void OnRenderDX( wxCommandEvent& event );
	  void CreateMainMenu();
	  void CreateMainToolBar();
	  void CreateToolWindow();
 
     DECLARE_EVENT_TABLE()
    };
 
    enum
    {
      wxMENU_RENDER_OGL = wxID_HIGHEST + 1, // declares an id which will be used to call our button
	  wxMENU_RENDER_DX,
	  wxMENU_RM_GRID
    };

	enum
{
	wxBUTTON_1 = wxID_HIGHEST + 20,
	wxBUTTON_2
};

#endif
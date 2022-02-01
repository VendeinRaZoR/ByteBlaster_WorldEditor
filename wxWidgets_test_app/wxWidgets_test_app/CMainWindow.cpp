#include "CMainWindow.h"

#define DEFAULT_RENDER_API "DirectX"

//Создаваемые окна (возможность редактирования содержимого)
CRenderWindow *g_pRenderWindow;
CPage_1 * m_pViewOptions;
CPage_2 * m_pMainPage;

//Event Table 
 wxBEGIN_EVENT_TABLE(CMainWindow, wxFrame)
    EVT_MENU(wxID_NEW,   CMainWindow::OnNewFile)
	EVT_MENU(wxID_OPEN,   CMainWindow::OnFileOpen)
    EVT_MENU(wxID_EXIT,  CMainWindow::OnExit)
    EVT_MENU(wxID_ABOUT, CMainWindow::OnAbout)
	EVT_MENU(wxID_CLOSE, CMainWindow::OnFileClose)
    EVT_MENU(wxMENU_RENDER_OGL, CMainWindow::OnRenderOGL)
	EVT_MENU(wxMENU_RENDER_DX, CMainWindow::OnRenderDX)
wxEND_EVENT_TABLE()

  // Initializes the MainApp class and tells our program
  // to run it
  bool CMainApp::OnInit()
  {
    // Create an instance of our frame, or window
    CMainWindow *MainWin = new CMainWindow("Byte Blaster World Editor v0.2", wxPoint(10, 10),wxSize(800,600));
	MainWin->Center();
	MainWin->Show(true); // show the window
	MainWin->SetIcon(wxIcon("bitmap1.bmp",wxBITMAP_TYPE_BMP));//SetIcon
    SetTopWindow(MainWin); // and finally, set it as the main window
   return TRUE;
  } 

 CMainWindow::CMainWindow()//Default c-tor for smth
 {
	m_pManager = NULL;
	//m_pManager = new wxAuiManager(this);
 }

  CMainWindow::CMainWindow(const wxString &title, const wxPoint &pos,const wxSize &size): wxFrame((wxFrame*)NULL,  - 1, title, pos,size)
  {
  //wxPanel *panel = new wxPanel(this, wxID_ANY,wxDefaultPosition,wxSize(20,100));
    //wxAuiToolBar * pDockToolBar = new wxAuiToolBar(this,wxID_ANY,wxPoint(0,0),wxSize(200,40));
	//pDockToolBar->AddControl(new wxControl(this,wxID_ANY));
	//pDockToolBar->AddTool(0,"Tool1",wxBitmap("bitmap1.bmp",wxBITMAP_TYPE_BMP) );
	m_pManager = NULL;
	m_pManager = new wxAuiManager(this);
	CreateMainMenu();
	CreateMainToolBar();
	CreateStatusBar();
	CreateToolWindow();
  }

  CMainWindow::~CMainWindow()
  {
	if(m_pManager)
	m_pManager->UnInit();
	if(m_pToolBar)
	delete m_pToolBar; 
  }

 void CMainWindow::CreateMainMenu()
 {
	for(int i = 0;i<MENU_NUM;i++)
	m_pMainMenu[i] = new wxMenu();
	for(int i = 0;i<SUB_MENU_NUM;i++)
	m_pSubMainMenu[i] = new wxMenu();
	m_pMainMenu[0]->Append(wxID_NEW, "&New\t","Create new file");
	m_pMainMenu[0]->Append(wxID_OPEN, "&Open\t","Open file");
	m_pMainMenu[0]->Append(wxID_CLOSE, "&Close\t","Close this file");
	m_pMainMenu[0]->Append(wxID_EXIT, "&Exit\t","Exit");

	m_pMainMenu[2]->Append(wxID_ABOUT, "&About\t","About us :)");

	m_pMainMenu[1]->AppendSubMenu(m_pSubMainMenu[0],"Choose Render Device");
	m_pSubMainMenu[0]->Append(wxMENU_RENDER_OGL,"OpenGL");
	m_pSubMainMenu[0]->Append(wxMENU_RENDER_DX,"DirectX");
	m_pSubMainMenu[0]->Enable(wxMENU_RENDER_OGL,false);
	m_pSubMainMenu[0]->Enable(wxMENU_RENDER_DX,false);
	m_pMainMenu[1]->AppendSubMenu(m_pSubMainMenu[1],"Terrain Render Modes");
	m_pSubMainMenu[1]->Append(wxMENU_RM_GRID,"Grid");
	m_pSubMainMenu[1]->Enable(wxMENU_RM_GRID,false);
	///Other ....
	m_szMenuItem[0] = wxString("File");
	m_szMenuItem[1] = wxString("Render");
	m_szMenuItem[2] = wxString("Help");
	m_pMainMenuBar = new wxMenuBar(MENU_NUM,&m_pMainMenu[0],m_szMenuItem);
	SetMenuBar(m_pMainMenuBar);
	//Toolbar then 
 }
 
 void CMainWindow::CreateMainToolBar()
 {
  m_pMainToolBar = CreateToolBar();
  m_pMainToolBar->AddTool(wxID_ANY, wxBitmap(wxT("bitmap1.bmp"), wxBITMAP_TYPE_BMP), wxT(""));
  m_pMainToolBar->AddSeparator();
  m_pMainToolBar->Realize();
 }

  void CMainWindow::OnExit( wxCommandEvent& event )
  {
	this->Close(false);
  }

  void CMainWindow::OnNewFile(wxCommandEvent &event)
  {
	 //Render Window with OpenGL
	g_pRenderWindow = new CRenderWindow(wxString(DEFAULT_RENDER_API),this,wxDefaultPosition,wxSize(640,480));
	g_pRenderWindow->Show(true);
	g_pRenderWindow->Center();
	m_pManager->AddPane(g_pRenderWindow, wxAuiPaneInfo().CenterPane());//Dockable window
	m_pManager->Update();
	m_pSubMainMenu[0]->Enable(wxMENU_RENDER_OGL,true);
	m_pSubMainMenu[0]->Enable(wxMENU_RENDER_DX,true);
	m_pViewOptions->Enable(true);
  }

  void CMainWindow::OnAbout(wxCommandEvent &event)
  {
   wxMessageBox( "This is a Byte Blaster World Editor v0.2 by Vendein_RaZoR","About Editor", wxOK | wxICON_INFORMATION );
  }

  void CMainWindow::OnFileOpen(wxCommandEvent& event)
  {
wxFileDialog dlg(this, "Choose a file", wxEmptyString, wxEmptyString,
		wxT("Terrain File (*.raw)|*.raw"), wxFD_OPEN);
dlg.ShowModal();
  }

  void CMainWindow::OnFileClose( wxCommandEvent& event )
  {
	  RemoveChild(g_pRenderWindow);
	m_pSubMainMenu[0]->Enable(wxMENU_RENDER_OGL,false);
	m_pSubMainMenu[0]->Enable(wxMENU_RENDER_DX,false);
	m_pViewOptions->Enable(false);
	//  g_pRenderWindow->Show(false);
	  delete g_pRenderWindow;
  }

  	  void CMainWindow::OnRenderOGL( wxCommandEvent& event )
	  {
SetTitle(wxString("Byte Blaster World Editor v0.2 Render [OpenGL]"));
g_pRenderWindow->SetRenderDevice(wxString("OpenGL"));
	  }

	  void CMainWindow::OnRenderDX( wxCommandEvent& event )
	  {
SetTitle(wxString("Byte Blaster World Editor v0.2 Render [DirectX]"));
g_pRenderWindow->SetRenderDevice(wxString("DirectX"));
	  }

  void CMainWindow::CreateToolWindow()
  {
m_pToolBar = new wxNotebook(this,-1);
m_pViewOptions = new CPage_1(m_pToolBar,wxDefaultPosition,wxSize(200,600));
m_pMainPage = new CPage_2(m_pToolBar,wxDefaultPosition,wxSize(200,600));
m_pMainPage->Bind( wxEVT_BUTTON, &CMainWindow::OnNewFile,this, wxBUTTON_1 );
m_pViewOptions->Enable(false);
m_pToolBar->Show(true);
m_pToolBar->AddPage(m_pMainPage,"Start Page",false);
m_pToolBar->AddPage(m_pViewOptions,"View Options",false);
m_pManager->AddPane(m_pToolBar, wxAuiPaneInfo().BestSize(200,600).Right().Floatable(false).Resizable(false));
m_pManager->Update();
  }
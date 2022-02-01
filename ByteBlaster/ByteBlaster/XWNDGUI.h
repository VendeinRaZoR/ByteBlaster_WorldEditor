#include "XWND.h"

#define MAX_HEADING_LEN 256

#define BS_STANDARTBUTTON WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON
#define ES_STANDARTEDITBOX WS_CHILD|WS_VISIBLE|WS_BORDER|ES_LEFT
#define BS_STANDARTGROUPBOX WS_CHILD|WS_VISIBLE|BS_GROUPBOX
#define BS_STANDARTSCROLLBAR WS_CHILD|SBS_SIZEBOX
#define BS_STANDARTSTATIC WS_CHILD|WS_VISIBLE
#define LBS_STANDARTLISTBOX WS_CHILD|WS_VISIBLE|LBS_STANDARD|LBS_WANTKEYBOARDINPUT

	  typedef struct 
       { 
     TCHAR tchHeading[MAX_HEADING_LEN]; 
   int tchLevel; 
    }Heading; 

class CGUIManager
{
public:
	CGUIManager();
	~CGUIManager();
	void InitCommonGUI(HWND hwnd);
	BOOL DestroyCommonGUI();
	////////////-----------------------------------------
	struct BUTTONSTRUCT
	{
	HWND CreateButton(int nButtonID,DWORD bStyle,int nX,int nY,int nWx,int nHy,char * szwText);
	void Init(HWND hwnd);
	private:
	void SetClassName();
    HWND hButton;
    char szbClassName[256];
    HWND _hwnd;
	}sButton,*BUTTONSTRUCT;
	/////////////////////////////////////////////////////////---------------
	struct EDITBOXSTRUCT
	{
	HWND CreateEditBox(int nButtonID,DWORD bStyle,int nX,int nY,int nWx,int nHy,char * szwText);
	void Init(HWND hwnd);
	private:
	void SetClassName();
    HWND hEditBox;
    char szbClassName[256];
    HWND _hwnd;
	}sEditBox,*EDITBOXSTRUCT;
	//////////////////////////////////////////////////////////--------------
	struct STATICSTRUCT
	{
	HWND CreateStatic(int nButtonID,DWORD bStyle,int nX,int nY,int nWx,int nHy,char * szwText);
	void Init(HWND hwnd);
	private:
	void SetClassName();
    HWND hStatic;
    char szbClassName[256];
    HWND _hwnd;
	}sStatic,*STATICSTRUCT;
////////////------------------------------------
	struct RADIOBUTTONSTRUCT
	{
	HWND CreateRadioButton(int nButtonID,int nX,int nY,int nWx,int nHy,char * szwText);
	void Init(HWND hwnd);
	private:
	void SetClassName();
HWND hRadioButton;
char szbClassName[256];
HWND _hwnd;
	}sRadioButton,*RADIOBUTTONSTRUCT;
//////////////----------------------------------------------------
	struct SCROLLBARSTRUCT
	{
	HWND CreateScrollBar(int nButtonID,int nX,int nY,int nWx,int nHy,char * szwText);
	void Init(HWND hwnd);
	private:
	void SetClassName();
HWND hScrollBar;
char szsbClassName[256];
HWND _hwnd;
	}sScrollBar,*SCROLLBARSTRUCT;
////////------------------------------------------------------------------
	struct STRUCTLISTBOX
	{
	HWND CreateListBox(int nListBoxID,int nX,int nY,int nWx,int nHy);
	void Init(HWND hwnd);
	private:
	void SetClassName();
HWND hListBox;
char szlbClassName[256];
HWND _hwnd;
	}sListBox,*STRUCTLISTBOX;
////////------------------------------------------------------------------
	struct STRUCTSTATUSBAR
	{
	HWND CreateStatusBar(int nStatusBarID,int nX,int nY,int nWx,int nHy,char * szwText);
	void Init(HWND hwnd);
	private:
	void SetClassName();
HWND hStatusBar;
char szsbClassName[256];
HWND _hwnd;
	}sStatusBar,*STRUCTSTATUSBAR;
////////------------------------------------------------------------------
	struct STRUCTPROGRESSBAR
	{
	HWND CreateProgressBar(int nProgressBarID,int nX,int nY,int nWx,int nHy);
	void Init(HWND hwnd);
	private:
	void SetClassName();
HWND hProgressBar;
char szpbClassName[256];
HWND _hwnd;
	}sProgressBar,*STRUCTPROGRESSBAR;
////////------------------------------------------------------------------
	struct STRUCTTREEVIEW
	{
	HWND CreateTreeView(int nTreeViewID,int nX,int nY,int nWx,int nHy);
	void Init(HWND hwnd);
	BOOL InitTreeViewImageLists(HWND hwndTV);
	HTREEITEM AddItemToTree(HWND hwndTV, LPTSTR lpszItem, int nLevel);
	BOOL InitTreeViewItems(HWND hwndTV);
	private:
	void SetClassName();
HWND hTreeView;
HINSTANCE g_hInst;
int g_nOpen;
int g_nDocument;
int g_nClosed;
char sztvClassName[256];
HWND _hwnd;
  Heading g_rgDocHeadings;
	}sTreeView,*STRUCTTREEVIEW;
////////------------------------------------------------------------------
	struct STRUCTIPADRESSBAR
	{
	HWND CreateIPAdressBar(int nIPAdressBarID,int nX,int nY,int nWx,int nHy);
	void Init(HWND hwnd);
	private:
	void SetClassName();
HWND hIPAdressBar;
char sziaClassName[256];
HWND _hwnd;
	}sIPAdressBar,*STRUCTIPADRESSBAR;
////////------------------------------------------------------------------
   	struct STRUCTLISTVIEW
	{
	HWND CreateListView(int nListViewID,int nX,int nY,int nWx,int nHy);
	void Init(HWND hwnd);
	private:
	void SetClassName();
HWND hListView;
char szlvClassName[256];
HWND _hwnd;
	}sListView,*STRUCTLISTVIEW;
////////------------------------------------------------------------------
	struct STRUCTTOOLBAR
	{
	HWND CreateListView(int nToolBarID,int nX,int nY,int nWx,int nHy);
	void Init(HWND hwnd);
	private:
	void SetClassName();
HWND hToolBar;
char sztbClassName[256];
HWND _hwnd;
	}sToolBar,*STRUCTTOOLBAR;
////////------------------------------------------------------------------
};
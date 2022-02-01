#include "XWNDGUI.h"

#define IDD_ABOUT 9005

CGUIManager::CGUIManager()
{
}

CGUIManager::~CGUIManager()
{
}
//-----------InitCommonGUI--------------------
void CGUIManager::InitCommonGUI(HWND hwnd)
{
sButton.Init(hwnd);
sEditBox.Init(hwnd);
sStatic.Init(hwnd);
sRadioButton.Init(hwnd);
sScrollBar.Init(hwnd);
sListBox.Init(hwnd);
sStatusBar.Init(hwnd);
sProgressBar.Init(hwnd);
sTreeView.Init(hwnd);
}
//-------------------Button----------------
HWND CGUIManager::BUTTONSTRUCT::CreateButton(int nButtonID,DWORD bStyle,int nX,int nY,int nWx,int nHy,char * szwText)
{
	CGUIManager::BUTTONSTRUCT::SetClassName();
	hButton = CreateWindowA(szbClassName,
		szwText,bStyle,
		nX,nY,nWx,nHy,_hwnd,
		(HMENU)nButtonID,0,0);
	return hButton;
}

void CGUIManager::BUTTONSTRUCT::Init(HWND hwnd)
{
	_hwnd = hwnd;
}

void CGUIManager::BUTTONSTRUCT::SetClassName()
{
strcpy(szbClassName,"button");
}

//-------------------EditBox----------------
HWND CGUIManager::EDITBOXSTRUCT::CreateEditBox(int nEditID, DWORD bStyle, int nX, int nY, int nWx, int nHy, char *szwText)
{
CGUIManager::EDITBOXSTRUCT::SetClassName();
hEditBox = CreateWindowA(szbClassName,szwText,bStyle,nX,nY,nWx,nHy,_hwnd,(HMENU)nEditID,0,0);
return hEditBox;
}

void CGUIManager::EDITBOXSTRUCT::Init(HWND hwnd)
{
_hwnd = hwnd;
}

void CGUIManager::EDITBOXSTRUCT::SetClassName()
{
strcpy(szbClassName,WC_EDIT);
}

//-------------------Static----------------
HWND CGUIManager::STATICSTRUCT::CreateStatic(int nEditID, DWORD bStyle, int nX, int nY, int nWx, int nHy, char *szwText)
{
CGUIManager::STATICSTRUCT::SetClassName();
hStatic = CreateWindowA(szbClassName,szwText,bStyle,nX,nY,nWx,nHy,_hwnd,(HMENU)nEditID,0,0);
return hStatic;
}

void CGUIManager::STATICSTRUCT::Init(HWND hwnd)
{
_hwnd = hwnd;
}

void CGUIManager::STATICSTRUCT::SetClassName()
{
strcpy(szbClassName,WC_STATIC);
}

//-------------------RadioButton----------------
HWND CGUIManager::RADIOBUTTONSTRUCT::CreateRadioButton(int nButtonID,int nX,int nY,int nWx,int nHy,char * szwText)
{
	CGUIManager::RADIOBUTTONSTRUCT::SetClassName();
	hRadioButton = CreateWindowA(szbClassName,
		szwText,WS_VISIBLE|WS_CHILD|BS_AUTOCHECKBOX,
		nX,nY,nWx,nHy,_hwnd,
		(HMENU)nButtonID,0,0);
	return hRadioButton;
}

void CGUIManager::RADIOBUTTONSTRUCT::Init(HWND hwnd)
{
	_hwnd = hwnd;
}

void CGUIManager::RADIOBUTTONSTRUCT::SetClassName()
{
strcpy(szbClassName,WC_BUTTON);
}

//-------------------ScrollBar----------------
HWND CGUIManager::SCROLLBARSTRUCT::CreateScrollBar(int nButtonID,int nX,int nY,int nWx,int nHy,char * szwText)
{
	CGUIManager::SCROLLBARSTRUCT::SetClassName();
    hScrollBar = CreateWindowA(szsbClassName,
		szwText,WS_CHILD|BS_AUTOCHECKBOX,
		nX,nY,nWx,nHy,_hwnd,
		(HMENU)nButtonID,0,0);
	return hScrollBar;
}

void CGUIManager::SCROLLBARSTRUCT::SetClassName()
{
strcpy(szsbClassName,WC_SCROLLBAR);
}

void CGUIManager::SCROLLBARSTRUCT::Init(HWND hwnd)
{
	_hwnd = hwnd;
}

//-------------------ListBox----------------
HWND CGUIManager::STRUCTLISTBOX::CreateListBox(int nListBoxID, int nX, int nY, int nWx, int nHy)
{
	CGUIManager::STRUCTLISTBOX::SetClassName();
    hListBox = CreateWindowA(szlbClassName,
		0,LBS_STANDARTLISTBOX,
		nX,nY,nWx,nHy,_hwnd,
		(HMENU)nListBoxID,0,0);
return hListBox;
}

void CGUIManager::STRUCTLISTBOX::Init(HWND hwnd)
{
	_hwnd = hwnd;
}

void CGUIManager::STRUCTLISTBOX::SetClassName()
{
	strcpy(szlbClassName,WC_LISTBOX);
}

//-------------------StatusBar----------------
void CGUIManager::STRUCTSTATUSBAR::SetClassName()
{
strcpy(szsbClassName,STATUSCLASSNAME);
}

HWND CGUIManager::STRUCTSTATUSBAR::CreateStatusBar(int nStatusBarID, int nX, int nY, int nWx, int nHy,char *szwText)
{
		CGUIManager::STRUCTSTATUSBAR::SetClassName();
    hStatusBar = CreateWindowA(szsbClassName,
		szwText,WS_VISIBLE|WS_CHILD,
		nX,nY,nWx,nHy,_hwnd,
		(HMENU)nStatusBarID,0,0);
return hStatusBar;
}

void CGUIManager::STRUCTSTATUSBAR::Init(HWND hwnd)
{
_hwnd = hwnd;
}

//-------------------ProgressBar----------------
HWND CGUIManager::STRUCTPROGRESSBAR::CreateProgressBar(int nProgressBarID, int nX, int nY, int nWx, int nHy)
{
	CGUIManager::STRUCTPROGRESSBAR::SetClassName();
    hProgressBar = CreateWindowA(szpbClassName,
		0,WS_VISIBLE|WS_CHILD,
		nX,nY,nWx,nHy,_hwnd,
		(HMENU)nProgressBarID,0,0);
return hProgressBar;
}

void CGUIManager::STRUCTPROGRESSBAR::Init(HWND hwnd)
{
	_hwnd = hwnd;
}

void CGUIManager::STRUCTPROGRESSBAR::SetClassName()
{
	strcpy(szpbClassName,PROGRESS_CLASS);
}
//-------------------TreeView--------------------
HWND CGUIManager::STRUCTTREEVIEW::CreateTreeView(int nTreeViewID, int nX, int nY, int nWx, int nHy)
{
	CGUIManager::STRUCTTREEVIEW::SetClassName();
    hTreeView = CreateWindowEx(0,
                            WC_TREEVIEW,
                            "Tree View",
                            WS_VISIBLE | WS_CHILD | WS_BORDER | TVS_HASLINES, 
                            nX, 
                            nY, 
                            nWx, 
                            nHy,
                            _hwnd, 
                            (HMENU)nTreeViewID, 
                            g_hInst, 
                            NULL); 
   if (!InitTreeViewImageLists(hTreeView) || 
                !InitTreeViewItems(hTreeView))
    { 
        DestroyWindow(hTreeView); 
        return FALSE; 
    } 
	return hTreeView;
}

void CGUIManager::STRUCTTREEVIEW::Init(HWND hwnd)
{
	_hwnd = hwnd;
}

void CGUIManager::STRUCTTREEVIEW::SetClassName()
{
	strcpy(sztvClassName,WC_TREEVIEW);
}

BOOL CGUIManager::STRUCTTREEVIEW::InitTreeViewImageLists(HWND hwndTV) 
{ 
    HIMAGELIST himl; 
    HBITMAP hbmp;    
	HANDLE bitmap;
    if ((himl = ImageList_Create(10,10,FALSE, 3,0))== NULL) 
    return FALSE; 
	bitmap = LoadImage(g_hInst,"tray.bmp",IMAGE_BITMAP,10,10,LR_LOADFROMFILE);
    g_nOpen = ImageList_Add(himl, (HBITMAP)bitmap, NULL); 
	g_nClosed = ImageList_Add(himl, (HBITMAP)bitmap, NULL);   
	g_nDocument = ImageList_Add(himl, (HBITMAP)bitmap, NULL); 
    if (ImageList_GetImageCount(himl) < 3) 
    return FALSE; 
    TreeView_SetImageList(hwndTV, himl, TVSIL_NORMAL); 
    return TRUE; 
} 

HTREEITEM CGUIManager::STRUCTTREEVIEW::AddItemToTree(HWND hwndTV, LPTSTR lpszItem, int nLevel)
{ 
    TVITEM tvi; 
    TVINSERTSTRUCT tvins; 
	HTREEITEM hti; 
    static HTREEITEM hPrev = (HTREEITEM)TVI_FIRST; 
    static HTREEITEM hPrevRootItem = NULL; 
    static HTREEITEM hPrevLev2Item = NULL; 
    tvi.mask = TVIF_TEXT | TVIF_IMAGE 
               | TVIF_SELECTEDIMAGE | TVIF_PARAM; 
    tvi.pszText = lpszItem; 
    tvi.cchTextMax = sizeof(tvi.pszText)/sizeof(tvi.pszText[0]); 
    tvi.iImage = g_nDocument; 
    tvi.iSelectedImage = g_nDocument; 
    tvi.lParam = (LPARAM)nLevel; 
    tvins.item = tvi; 
    tvins.hInsertAfter = hPrev; 
    if (nLevel == 1) 
        tvins.hParent = TVI_ROOT; 
    else if (nLevel == 2) 
        tvins.hParent = hPrevRootItem; 
    else 
        tvins.hParent = hPrevLev2Item; 
    hPrev = (HTREEITEM)SendMessage(hwndTV, TVM_INSERTITEM, 
        0, (LPARAM)(LPTVINSERTSTRUCT)&tvins); 
    if (hPrev == NULL)
        return NULL;
    if (nLevel == 1) 
        hPrevRootItem = hPrev; 
    else if (nLevel == 2) 
        hPrevLev2Item = hPrev; 
    if (nLevel > 1)
    { 
        hti = TreeView_GetParent(hwndTV, hPrev); 
        tvi.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE; 
        tvi.hItem = hti; 
        tvi.iImage = g_nClosed; 
        tvi.iSelectedImage = g_nClosed; 
        TreeView_SetItem(hwndTV, &tvi); 
    } 

    return hPrev; 
} 

BOOL CGUIManager::STRUCTTREEVIEW::InitTreeViewItems(HWND hwndTV)
{ 
 HTREEITEM hti;
 AddItemToTree(hwndTV,"General",1); 
 hti = AddItemToTree(hwndTV,"Vendein_RaZoR",2); 
 AddItemToTree(hwndTV,"Всякие юзеры",2); 
        if (hti == NULL)
		{
        return FALSE;    
		}
    return TRUE; 
}
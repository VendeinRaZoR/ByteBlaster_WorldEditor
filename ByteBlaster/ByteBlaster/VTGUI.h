#ifndef _VRGUI_
#define _VRGUI_

#include "VWindow.h"
#include "VEventHandler.h"

#define MAX_TBBUTTON 256
#define MAX_SYMBOLS 128

class VBaseGUIElement
{
protected:
	int m_nElemID;
	int m_nSx,m_nSy,m_nX,m_nY;
	char * m_szElementName;
	char * m_szElementTitle;
	HWND m_hGuiElement;
	VBaseWindow *m_pBaseWindow;
	VEvent * m_pEvent;
public:
	VTAPI VBaseGUIElement(VBaseWindow * pBaseWindow = NULL);
	VTAPI ~VBaseGUIElement();
public:
	VTAPI void Create(char * lpcElementName,LPCSTR lpcElementType,int nX,int nY,int nSx,int nSy);
	VTAPI void SetSize(int nSx,int nSy);
	VTAPI void SetPosition(int nX,int nY);
	VTAPI void SetText(LPCSTR lpcElementText);
	VTAPI void SetID(int nID);
	VTAPI int GetID();
	VTAPI bool isActive();
	VTAPI char * GetElementName();
	VTAPI void SetElementName(char * szElementName);
    VTAPI char * GetText();
	VTAPI UINT GetInt();
};

class VTGuiManager
{
	VBaseGUIElement *BaseGUIElement;
	list<VBaseGUIElement*>m_lGUIElement;
	VBaseWindow *m_pBaseWindow;
	TBBUTTON m_tbButton[MAX_TBBUTTON];
	int m_ntbButton;
private:
	//Menu
	HMENU m_hMenu;
	int m_nCol,m_nRow;
	char **m_szMenuTable;
	HMENU *m_hPopupMenu;
	//////////////////
	HWND m_hToolBar;
    HWND m_hStatusBar;
public:
	VTAPI VTGuiManager(VBaseWindow * pBaseWindow = NULL);
	 VTAPI ~VTGuiManager();
	 void Initialize(VBaseWindow * pBaseWindow = NULL);
public:
	VTAPI BOOL CreateTopMenu(/*char **szMenuTable,int nRow,int nCol*/);
    VTAPI void CreateStatusBar();
	VTAPI void CreateToolBar();
public:
	 VTAPI void AddElement(char * lpcElementName,LPCSTR lpcElementType,char * szElementTitle,int nX,int nY,int nSx,int nSy);
	 VTAPI void AddElement(int nElemID);
	 VTAPI void DeleteElement();
	 VTAPI bool isEmpty();
	 VTAPI int NumOfElem();
	 VTAPI int GetElementID(char * szElementName);
	 VTAPI VBaseGUIElement * GetElementByID(int nID);
	 VTAPI void AddToolbarElement(char * szElementName,int nCommand,BYTE btStyle,BYTE btState,int nBitmap);
};
#endif

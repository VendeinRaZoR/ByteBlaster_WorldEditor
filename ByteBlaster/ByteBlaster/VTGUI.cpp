#include "VTGUI.h"

int g_nElementID;

VBaseGUIElement::VBaseGUIElement(VBaseWindow * pBaseWindow)
	{
		m_pBaseWindow = pBaseWindow;
		m_hGuiElement = 0;
		m_pEvent = new VEvent(m_pBaseWindow,WM_COMMAND);
	}

VBaseGUIElement::~VBaseGUIElement()
{
}

void VBaseGUIElement::Create(char * lpcElementName,LPCSTR lpcElementType,int nX,int nY,int nSx,int nSy)
{
        m_nX = nX;
		m_nY = nY;
        m_nSx = nSx;
		m_nSy = nSy;
		m_hGuiElement = CreateWindow(lpcElementType,lpcElementName,WS_CHILD | WS_VISIBLE,nX,nY,nSx,nSy,*m_pBaseWindow,(HMENU)m_nElemID,GetHInst(),0);
}

void VBaseGUIElement::SetPosition(int nX, int nY)
{
    m_nX = nX;
	m_nY = nY;
    SetWindowPos(m_hGuiElement,HWND_TOP,nX,nY,m_nSx,m_nSy,SWP_SHOWWINDOW);
}

void VBaseGUIElement::SetSize(int nSx,int nSy)
{
    m_nSx = nSx;
    m_nSy = nSy;
	SetWindowPos(m_hGuiElement,HWND_TOP,m_nX,m_nY,nSx,nSy,SWP_SHOWWINDOW);
}

bool VBaseGUIElement::isActive()
{
	return (LOWORD(m_pEvent->GetEventParam("Param1")) == m_nElemID) ? 1 : 0;
}

char * VBaseGUIElement::GetElementName()
{
	return m_szElementName;
}

void VBaseGUIElement::SetElementName(char * szElementName)
{
	m_szElementName = szElementName;
}

void VBaseGUIElement::SetID(int nID)
{
	m_nElemID = nID;
}

int VBaseGUIElement::GetID()
{
	return m_nElemID;
}


void VBaseGUIElement::SetText(LPCSTR lpcElementText)
{
	SetWindowText(m_hGuiElement,lpcElementText);
}

char * VBaseGUIElement::GetText()
{
	char * szText;
	GetDlgItemText(*m_pBaseWindow,m_nElemID,szText,MAX_SYMBOLS);
	return szText;
}

UINT VBaseGUIElement::GetInt()
{
	return GetDlgItemInt(*m_pBaseWindow,m_nElemID,NULL,true);
}

VTGuiManager::VTGuiManager(VBaseWindow * pBaseWindow)
{
m_pBaseWindow = pBaseWindow;
m_ntbButton = 0;
}

VTGuiManager::~VTGuiManager()
{
g_nElementID = 0;
}

BOOL VTGuiManager::CreateTopMenu(/*char **szMenuTable,int nRow,int nCol*/)
{
      /* m_nRow = nRow;
		m_nCol = nCol;
		m_szMenuTable = new char * [nRow*nCol];
		for(int i=0;i<(nRow*nCol);i++)
       m_szMenuTable[i] = new char[StrLen(szMenuTable[i]+1)];
		for(int i=0;i<(nRow*nCol);i++)
      StrCpy(m_szMenuTable[i],szMenuTable[i]);
	m_hPopupMenu = new HMENU[m_nCol*(m_nRow-1)];
		m_hMenu = CreateMenu();
		for(int i = 0;i<(m_nCol);i++)
		{
		m_hPopupMenu[i] = CreatePopupMenu();
      for(int j = m_nCol+i;j < (m_nRow*m_nCol);j+=(m_nCol))
		{
		if(StrCmp(m_szMenuTable[j],"") != 0)
		AppendMenu(m_hPopupMenu[i], MF_STRING, i, m_szMenuTable[j]);
		}
		if(StrCmp(m_szMenuTable[i],"") != 0)
	    AppendMenu(m_hMenu, MF_STRING | MF_POPUP, (UINT_PTR)m_hPopupMenu[i], m_szMenuTable[i]);
		}*/
	printf("%x\n",m_pBaseWindow->GetWindowHandle());
		SetMenu(*m_pBaseWindow,LoadMenu(GetHInst(),MAKEINTRESOURCE(IDR_MENU2)));
		return TRUE;
}

void VTGuiManager::AddElement(char * lpcElementName,LPCSTR lpcElementType,char * szElementTitle,int nX,int nY,int nSx,int nSy)
{
	BaseGUIElement = new VBaseGUIElement(m_pBaseWindow);
	BaseGUIElement->SetID(g_nElementID++);
	BaseGUIElement->SetElementName(lpcElementName);
	BaseGUIElement->Create(szElementTitle,lpcElementType,nX,nY,nSx,nSy);
	m_lGUIElement.push_back(BaseGUIElement);
}

void VTGuiManager::AddElement(int nElemID)
{
BaseGUIElement = new VBaseGUIElement(m_pBaseWindow);
BaseGUIElement->SetID(nElemID);
m_lGUIElement.push_back(BaseGUIElement);
}

int VTGuiManager::GetElementID(char * szElementName)
{
	for(list<VBaseGUIElement*>::iterator i = m_lGUIElement.begin();i != m_lGUIElement.end();i++)
	{
		if(!String::StrCmp(szElementName,(*i)->GetElementName()))
		return (*i)->GetID();
	}
}

VBaseGUIElement * VTGuiManager::GetElementByID(int nID)
{
		for(list<VBaseGUIElement*>::iterator i = m_lGUIElement.begin();i != m_lGUIElement.end();i++)
	    {
			if(nID == (*i)->GetID())
			{
            return (*i);
			}
		}
}
void VTGuiManager::CreateStatusBar() 
	{
m_hStatusBar = CreateStatusWindow(WS_CHILD | WS_VISIBLE , "Status Bar",*m_pBaseWindow,1000);
	}

void VTGuiManager::AddToolbarElement(char *szElementName, int nCommand, BYTE btStyle, BYTE btState, int nBitmap)
{
    m_tbButton[m_ntbButton].iBitmap=nBitmap;
    m_tbButton[m_ntbButton].idCommand=nCommand;
    m_tbButton[m_ntbButton].fsState= btState;
	m_tbButton[m_ntbButton].fsStyle = btStyle;
	m_tbButton[m_ntbButton].iString = (INT_PTR)szElementName;
	m_tbButton[m_ntbButton].dwData = 0;
	m_ntbButton++;
}

void VTGuiManager::CreateToolBar()
{
 m_hToolBar = CreateToolbarEx(*m_pBaseWindow,WS_CHILD|WS_BORDER|WS_VISIBLE,IDR_TOOLBAR1,m_ntbButton,GetHInst(),IDR_TOOLBAR1,m_tbButton,m_ntbButton,16,16,16,16,sizeof(TBBUTTON));
}
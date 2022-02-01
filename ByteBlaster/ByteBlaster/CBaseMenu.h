#include <windows.h>
#include <tchar.h>
#include <sstream>
#include <stdexcept>
#include <cassert>
#include <windowsx.h>
#include <commctrl.h>
#include "VString.h"

#define MAX_MENU 256

using namespace String;

class CBaseMenu
{
private:
    HMENU m_hMenu;
	int m_nCol,m_nRow;
	char **m_szMenuTable;
	HMENU *m_hPopupMenu;
public:
	CBaseMenu(char **szMenuTable,int nRow,int nCol)
	{
		m_nRow = nRow;
			m_nCol = nCol;
		m_szMenuTable = new char * [nRow*nCol];
		for(int i=0;i<(nRow*nCol);i++)
        m_szMenuTable[i] = new char[StrLen(szMenuTable[i]+1)];
		for(int i=0;i<(nRow*nCol);i++)
       StrCpy(m_szMenuTable[i],szMenuTable[i]);
    //HMENU hSubMenu = CreatePopupMenu();
    //AppendMenu(hSubMenu, MF_STRING, 1, "&Exit");
    //AppendMenu(hMenu, MF_STRING | MF_POPUP, (UINT)hSubMenu, "&File");
	}
	HMENU CreateWindowMenu()
	{
		m_hPopupMenu = new HMENU[m_nCol*(m_nRow-1)];
		for(int i=0, j = (m_nRow-1);j<(m_nCol*(m_nRow-1)),i<(m_nCol*(m_nRow-1));i++,j++)
		{
		m_hPopupMenu[i] = CreatePopupMenu();
		AppendMenu(m_hPopupMenu[i], MF_STRING, j, m_szMenuTable[j]);
		}
		m_hMenu = CreateMenu();
		for(int i=0;i<(m_nCol);i++)
		{
		if(StrCmp(m_szMenuTable[i],"") != 0)
		AppendMenu(m_hMenu, MF_STRING | MF_POPUP, (UINT_PTR)m_hPopupMenu[i], m_szMenuTable[i]);
		}
	return m_hMenu;
	}
	~CBaseMenu(){}
};
#include "VWindow.h"
#include "VTGui.h"
#include "TestWindow.h"
#include "TestChildWindow.h"
#include "RenderWindow.h"
#include <cmath>
#include "VString.h"
#include <TlHelp32.h>
#include "VArray.h"
#include <vector>

CTestWindow *TestWindow;

BOOL wmain(int argc, char **argv)
{
	//INITCOMMONCONTROLSEX initcntrl;
	//initcntrl.dwSize = sizeof(INITCOMMONCONTROLSEX);
	//initcntrl.dwICC = ICC_LISTVIEW_CLASSES;
	//BOOL cmncntrl = InitCommonControlsEx(&initcntrl);
	//FreeConsole(); // - Release Mode
TestWindow = new CTestWindow();
CTestChildWindow TestChildWindow(TestWindow);
return TestWindow->GetMsg();  
}
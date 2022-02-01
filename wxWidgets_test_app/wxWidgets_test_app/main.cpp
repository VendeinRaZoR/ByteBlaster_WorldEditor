#include "CMainWindow.h"

int main(int argc,char **argv)
{
	//FreeConsole();
	CMainApp app;
	wxEntryStart( argc, argv );
	app.CallOnInit();
	app.OnRun();
	return 0;
}
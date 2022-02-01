#ifndef VAPPLICATION_H
#define VAPPLICATION_H

#include "VT.h"
#include "resource.h"

#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <tchar.h>
#include <sstream>
#include <stdexcept>
#include <cassert>
#include <vector>
#include <list>
#include <map>
#include <Tlhelp32.h>
#include "VDebugInfo.h"

#include "VString.h"


using namespace String;

#ifndef STRICT
#define STRICT
#endif

#ifndef WINVER
#define WINVER         0x0500
#endif
#ifndef _WIN32_WINDOWS
#define _WIN32_WINDOWS 0x0500 
#endif
#ifndef _WIN32_WINNT
#define _WIN32_WINNT   0x0600
#endif

#define MAX_ARGLEN 256

#define PROCESS_NAME "ByteBlaster.exe"

#define INIT_CMN_CNTRLS() ((WINVER == _WIN32_WINDOWS) ? InitCommonControls() : NULL) 

#define NULLRETURN {return NULL;}

#define NORETURN {}

/*class VApplication 
{
public:
	VApplication(int argc, char **argv){}
	VApplication(){}
	~VApplication(){}
};
*/
#endif
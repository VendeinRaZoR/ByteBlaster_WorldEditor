#ifndef VDEBUGINFO_H
#define VDEBUGINFO_H
//#include "VT.h"
#include "VApplication.h"

namespace _Debug
{
	void ConsoleInfo(char * szFormat  ...);
	void LogInfo();
	/*void WindowInfo(char * szFormat  ...)
	{
		va_list arglist;
	va_start(arglist,szFormat);
	printf("[Debug] : ");
     while(*(szFormat))
		{
	   if(*szFormat == '%')
			{
	    szFormat++;
		switch(*szFormat)
		{
		case 's':
			{
		char * szString = va_arg(arglist,char*);
		MessageBoxA(0,"[Debug]",szString,MB_ICONWARNING);
		break;
			}
		case 'd':
			{
		int nNumber = va_arg(arglist,int);
	    sprintf("%d",nNumber);
		break;
			}
		case 'c':
			{
		char c = va_arg(arglist,char);
	    printf("%c",*szFormat);
		break;
			}
		case 'x':
			{
		unsigned int nhex = va_arg(arglist,unsigned int);
	    printf("0x%x",nhex);
		break;
			}
		case 'X':
			{
		unsigned int nhex = va_arg(arglist,unsigned int);
	    printf("0x%X",nhex);
		break;
			}
		default:
            printf("%c",*szFormat);
		}
			}else
			{
			printf("%c",*szFormat);
			}
			szFormat++;
		}
		va_end(arglist);
	}*/
	void TextInfo();
};


#endif 
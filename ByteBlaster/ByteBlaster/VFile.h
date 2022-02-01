#include <stdlib.h>
#include <stdio.h>
#include <cstdarg>
#include <fstream>

#define READ "r"
#define WRITE "w"
#define READUPDATE "r+"
#define WRITEUPDATE "w+"
#define APPEND "a"
#define APPENDUPDATE "a+"

using namespace std;

class VFile
{
FILE *m_File;
VString m_pFileName;
public:
	VFile(char * pFileName = '\0',const char * szMode = WRITE)
	{
	m_File = NULL;
	m_pFileName = pFileName;
    m_File = fopen(m_pFileName,szMode);
	}
////////////////////////////////
//C File Working
////////////////////////////////
virtual bool Write(char * szFormat ...);
virtual bool Read(char * szFormat ...);
virtual void Read(size_t NumBytes,char * szBuffer);
virtual void Close(){fclose(m_File);}
virtual void Clear(){fclose(fopen (m_pFileName,WRITE));}

long size()
{
long size;
fseek(m_File, 0, SEEK_END);
size = ftell(m_File);
return size;
}
////////////////////////////////
//C++ File Working
////////////////////////////////
template <class WFType>VFile &operator<<(WFType wfVal);
template <class WFType>VFile &operator>>(WFType &wfVal);//TODO !!!
////////////////////////////////
	~VFile()
	{
		if(m_File != 0)
			fclose(m_File);
	}
};

bool VFile::Write(char * szFormat ...)
{
	va_list arglist;
	va_start(arglist,szFormat);
	if (m_File == NULL)return 0;
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
		fputs(szString,m_File);
		break;
			}
		case 'f':
			{
		float fNumber = va_arg(arglist,float);
		fprintf(m_File,"%.f",fNumber);////Changed .after
		break;
			}
		case 'd':
			{
		int nNumber = va_arg(arglist,int);
	    fprintf(m_File,"%d",nNumber);
		break;
			}
		case 'c':
			{
		char c = va_arg(arglist,char);
	    fputc(c,m_File);
		break;
			}
		case 'x':
			{
		unsigned int nhex = va_arg(arglist,unsigned int);
	    fprintf(m_File,"0x%x",nhex);
		break;
			}
		case 'X':
			{
		unsigned int nhex = va_arg(arglist,unsigned int);
	    fprintf(m_File,"0x%X",nhex);
		break;
			}
		default:
              fputc(*szFormat,m_File);
		}
	   }else
			{
			fputc(*szFormat,m_File);
			}
			szFormat++;
		}
		va_end(arglist);
	return 1;
}

bool VFile::Read(char * szFormat ...)
{
	va_list arglist;
	va_start(arglist,szFormat);
	if (m_File == NULL)return 0;
     while(*(szFormat))
		{
			if(*szFormat == '%')
			{
		  szFormat++;
		switch(*szFormat)
		{
		case 's':
			{
		char *szString = va_arg(arglist,char*);
		fscanf(m_File,"%s",szString);
		break;
			}
		case 'd':
			{
		int *nNumber = va_arg(arglist,int*);
	    fscanf(m_File,"%d",nNumber);
		break;
			}
		case 'f':
			{
		float *nNumber = va_arg(arglist,float*);
	    fscanf(m_File,"%.2f",nNumber);
		break;
			}
		case 'x':
			{
		unsigned int* nhex = va_arg(arglist,unsigned int*);
	    fscanf(m_File,"%x",nhex);
		break;
			}
		case 'X':
			{
		unsigned int *nhex = va_arg(arglist,unsigned int*);
	    fscanf(m_File,"%X",nhex);
		break;
			}
		}
			szFormat++;
		}
	 }
		va_end(arglist);
return 1;
}

void VFile::Read(size_t NumBytes,char * szBuffer)
{
/*while((c = fgetc(m_File)) != '\n')nNumBytes++;
fclose(m_File);
szBuffer = new char[nNumBytes];
m_File = fopen (m_pFileName,READ);
while((c = fgetc(m_File)) != feof(m_File))
*(szBuffer++) = c;
szBuffer -= nNumBytes;*/
fread(szBuffer,NumBytes,sizeof(char),m_File);//Потеря производительности !!!
}


//////////C++ File/////////////

template <class WFType>VFile &VFile::operator<<(WFType wfVal)
{
if(typeid(WFType) == typeid(int))
fprintf(m_File,"%d",wfVal);
else if(typeid(WFType) == typeid(char*))
fprintf(m_File,"%s",wfVal);
else if(typeid(WFType) == typeid(char const *))
fprintf(m_File,"%s",wfVal);
else if(typeid(WFType) == typeid(char))
fprintf(m_File,"%c",wfVal);
else if(typeid(WFType) == typeid(float))
fprintf(m_File,"%f",wfVal);
else 
fprintf(m_File,"%d",wfVal);
return *this;
}

template <class WFType>VFile &VFile::operator>>(WFType &wfVal)
{
if(typeid(WFType) == typeid(int))
fscanf(m_File,"%d",&wfVal);
if(typeid(WFType) == typeid(char *))
fscanf(m_File,"%s",wfVal);
if(typeid(WFType) == typeid(char))
fscanf(m_File,"%c",&wfVal);
return *this;//Не передается по ссылке 
}
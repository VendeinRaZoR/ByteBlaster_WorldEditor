#include "TextFile.h"

CTextFile::CTextFile()
{
}

CTextFile::~CTextFile()
{
ZeroMemory(file,sizeof(file));
}

void CTextFile::WriteTXTFile(char * filename,char * writemsg)
{
	f.open(filename,ios::app);
	f << writemsg << "\n";
	f.close();
}

char * CTextFile::ReadTXTFile(char * filename,int nstr,char * format)
{
file = fopen(filename,"r");
if(!file)
{return 0;}
for(int i = 0;i<nstr;i++)
{fgets(buff , sizeof(buff), file)[i];}
sscanf(buff,format,readmsg);
fclose(file);
return readmsg;
}

void CTextFile::ClearTXTFile(char * filename)
{
	f.open(filename);
	f.close();
}
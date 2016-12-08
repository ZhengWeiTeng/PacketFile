#include "StdAfx.h"
#include "SerchAllFile.h"


static CSerchAllFile* instance;


CSerchAllFile::CSerchAllFile(void)
{
}


CSerchAllFile::~CSerchAllFile(void)
{
}


CSerchAllFile* CSerchAllFile::getInstance()
{
if (instance == NULL)
{
instance = new CSerchAllFile();
}


return instance;
}


//遍历文件夹下的文件名列表(包括嵌套文件夹)
void CSerchAllFile::get_filelist(char *foldname,vector<string> &filelist)
{
HANDLE hFind;
WIN32_FIND_DATA fileData;
string line;
char fn[MAX_PATH];
char tmpfn[MAX_PATH];
strcpy(fn,foldname);


//需要对文件夹名的字符串进行处理
if(fn[strlen(fn) -1] != '\\' )
{
strcat(fn, "\\");
}


//留意顺序，此时fn已加入"\\"
strcpy(tmpfn,fn);
//不加*会出错！
strcat(fn, "*");


hFind = FindFirstFile(fn, &fileData);
FindNextFile(hFind, &fileData);
while(FindNextFile(hFind, &fileData))
{
//如果扫描到的当前为文件夹
if (fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
{
if(fileData.cFileName[0]!='.')
{
char szFile[MAX_PATH];
strcpy(szFile,tmpfn);
strcat(szFile,fileData.cFileName);
get_filelist(szFile,filelist);
}
}
//扫描到文件
else
{
line = (string)tmpfn;
line+=fileData.cFileName;
/*if (line.find(".h",0)!=string::npos)
{
filelist.push_back(line);
}
else
{
continue;
}*/
filelist.push_back(line);
}
//cout<<line<<endl;
}
}

#include "StdAfx.h"
#include "MyCab.h"


CMyCab::CMyCab(void)
{
memset(&fh,0x0,sizeof(fh));
memset(ObjectFilePathName,0x0,sizeof(ObjectFilePathName));
}


CMyCab::~CMyCab(void)
{
}


//添加文件到包内
void CMyCab::AddFile(const char * FilePathName)
{
if ( fh.FileCount >= MAX_FILE_COUNT - 1 )
{
cout<<"最多支持"<<MAX_FILE_COUNT<<"个文件"<<endl;
return;
}
strcpy(fh.FileName[fh.FileCount],FilePathName);
fh.FileCount++;
}


//设置打包输出文件
void CMyCab::SetOutPutFile(char * OutFile)
{
memset(ObjectFilePathName,0x0,sizeof(ObjectFilePathName));
strcpy(ObjectFilePathName,OutFile);
}


//获取文件大小(传入以二进制方式打开的文件指针)
long CMyCab::GetFileSize(FILE *pf)
{
//指针移到文件尾
fseek(pf,0,/*SEEK_END*/ 2);
return ftell(pf);
}


//制作打包文件
void CMyCab::DoMakeSFX()
{
if ( fh.FileCount < 1 )
{
cout<<"没有文件添加到打包"<<endl;
return;
}
if ( strlen(ObjectFilePathName) < 1 )
{
cout<<"没有指定打包文件输出位置"<<endl;
return;
}


FILE *pOutFile = NULL;
FILE *pWorkFile = NULL;


//获取所有文件大小
for ( int i = 0 ; i < fh.FileCount ; i++ )
{
pWorkFile = fopen(fh.FileName[i],"rb");
if ( NULL == pWorkFile )
{
cout<<"文件:"<<fh.FileName[i]<<"无法读取["<<strerror(errno)<<"]"<<endl;
return;
}
fh.FileLen[i] = GetFileSize(pWorkFile);
fclose(pWorkFile);
}


//检查是否有对应的文件夹
CheckTargetPath(ObjectFilePathName);
//开始合并写文件
pOutFile = fopen(ObjectFilePathName,"wb");
if ( NULL == pOutFile )
{
cout<<"输出文件创建失败["<<strerror(errno)<<"]"<<endl;
return;
}


//写入文件头
fwrite(&fh,sizeof(fh),1,pOutFile);
//写入各文件
for ( int i = 0 ; i < fh.FileCount ; i++ )
{
unsigned char *pTmpData = NULL;
pWorkFile = fopen(fh.FileName[i],"rb");
if ( NULL == pWorkFile )
{
cout<<"文件:"<<fh.FileName[i]<<"无法读取["<<strerror(errno)<<"]"<<endl;
fclose(pWorkFile);
fclose(pOutFile);
return;
}
pTmpData = new unsigned char[fh.FileLen[i]];
fread(pTmpData,fh.FileLen[i],1,pWorkFile);
if ( ferror(pWorkFile) )
{
cout<<"文件:"<<fh.FileName[i]<<"无法读取["<<strerror(errno)<<"]"<<endl;
fclose(pWorkFile);
fclose(pOutFile);
return;
}
fwrite(pTmpData,fh.FileLen[i],1,pOutFile);
if ( ferror(pOutFile) )
{
cout<<"文件:"<<ObjectFilePathName<<"无法写入["<<strerror(errno)<<"]"<<endl;
fclose(pWorkFile);
fclose(pOutFile);
return;
}
delete [] pTmpData;
fclose(pWorkFile);
}


fclose(pOutFile);
cout<<"打包完成"<<endl;
}


//解包(为了节省时间不写错误处理了,可以根据上面自己添加)
void CMyCab::DoUnSFX(char *CabFilePathName)
{
FILE *pCAB = NULL;
FILE *pWork = NULL;


pCAB = fopen(CabFilePathName,"rb");


//读文件头
memset(&fh,0x0,sizeof(fh));
fread(&fh,sizeof(fh),1,pCAB);


printCAB();


//解包的所有文件放到当前目录下
for ( int i = 0 ; i < fh.FileCount ; i++ )
{
unsigned char *pTmpData = NULL;
pTmpData = new unsigned char[fh.FileLen[i]];
fread(pTmpData,fh.FileLen[i],1,pCAB);
//只取文件名,不要生成文件的路径名
char tmpFileName[MAX_PATH];
string str = "F:\\PacketFile\\test";
string aaa;
aaa.assign(fh.FileName[i] ,strlen(fh.FileName[i]) );
const char *chaaaaa = aaa.replace(0, str.length(), "\\").c_str();
char ptmpC[MAX_PATH];
strcpy(ptmpC, chaaaaa);


memset(tmpFileName,0x0,sizeof(tmpFileName));
strcpy(tmpFileName,ptmpC+1);
//取CAB文件路径
char tmpPathName[MAX_PATH];
memset(tmpPathName,0x0,sizeof(tmpPathName));
strcpy(tmpPathName,CabFilePathName);
char* tmpC = tmpPathName + strlen(tmpPathName);
while('\\' != *tmpC)
{
tmpC--;
}
tmpC++;
*tmpC = '\0';
strcat(tmpPathName,tmpFileName);


pWork = fopen(tmpPathName,"wb");
if (pWork == NULL)
{
CheckTargetPath(tmpPathName);
pWork = fopen(tmpPathName,"wb");
}
fwrite(pTmpData,fh.FileLen[i],1,pWork);
fclose(pWork);
delete [] pTmpData;
}


fclose(pCAB);
}


//显示打包内文件信息
void CMyCab::printSFX()
{
cout<<"文件内信息如下:"<<endl;
cout<<"文件总数:"<<fh.FileCount<<endl;
for ( int i = 0 ; i < fh.FileCount ; i++ )
{
cout<<fh.FileName[i]<<"\t\t\t\t"<<fh.FileLen[i]<<"字节"<<endl;
}
}


//创建文件夹
void CMyCab::CheckTargetPath(string targetPath)
{
//Log &log = Log::getLog("main", "CheckTargetPath");
int e_pos = targetPath.length();
int f_pos = targetPath.find("\\",0);
string subdir;
do
{
e_pos = targetPath.find("\\",f_pos+2);
if(e_pos != -1)
{
subdir = targetPath.substr(0,e_pos);
if(_mkdir(subdir.c_str())==0)
printf( "creat success %s",subdir.c_str());
else 
printf("creat fail %s",subdir.c_str());
}
f_pos = e_pos;
}while(f_pos!=-1);
}
